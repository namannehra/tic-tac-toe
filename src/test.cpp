#include <iostream>
#include <chrono>
#include "lib/tic-tac-toe.cpp"
#include "lib/tic-tac-toe-ai.cpp"

using std::cout;
using std::endl;

void test(int move) {
  std::chrono::time_point<std::chrono::system_clock> start, end;
  TicTacToe game;
  if (move < 0 || move > 8) {
    cout << "First move     : ";
  } else {
    game.move(move);
    cout << "After move at " << move << ": ";
  }
  start = std::chrono::system_clock::now();
  TicTacToeAi::move(game);
  end = std::chrono::system_clock::now();
  std::chrono::duration<double> seconds = end - start;
  cout << seconds.count() << endl;
}

int main() {
  test(-1);
  test(0);
  test(1);
  test(4);
  return 0;
}