#include <string>

#include <catch2/catch.hpp>
#include <tictactoe/tictactoe.h>

using tictactoe::Board;
using tictactoe::BoardState;

TEST_CASE("Invalid string provided to constructor") {
  SECTION("String is too short") {
    REQUIRE_THROWS_AS(Board("xxooo"), std::invalid_argument);
  }

  SECTION("String is empty") {
    REQUIRE_THROWS_AS(Board(""), std::invalid_argument);
  }

  SECTION("String is too long") {
    REQUIRE_THROWS_AS(Board("XoX..oXooX"), std::invalid_argument);
  }
}

TEST_CASE("Boards with no winner") {
  SECTION("Full 3x3 board with no winner") {
    REQUIRE(Board("xxoooxxxo").EvaluateBoard() == BoardState::NoWinner);
  }

  SECTION("3x3 game in progress x went last") {
    REQUIRE(Board("..O.x.X..").EvaluateBoard() == BoardState::NoWinner);
  }

  SECTION("3x3 game in progress o went last") {
    REQUIRE(Board("..O.x.X..").EvaluateBoard() == BoardState::NoWinner);
  }

  SECTION("Full 4x4 board with no winner") {
    REQUIRE(Board("xxooooxxxxooooxx").EvaluateBoard() == BoardState::NoWinner);
  }

  SECTION("Empty Board State") {
    REQUIRE(Board(".........").EvaluateBoard() == BoardState::NoWinner);
  }
}

TEST_CASE("Valid Boards X Wins") {
  SECTION("3x3 board vertical win") {
    REQUIRE(Board(".xoOxo.x.").EvaluateBoard() == BoardState::Xwins);
  }

  SECTION("3x3 board horizontal win") {
    REQUIRE(Board("o.oxXx.s3").EvaluateBoard() == BoardState::Xwins);
  }

  SECTION("3x3 board diagonal win") {
    REQUIRE(Board("xo..xo.Ox").EvaluateBoard() == BoardState::Xwins);
  }

  SECTION("3x3 board anti-diagonal win") {
    REQUIRE(Board(".ox.Xox.o").EvaluateBoard() == BoardState::Xwins);
  }

  SECTION("4x4 board horizontal win") {
    REQUIRE(Board("xXxxO.o.O.o..O.x").EvaluateBoard() == BoardState::Xwins);
  }
}

TEST_CASE("Valid Boards O wins") {
  SECTION("3x3 board vertical win") {
    REQUIRE(Board("x.ox.o.xo").EvaluateBoard() == BoardState::Owins);
  }

  SECTION("3x3 board horizontal win") {
    REQUIRE(Board("oOox.x.sx").EvaluateBoard() == BoardState::Owins);
  }

  SECTION("3x3 board diagonal win") {
    REQUIRE(Board("ox..ox.Xo").EvaluateBoard() == BoardState::Owins);
  }

  SECTION("3x3 board anti-diagonal win") {
    REQUIRE(Board(".Xo.oXo.x").EvaluateBoard() == BoardState::Owins);
  }

  SECTION("4x4 board diagonal win") {
    REQUIRE(Board("Ox..Xo.x..o..x.O").EvaluateBoard() == BoardState::Owins);
  }
}
