#pragma once

#include "piece.hpp"
#include <curses.h>
#include <vector>

namespace game {

using std::vector;
using Pieces = vector<entity::Piece>;

class Printer {
  public:
    static void PrintCurrent(const entity::Piece &current, WINDOW *win);
    static void PrintPrevious(const Pieces &previous, WINDOW *win);
    static void Clear(WINDOW *win);

  private:
    static constexpr char kChar = ' ';
};

} // namespace game
