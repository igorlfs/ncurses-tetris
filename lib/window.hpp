#pragma once

#include <ncurses.h>

class Window {
  public:
    /// Constructors
    explicit Window(WINDOW *win);

    /// Getters
    int GetX() const { return this->xMax_ - 1; }
    int GetY() const { return this->yMax_ - 1; }
    int GetSize() const { return (this->xMax_ - 1) * (this->yMax_ - 1); }
    WINDOW *GetWin() const { return this->window_; }

  private:
    WINDOW *window_;
    int yMax_, xMax_;
};
