#include "printer.hpp"

void game::Printer::PrintCurrent(const entity::Piece &current, WINDOW *win) {
    const auto LAYOUT = current.GetLayout();
    const short COLOR = current.GetColor();

    for (const auto &block : LAYOUT) {
        wattron(win, COLOR_PAIR(COLOR));
        mvwaddch(win, block.first, block.second, kChar);
        wattroff(win, COLOR_PAIR(COLOR));
    }
}

void game::Printer::Clear(WINDOW *win) {
    for (int i = 1; i < win->_maxx; ++i) {
        for (int j = 1; j < win->_maxy; ++j) {
            mvwaddch(win, j, i, kChar);
        }
    }
}

void game::Printer::PrintPrevious(const Pieces &previous, WINDOW *win) {
    for (const auto &piece : previous) {
        const auto LAYOUT = piece.GetLayout();
        const short COLOR = piece.GetColor();

        for (const auto &block : LAYOUT) {
            wattron(win, COLOR_PAIR(COLOR));
            mvwaddch(win, block.first, block.second, kChar);
            wattroff(win, COLOR_PAIR(COLOR));
        }
    }
}
