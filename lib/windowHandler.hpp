#include <curses.h>
class WindowHandler {
  public:
    static WINDOW *CentralizedWindow(const int &rows, const int &cols);

    static WINDOW *MakeScoreWindow(WINDOW *primaryWindow);
};
