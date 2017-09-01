#include <iostream>
#include <conio.h>
#include "lib/tic-tac-toe.cpp"
#include "lib/tic-tac-toe-ai.cpp"

using std::cin;
using std::cout;
using std::endl;

bool multiplayer() {
  while (true) {
    unsigned players;
    cout << "1 player or 2 players? (1/2) ";
    cin >> players;
    if (players == 1) {
      return false;
    }
    if (players == 2) {
      return true;
    }
  }
}

bool userFirst() {
  while (true) {
    char c;
    cout << "Go first? (Y/N) ";
    cin >> c;
    if (c == 'Y' || c == 'y') {
      return true;
    }
    if (c == 'N' || c == 'n') {
      return false;
    }
  }
}

struct Player {
  std::string name;
  bool ai;
  void move(TicTacToe& game) {
    if (ai) {
      cout << name << " move: " << TicTacToeAi::move(game) + 1 << endl;
    } else {
      while (true) {
        cout << name << " move: ";
        unsigned position;
        cin >> position;
        try {
          game.move(position - 1);
          break;
        } catch (std::out_of_range) {
          cout << "Position must be between 1 and 9" << endl;
        } catch (TicTacToe::Errors::NotEmpty) {
          cout << "Position is not empty" << endl;
        }
      }
    }
  }
};

int main() {
  cout << "Welcome to TicTacToe" << endl;
  Player player1, player2;
  if (multiplayer()) {
    player1 = {"Player 1", false};
    player2 = {"Player 2", false};
  } else if (userFirst()) {
    player1 = {"Player", false};
    player2 = {"AI", true};
  } else {
    player1 = {"AI", true};
    player2 = {"Player", false};
  }
  char const* instructions =
    #include "lib/instructions.text"
  ;
  cout << endl << instructions << endl << endl;
  if (player1.ai) {
    cout << "Press any key to continue . . . ";
    getch();
    cout << endl;
  }
  TicTacToe game;
  TicTacToe::State state = game.state();
  while (state == TicTacToe::State::inProgress) {
    if (game.moves() % 2) {
      player2.move(game);
    } else {
      player1.move(game);
    }
    cout << game << endl << endl;
    state = game.state();
  }
  if (state == TicTacToe::State::draw) {
    cout << "Draw" << endl;
  } else {
    cout
      << (state == TicTacToe::State::player1Won ? player1 : player2).name
      << " won"
      << endl;;
  }
  return 0;
}