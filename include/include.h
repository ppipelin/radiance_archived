#pragma once
#pragma warning(disable: 4505)

#include <iostream>
#include <vector>
#include <array>
#include <cstdint>
#include <string>
#include <chrono>
#include <cassert>
#include <utility>

using UInt = std::uint_fast16_t;
using Key = uint64_t;
using Int = std::int_fast16_t;
using Value = Int;

constexpr UInt BOARD_SIZE = 8;
constexpr UInt BOARD_SIZE2 = 8 * 8;

constexpr UInt MAX_MOVES = 218;
constexpr UInt MAX_PLY = 246;

// Chess-related constexpr should only be used for chess-related concepts, otherwise use regular math-related namings.
constexpr Value VALUE_ZERO = 0;
constexpr Value VALUE_DRAW = 0;

constexpr Value VALUE_MATE = 32000;
constexpr Value VALUE_INFINITE = VALUE_MATE + 1;
constexpr Value VALUE_NONE = VALUE_MATE + 2;
constexpr Value VALUE_MATE_IN_MAX_PLY = VALUE_MATE - MAX_PLY;
constexpr Value VALUE_MATED_IN_MAX_PLY = -VALUE_MATE_IN_MAX_PLY;

constexpr Value VALUE_TB = VALUE_MATE_IN_MAX_PLY - 1;
constexpr Value VALUE_TB_WIN_IN_MAX_PLY = VALUE_TB - MAX_PLY;
constexpr Value VALUE_TB_LOSS_IN_MAX_PLY = -VALUE_TB_WIN_IN_MAX_PLY;

static void debug(std::string str)
{
	std::cout << "DEBUG: " << str << std::endl;
}

static void warn(std::string str)
{
	std::cout << "WARN: " << str << std::endl;
}

static void err(std::string str)
{
	std::cout << "ERR: " << str << std::endl;
}

// From https://github.com/official-stockfish/Stockfish
// xorshift64star Pseudo-Random Number Generator
// This class is based on original code written and dedicated
// to the public domain by Sebastiano Vigna (2014).
// It has the following characteristics:
//
//  -  Outputs 64-bit numbers
//  -  Passes Dieharder and SmallCrush test batteries
//  -  Does not require warm-up, no zeroland to escape
//  -  Internal state is a single 64-bit integer
//  -  Period is 2^64 - 1
//  -  Speed: 1.60 ns/call (Core i7 @3.40GHz)
//
// For further analysis see
//   <http://vigna.di.unimi.it/ftp/papers/xorshift.pdf>

class PRNG
{
	uint64_t s;

	uint64_t rand64()
	{

		s ^= s >> 12, s ^= s << 25, s ^= s >> 27;
		return s * 2685821657736338717LL;
	}

public:
	PRNG(uint64_t seed) : s(seed) { assert(seed); }

	template<typename T> T rand() { return T(rand64()); }

	/// Special generator used to fast init magic numbers.
	/// Output values only have 1/8th of their bits set on average.
	template<typename T> T sparse_rand()
	{
		return T(rand64() & rand64() & rand64());
	}
};
