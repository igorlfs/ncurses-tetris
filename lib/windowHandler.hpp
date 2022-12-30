#include <curses.h>
class WindowHandler {
  public:
    static WINDOW *CentralizedWindow(const int &cols, const int &rows);

    static WINDOW *MakeScoreWindow(WINDOW *primaryWindow);
};
