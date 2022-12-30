#include <windowHandler.hpp>

WINDOW *WindowHandler::CentralizedWindow(const int &rows, const int &cols) {
    int yMax;
    int xMax;

    getmaxyx(stdscr, yMax, xMax);

    return newwin(rows, cols, (yMax - rows) / 2, (xMax - cols) / 2);
}

WINDOW *WindowHandler::MakeScoreWindow(WINDOW *primaryWindow) {
    constexpr int kWidth = 21;
    constexpr int kHeight = 3;
    int xScr = getmaxx(stdscr);
    int yPri = getbegy(primaryWindow);
    return newwin(kHeight, kWidth, yPri - kHeight, (xScr - kWidth) / 2);
}
