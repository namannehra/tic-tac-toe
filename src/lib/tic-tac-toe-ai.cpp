#ifndef TIC_TAC_TOE_AI
#define TIC_TAC_TOE_AI

#include <random>
#include <chrono>
#include "tic-tac-toe.cpp"

class TicTacToeAi {
  public:
    static int score(const TicTacToe& game, bool maximize = false) {
      unsigned moves = game.moves();
      if (moves <= 1) {
        return 0;
      }
      return score(game, moves, maximize);
    }
    static unsigned move(TicTacToe& game) {
      if (game.state() != TicTacToe::State::inProgress) {
        throw TicTacToe::Errors::GameOver();
      }
      int bestScore = - 10;
      unsigned bestMoves[9];
      unsigned bestMovesFilled = 0;
      for (unsigned i = 0; i < 9; i++) {
        TicTacToe newGame = game;
        try {
          newGame.move(i);
        } catch (TicTacToe::Errors::NotEmpty) {
          continue;
        }
        int _score = score(newGame);
        if (_score > bestScore) {
          bestScore = _score;
          bestMovesFilled = 1;
          bestMoves[0] = i;
        } else if (_score == bestScore) {
          bestMoves[bestMovesFilled++] = i;
        }
      }
      std::default_random_engine generator;
      std::uniform_int_distribution<unsigned>
        distribution(0, bestMovesFilled - 1);
      generator
        .seed(std::chrono::system_clock::now().time_since_epoch().count());
      unsigned move = bestMoves[distribution(generator)];
      game.move(move);
      return move;
    }
  private:
    static int score(const TicTacToe& game, unsigned depth, bool maximize) {
      TicTacToe::State state = game.state();
      if (state == TicTacToe::State::draw) {
        return 0;
      } else if (state != TicTacToe::State::inProgress) {
        return maximize ? depth - 10 : 10 - depth;
      }
      if (maximize) {
        int bestScore = - 10;
        for (unsigned i = 0; i < 9; i++) {
          TicTacToe newGame = game;
          try {
            newGame.move(i);
          } catch (TicTacToe::Errors::NotEmpty) {
            continue;
          }
          int _score = score(newGame, depth + 1, false);
          if (_score > bestScore) {
            bestScore = _score;
          }
        }
        return bestScore;
      } else {
        int bestScore = 10;
        for (unsigned i = 0; i < 9; i++) {
          TicTacToe newGame = game;
          try {
            newGame.move(i);
          } catch (TicTacToe::Errors::NotEmpty) {
            continue;
          }
          int _score = score(newGame, depth + 1, true);
          if (_score < bestScore) {
            bestScore = _score;
          }
        }
        return bestScore;
      }
    }
};

#endif