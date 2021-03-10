#include "tictactoe/tictactoe.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <string>

namespace tictactoe {

using std::string;
using std::vector;
using std::invalid_argument;

Board::Board(const string& board) {
  player_one_ = 'x';
  player_two_ = 'o';
  one_wins_ = 0;
  two_wins_ = 0;
  if (!(IsValidLength(board.length()))) {
    throw invalid_argument("Not a valid board size");
  }
  string boardToLower = board;
  transform(boardToLower.begin(), boardToLower.end(), boardToLower.begin(), ::tolower);
  dimension_ = (int) sqrt(board.size());
  arrayBoard.resize(dimension_, vector<char>(dimension_));
  int charCount = 0;
  for (int r = 0; r < dimension_; r++) {
    for (int c = 0; c < dimension_; c++) {
      arrayBoard[r][c] = boardToLower.at(charCount);
      charCount++;
    }
  }
}

BoardState Board::EvaluateBoard() {
  if (IsTurnSkipped()) {
    return BoardState::UnreachableState;
  }
  EvaluateDiagonal(player_one_);
  EvaluateDiagonal(player_two_);
  EvaluateAntiDiagonal(player_two_);
  EvaluateAntiDiagonal(player_two_);
  for (int row = 0; row < dimension_; row++) {
    EvaluateRow(row, player_one_);
    EvaluateRow(row, player_two_);
  }
  for (int col = 0; col < dimension_; col++) {
    EvaluateCol(col, player_one_);
    EvaluateCol(col, player_two_);
  }
  if (one_wins_ > 0 && two_wins_ > 0) {
    return BoardState::UnreachableState;
  } else if (one_wins_ > 0) {
    return BoardState::Xwins;
  } else if (two_wins_ > 0) {
    return BoardState::Owins;
  } else {
    return BoardState::NoWinner;
  }
}

void Board::EvaluateRow(int row, char player) {
  for (int col = 0; col < dimension_; col++) {
    if (arrayBoard[row][col] != player) {
      return;
    }
  }
  if (player == player_one_) {
    one_wins_++;
  } else {
    two_wins_++;
  }
}

void Board::EvaluateCol(int col, char player) {
  for (int row = 0; row < dimension_; row++) {
    if (arrayBoard[row][col] != player) {
      return;
    }
  }
  if (player == player_one_) {
    one_wins_++;
  } else {
    two_wins_++;
  }
}

void Board::EvaluateDiagonal(char player) {
  for (int rowCol = 0; rowCol < dimension_; rowCol++) {
    if (arrayBoard[rowCol][rowCol] != player) {
      return;
    }
  }
  if (player == player_one_) {
    one_wins_++;
  } else {
    two_wins_++;
  }
}

void Board::EvaluateAntiDiagonal(char player) {
  int row = 0;
  int col = dimension_ - 1;
  while (col >= 0) {
    if (arrayBoard[row][col] != player) {
      return;
    }
    col--;
    row++;
  }
  if (player == player_one_) {
    one_wins_++;
  } else {
    two_wins_++;
  }
}

bool Board::IsTurnSkipped() {
  int oneCount = 0;
  int twoCount = 0;
  for (int r = 0; r < dimension_; r++) {
    for (int c = 0; c < dimension_; c++) {
      if (arrayBoard[r][c] == player_one_) {
        oneCount++;
      } else if (arrayBoard[r][c] == player_two_) {
        twoCount++;
      }
    }
  }
  return oneCount < twoCount || oneCount - twoCount > 1;
}

bool Board::IsValidLength(int input_length) {
  if (input_length < 9) {
    return false;
  }
  double root = sqrt(input_length);
  return (int) root * (int) root == input_length;
}

}  // namespace tictactoe
