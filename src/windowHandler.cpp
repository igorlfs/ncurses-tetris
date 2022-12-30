#include <windowHandler.hpp>

WINDOW *WindowHandler::CentralizedWindow(const int &cols, const int &rows) {
    int yMax;
    int xMax;

    getmaxyx(stdscr, yMax, xMax);

    return newwin(cols, rows, (yMax - cols) / 2, (xMax - rows) / 2);
}
WINDOW *WindowHandler::MakeScoreWindow(WINDOW *primaryWindow) {
    int xMax;
    int yMax;
    int xScr = getmaxx(stdscr);
    getmaxyx(primaryWindow, yMax, xMax);
    return newwin(3, xMax, yMax + 4, (xScr - xMax) / 2);
}
