# ARCHIVED REPOSITORY

For a newer version of the engine, go to https://github.com/ppipelin/radiance/

# Radiance Engine
[![Build Status](https://github.com/ppipelin/radiance_archived/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/ppipelin/radiance_archived/actions/workflows/cmake-multi-platform.yml)
[![Latest Release](https://img.shields.io/github/v/release/ppipelin/radiance_archived?display_name=release)](https://github.com/ppipelin/radiance_archived/releases)
![License](https://img.shields.io/github/license/ppipelin/radiance_archived)

[![Lichess classical rating](https://lichess-shield.vercel.app/api?username=radianceengine&format=classical)](https://lichess.org/@/radianceengine/perf/classical)
[![Lichess rapid rating](https://lichess-shield.vercel.app/api?username=radianceengine&format=rapid)](https://lichess.org/@/radianceengine/perf/rapid)
[![Lichess blitz rating](https://lichess-shield.vercel.app/api?username=radianceengine&format=blitz)](https://lichess.org/@/radianceengine/perf/blitz)
[![Lichess bullet rating](https://lichess-shield.vercel.app/api?username=radianceengine&format=bullet)](https://lichess.org/@/radianceengine/perf/bullet)

C++ chess engine

![Radiance Logo, courtesy of Jim Ablett](dcu2Wsn.png "Image Credit: Jim Ablett")

## Move Generation and Ordering

- Precomputed Bitboard Move Generation
- Transposition Table Move Ordering
- Principal Variation Move Ordering
- MVV-LVA

## Search

- [Principal Variation Search](https://www.chessprogramming.org/Principal_Variation_Search)
- [Alpha-Beta](https://www.chessprogramming.org/Alpha-Beta) Pruning
- [Aspiration Window](https://www.chessprogramming.org/Aspiration_Windows)
- [Late Move Reduction](https://www.chessprogramming.org/Late_Move_Reductions)
- [Quiescence Search](https://www.chessprogramming.org/Quiescence_Search)
- Threefold Repetition
- Time Management

## Evaluation

- [Tuned](https://www.chessprogramming.org/PeSTO%27s_Evaluation_Function) Piece-square Tables
- [_AlphaZero_ Average Piece Values](https://arxiv.org/pdf/2009.04374)
- Bitboard Evaluation
- Transposition Table Evaluation
- Endgame Heuristics
- Pawn Structures Heuristics

## Versions tournament

Time control: 120+1

CCRL [blitz benchmark](https://computerchess.org.uk/ccrl/404/cgi/compare_engines.cgi?family=Radiance&print=Rating+list&print=Score+with+common+opponents).

| Rank | Name             | CCRL  | Elo  | +/- | Games | Score | Draw  |
| ---- | ---------------- | ----- | ---- | --- | ----- | ----- | ----- |
| 0    | [radiance_3.5]   |       | 370* |     |       |       |       |
| 1    | [radiance_3.4]   |  1302 |  345 |   6 | 22528 | 87.9% |  6.4% |
| 2    | [radiance_3.2]   |       |  295 |   6 | 22528 | 84.5% |  7.0% |
| 3    | [radiance_3.3]   |       |  294 |   6 | 22528 | 84.4% |  7.4% |
| 4    | [radiance_3.1.1] |  1118 |  188 |   5 | 22528 | 74.7% |  7.7% |
| 5    | [radiance_2.4]   |       |   54 |   4 | 22528 | 57.8% |  8.8% |
| 6    | [radiance_3.0.1] |       |   39 |   4 | 22528 | 55.6% |  7.6% |
| 7    | [radiance_2.3]   |   866 |   38 |   4 | 22528 | 55.5% |  8.7% |
| 8    | [radiance_2.2]   |       | -136 |   5 | 22528 | 31.3% |  4.1% |
| 9    | [radiance_2.1]   |       | -147 |   5 | 22528 | 30.1% |  3.2% |
| 10   | [radiance_2.0]   |       | -170 |   5 | 22528 | 27.3% |  2.6% |
| 11   | [radiance_1.5]   |       | -375 |   7 | 22528 | 10.4% |  0.2% |
| 12   | [radiance_1.4]   |       | -957 |  36 | 22528 |  0.4% |  0.0% |

## Getting started

### Compilation

```
export CXX=g++-12
export CC=gcc-12
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
make
./radiance
go
stop
```

### UCI options

| Name         | Type  | Default value |  Valid values                                                      | Description                                          |
| ------------ | ----- | ------------- | ------------------------------------------------------------------ | ---------------------------------------------------- |
| `Hash`       | spin  |      256      |                     [1, 131072]                                    | Memory allocated to the transposition table (in MB). |
| `Threads`    | spin  |       1       |                       [1, 1]                                       | Number of threads used to search.                    |
| `Evaluation` | combo |  "PSQTunedBB" | [ "PSQTunedBB", "PSQTuned", "PSQ", "Shannon", "ShannonHeuristics"] | Type of evaluation function.                         |
| `Search`     | combo |  "abNegamax"  |          ["abNegamax", "Minimax", "Random"]                        | Type of search function.                             |

### Commands

- `uci`
- `isready`
- `setoption name <id> [value <x>]`
- `position [fen <string> | startpos | kiwi | lasker] [moves <string>...]`
- `eval`
- `go [movetime <int> | [wtime <int>] [btime <int>] [winc <int>] [binc <int>] | depth <int> | infinite | perft <int>]`
- `stop`
- `quit`
- `ucinewgame`
- `d`

_I'm radiant!_

[radiance_3.5]: https://github.com/ppipelin/radiance_archived/releases/tag/3.5
[radiance_3.4]: https://github.com/ppipelin/radiance_archived/releases/tag/3.4
[radiance_3.3]: https://github.com/ppipelin/radiance_archived/releases/tag/3.3
[radiance_3.2]: https://github.com/ppipelin/radiance_archived/releases/tag/3.2
[radiance_3.1.1]: https://github.com/ppipelin/radiance_archived/releases/tag/3.1.1
[radiance_3.0.1]: https://github.com/ppipelin/radiance_archived/releases/tag/3.0.1
[radiance_2.4]: https://github.com/ppipelin/radiance_archived/releases/tag/2.4
[radiance_2.3]: https://github.com/ppipelin/radiance_archived/releases/tag/2.3
[radiance_2.2]: https://github.com/ppipelin/radiance_archived/releases/tag/2.2
[radiance_2.1]: https://github.com/ppipelin/radiance_archived/releases/tag/2.1
[radiance_2.0]: https://github.com/ppipelin/radiance_archived/releases/tag/2.0
[radiance_2.4]: https://github.com/ppipelin/radiance_archived/releases/tag/2.4
[radiance_1.5]: https://github.com/ppipelin/radiance_archived/releases/tag/1.5
[radiance_1.4]: https://github.com/ppipelin/radiance_archived/releases/tag/1.4
