# TicTacToe

Tic-tac-toe game with 1 player and 2 player modes in C++11. 1 player mode is
implemented using [minimax](https://en.wikipedia.org/wiki/Minimax) with
following improvements:

* A fast win is prefered over a slow win.
* A slow loss is prefered over a fast loss.
* Checks are performed when scoring board at 0 or 1 moves to improve speed.
* Out of all possible best moves, one move is made at random using time as seed.

A test file is included which times computer's move at different positions.

## Structure

* `/src`: All source code
  * `/lib`: Classes, functions, etc.
* `/build`: Binaries for production
* `/debug`: Temporary binaries for development

## Build instructions

* For development
```
g++ --std c++11 -o debug/tic-tac-toe src/main.cpp
./debug/tic-tac-toe
```

* For production
```
g++ --std c++11 -o build/tic-tac-toe -O3 src/main.cpp
./build/tic-tac-toe
```

## Testing

```
g++ --std c++11 -o debug/test -O3 src/test.cpp
./debug/test
```