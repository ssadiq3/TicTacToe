#include "tictactoe/tictactoe.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>

namespace tictactoe {

using std::string;
using std::vector;
using std::invalid_argument;

Board::Board(const string& board) {
  playerOne = 'x';
  playerTwo = 'o';
  pOneWins = 0;
  pTwoWins = 0;
  if (!(IsValidLength(board.length()))) {
    throw invalid_argument("Not a valid board size");
  }
  string boardToLower = board;
  transform(boardToLower.begin(), boardToLower.end(), boardToLower.begin(), ::tolower);
  dimension = (int) sqrt(board.size());
  arrayBoard.resize(dimension, vector<char>(dimension));
  int charCount = 0;
  for (int r = 0; r < dimension; r++) {
    for (int c = 0; c < dimension; c++) {
      arrayBoard[r][c] = boardToLower.at(charCount);
      charCount++;
    }
  }
}

BoardState Board::EvaluateBoard() {
  if (IsTurnSkipped()) {
    return BoardState::UnreachableState;
  }
  EvaluateDiagonal(playerOne);
  EvaluateDiagonal(playerTwo);
  EvaluateAntiDiagonal(playerOne);
  EvaluateAntiDiagonal(playerTwo);
  for (int row = 0; row < dimension; row++) {
    EvaluateRow(row, playerOne);
    EvaluateRow(row, playerTwo);
  }
  for (int col = 0; col < dimension; col++) {
    EvaluateCol(col, playerOne);
    EvaluateCol(col, playerTwo);
  }
  std::cout<<pOneWins<<std::endl;
  std::cout<<pTwoWins<<std::endl;
  if (pOneWins > 0 && pTwoWins > 0) {
    return BoardState::UnreachableState;
  } else if (pOneWins > 0) {
    return BoardState::Xwins;
  } else if (pTwoWins > 0) {
    return BoardState::Owins;
  } else {
    return BoardState::NoWinner;
  }
}

void Board::EvaluateRow(int row, char player) {
  for (int col = 0; col < dimension; col++) {
    if (arrayBoard[row][col] != player) {
      return;
    }
  }
  if (player == playerOne) {
    pOneWins++;
  } else {
    pTwoWins++;
  }
}

void Board::EvaluateCol(int col, char player) {
  for (int row = 0; row < dimension; row++) {
    if (arrayBoard[row][col] != player) {
      return;
    }
  }
  if (player == playerOne) {
    pOneWins++;
  } else {
    pTwoWins++;
  }
}

void Board::EvaluateDiagonal(char player) {
  for (int rowCol = 0; rowCol < dimension; rowCol++) {
    if (arrayBoard[rowCol][rowCol] != player) {
      return;
    }
  }
  if (player == playerOne) {
    pOneWins++;
  } else {
    pTwoWins++;
  }
}

void Board::EvaluateAntiDiagonal(char player) {
  int row = 0;
  int col = dimension - 1;
  while (col >= 0) {
    if (arrayBoard[row][col] != player) {
      return;
    }
    col--;
    row++;
  }
  if (player == playerOne) {
    pOneWins++;
  } else {
    pTwoWins++;
  }
}

bool Board::IsTurnSkipped() {
  int oneCount = 0;
  int twoCount = 0;
  for (int r = 0; r < dimension; r++) {
    for (int c = 0; c < dimension; c++) {
      if (arrayBoard[r][c] == playerOne) {
        oneCount++;
      } else if (arrayBoard[r][c] == playerTwo) {
        twoCount++;
      }
    }
  }
  return abs(oneCount - twoCount) > 1;
}

bool Board::IsValidLength(int inputLength) {
  if (inputLength < 9) {
    return false;
  }
  double root = sqrt(inputLength);
  return (int) root * (int) root == inputLength;
}

}  // namespace tictactoe
