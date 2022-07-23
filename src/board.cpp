#include "board.hpp"

Board::Board(WINDOW *win) : window_(win), yMax_(win->_maxy), xMax_(win->_maxx) {
    box(this->window_, 0, 0);
    wrefresh(this->window_);
    keypad(this->window_, true);
    leaveok(this->window_, true);
}
