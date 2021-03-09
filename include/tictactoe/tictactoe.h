#pragma once

#include <string>
#include <vector>

namespace tictactoe {

/**
 * This enumeration specifies the possible results of the evaluation of a
 * Tic-Tac-Toe board.
 */
enum class BoardState {
  NoWinner,
  Xwins,
  Owins,
  UnreachableState,
};

/**
 * This class can store a Tic-Tac-Toe board and evaluate its state.
 */
class Board {
 public:
  /**
   * Constructs a Board from a string consisting of 9 characters in row-major
   * order (i.e. the first three characters specify the first row).
   *
   * An 'X' or 'x' represents that the corresponding square is filled with an X,
   * an 'O' or 'o' represents that the corresponding square is filled with an O,
   * and any other character represents that the corresponding square is empty.
   *
   * This method throws a std::invalid_argument exception if the string provided
   * is not a valid board.
   */
  Board(const std::string& board);

  /**
   * Evaluates the state of the board.
   */
  BoardState EvaluateBoard();

 private:
 std::vector< std::vector< char > > arrayBoard;
 int dimension;
 int pOneWins;
 int pTwoWins;
 char playerOne;
 char playerTwo;

  /**
    * Evaluates a win through a given row and increments win count for that player
    * @param boardArray 2D array of tic tac toe board
    * @param row which row is being evaluated
    * @param player 'x' or 'o'
    */
 void EvaluateRow(int row, char player);

  /**
    * Evaluates a win through a given row and increments win count for that player
    * @param boardArray 2D array of tic tac toe board
    * @param col which column is being evaluated
    * @param player 'x' or 'o'
    */
 void EvaluateCol(int col, char player);

  /**
    * Evaluates a win in the left-right diagonal for given player, increments win count for that player
    * @param boardArray 2D array of tic tac toe board
    * @param player 'x' or 'o'
    */
 void EvaluateDiagonal(char player);

  /**
    * Evaluates a win in the right-left diagonal for given player, increments win count for that player
    * @param boardArray 2D array of tic tac toe board
    * @param player 'x' or 'o'
    */
 void EvaluateAntiDiagonal(char player);

  /**
    * Checks if a turn has been skipped
    * @param boardArray 2D array of tic tac toe board
    * @return True if a turn has been skipped, false if not
    */
 bool IsTurnSkipped();

  /**
    * Evaluates validity of string length, must be >= 9 and perfect square
    * @param inputLength length of board string
    * @return true if valid, false if invalid
    */
 bool IsValidLength(int inputLength);

};

}  // namespace tictactoe
