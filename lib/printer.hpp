#pragma once

#include "piece.hpp"
#include <curses.h>
#include <vector>

namespace game {

using std::vector;
using Pieces = vector<entity::Piece>;

class Printer {
  public:
    static void PrintPiece(const entity::Piece &piece, WINDOW *win);
    static void PrintPrevious(const Pieces &previous, WINDOW *win);
    static void PrintScore(const int &score, WINDOW *win);
    static void Clear(WINDOW *win);

  private:
    static void AuxPrint(const entity::tetramino &layout, const int &color,
                         WINDOW *win);
    static constexpr char kChar = ' ';
};

} // namespace game
