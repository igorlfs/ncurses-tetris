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
    static void PrintLegacy(const Pieces &legacy, WINDOW *win);
    static void Clear(WINDOW *win);
};

} // namespace game
