#ifndef TIC_TAC_TOE
#define TIC_TAC_TOE

#include <ostream>
#include <array>

using std::ostream;
using std::endl;

class TicTacToe {
  public:
    enum class State {inProgress, draw, player1Won, player2Won};
    enum class Mark {blank, cross, zero};
    typedef std::array<Mark, 9> Board;
    struct Errors {
      struct GameOver: std::runtime_error {
        GameOver(): runtime_error("Game is over.") {}
      };
      struct NotEmpty: std::runtime_error {
        NotEmpty(): runtime_error("Index is not empty.") {}
      };
    };
    TicTacToe() {
      clear();
    }
    State state() const {
      return _state;
    }
    unsigned moves() const {
      return _moves;
    }
    Mark get(unsigned index) const {
      if (index > 8) {
        throw std::out_of_range("Index is not between 1 and 9.");
      }
      return _board[index];
    }
    Board board() const {
      return _board;
    }
    void move(unsigned index) {
      if (index > 8) {
        throw std::out_of_range("Index is not between 1 and 9.");
      }
      if (_state != State::inProgress) {
        throw Errors::GameOver();
      }
      if (_board[index] != Mark::blank) {
        throw Errors::NotEmpty();
      }
      _board[index] = _moves % 2 ? Mark::zero : Mark::cross;
      _moves++;
      updateState();
    }
    void clear() {
      _state = State::inProgress;
      _moves = 0;
      _board.fill(Mark::blank);
    }
    friend ostream& operator<< (ostream& output, const TicTacToe& game) {
      for (unsigned i = 0; i < 3; i++) {
        if (!i) {
          output << "-------------";
        }
        output << endl;
        for (unsigned j = 0; j < 3; j++) {
          if (!j) {
            output << "|";
          }
          output << " " << toChar(game._board[i * 3 + j]) << " |";
        }
        output << endl << "-------------";
      }
      return output;
    }
  private:
    State _state;
    unsigned _moves;
    Board _board;
    void updateState() {
      if (_moves < 5) {
        return;
      }
      Mark center = _board[4];
      if (center != Mark::blank) {
        for (unsigned i = 0; i < 4; i++) {
          if (_board[i] == center && _board[8 - i] == center) {
            return setWinner(center);
          }
        }
      }
      Mark topLeft = _board[0];
      if (
        topLeft != Mark::blank && (
          (_board[1] == topLeft && _board[2] == topLeft) ||
          (_board[3] == topLeft && _board[6] == topLeft)
        )
      ) {
        return setWinner(topLeft);
      }
      Mark bottomRight = _board[8];
      if (
        bottomRight != Mark::blank && (
          (_board[2] == bottomRight && _board[5] == bottomRight) ||
          (_board[6] == bottomRight && _board[7] == bottomRight)
        )
      ) {
        return setWinner(bottomRight);
      }
      if (_moves == 9) {
        _state = State::draw;
      }
    }
    void setWinner(Mark mark) {
      _state = mark == Mark::cross ? State::player1Won : State::player2Won;
    }
    static char toChar(Mark mark) {
      if (mark == Mark::cross) {
        return 'X';
      }
      if (mark == Mark::zero) {
        return 'O';
      }
      return ' ';
    }
};

#endif