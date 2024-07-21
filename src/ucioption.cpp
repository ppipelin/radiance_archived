#include <cassert>
#include <sstream>

#include "uci.h"

UCI::OptionsMap Options; // Global object

namespace UCI {
	/// Our case insensitive less() function as required by UCI protocol
	bool CaseInsensitiveLess::operator() (const std::string &s1, const std::string &s2) const
	{
		return std::lexicographical_compare(s1.begin(), s1.end(), s2.begin(), s2.end(),
			[](char c1, char c2) { return tolower(c1) < tolower(c2); });
	}

	/// UCI::init() initializes the UCI options to their hard-coded default values
	void init(OptionsMap &)
	{
		// constexpr int MaxHashMB = 33554432;
		// o["Debug Log File"] << Option("", on_logger);
		// o["Threads"] << Option(1, 1, 1024, on_threads);
		// o["Hash"] << Option(16, 1, MaxHashMB, on_hash_size);
		// o["Clear Hash"] << Option(on_clear_hash);
		// o["Ponder"] << Option(false);
		// o["MultiPV"] << Option(1, 1, 500);
		// o["Skill Level"] << Option(20, 0, 20);
		// o["Move Overhead"] << Option(10, 0, 5000);
		// o["Slow Mover"] << Option(100, 10, 1000);
		// o["nodestime"] << Option(0, 0, 10000);
		// o["UCI_Chess960"] << Option(false);
		// o["UCI_AnalyseMode"] << Option(false);
		// o["UCI_LimitStrength"] << Option(false);
		// o["UCI_Elo"] << Option(1320, 1320, 3190);
		// o["UCI_ShowWDL"] << Option(false);
		// o["SyzygyPath"] << Option("<empty>", on_tb_path);
		// o["SyzygyProbeDepth"] << Option(1, 1, 100);
		// o["Syzygy50MoveRule"] << Option(true);
		// o["SyzygyProbeLimit"] << Option(7, 0, 7);
		// o["EvalFile"] << Option(EvalFileDefaultName, on_eval_file);
	}

	/// operator<<() is used to print all the options default values in chronological
	/// insertion order (the idx field) and in the format defined by the UCI protocol.
	std::ostream &operator<<(std::ostream &os, const OptionsMap &om)
	{

		for (size_t idx = 0; idx < om.size(); ++idx)
			for (const auto &it : om)
				if (it.second.idx == idx)
				{
					const Option &o = it.second;
					os << "\noption name " << it.first << " type " << o.type;

					if (o.type == "string" || o.type == "check" || o.type == "combo")
						os << " default " << o.defaultValue;

					if (o.type == "spin")
						os << " default " << int(stof(o.defaultValue))
						<< " min " << o.min
						<< " max " << o.max;

					break;
				}

		return os;
	}

	Option::Option(const char *v, OnChange f) : type("string"), min(0), max(0), on_change(f)
	{
		defaultValue = currentValue = v;
	}

	Option::Option(bool v, OnChange f) : type("check"), min(0), max(0), on_change(f)
	{
		defaultValue = currentValue = (v ? "true" : "false");
	}

	Option::Option(OnChange f) : type("button"), min(0), max(0), on_change(f) {}

	Option::Option(double v, int minv, int maxv, OnChange f) : type("spin"), min(minv), max(maxv), on_change(f)
	{
		defaultValue = currentValue = std::to_string(v);
	}

	Option::Option(const char *v, const char *cur, OnChange f) : type("combo"), min(0), max(0), on_change(f)
	{
		defaultValue = v; currentValue = cur;
	}

	Option::operator int() const
	{
		assert(type == "check" || type == "spin");
		return (type == "spin" ? std::stoi(currentValue) : currentValue == "true");
	}

	Option::operator std::string() const
	{
		assert(type == "string");
		return currentValue;
	}

	bool Option::operator==(const char *s) const
	{
		assert(type == "combo");
		return   !CaseInsensitiveLess()(currentValue, s)
			&& !CaseInsensitiveLess()(s, currentValue);
	}

	/// operator<<() inits options and assigns idx in the correct printing order
	void Option::operator<<(const Option &o)
	{

		static size_t insert_order = 0;

		*this = o;
		idx = insert_order++;
	}

	/// operator=() updates currentValue and triggers on_change() action. It's up to
	/// the GUI to check for option's limits, but we could receive the new value
	/// from the user by console window, so let's check the bounds anyway.
	Option &Option::operator=(const std::string &v)
	{

		assert(!type.empty());

		if ((type != "button" && type != "string" && v.empty())
			|| (type == "check" && v != "true" && v != "false")
			|| (type == "spin" && (stof(v) < min || stof(v) > max)))
			return *this;

		if (type == "combo")
		{
			OptionsMap comboMap; // To have case insensitive compare
			std::string token;
			std::istringstream ss(defaultValue);
			while (ss >> token)
				comboMap[token] << Option();
			if (!comboMap.count(v) || v == "var")
				return *this;
		}

		if (type != "button")
			currentValue = v;

		if (on_change)
			on_change(*this);

		return *this;
	}
} // namespace UCI
