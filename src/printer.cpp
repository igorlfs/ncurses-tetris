#include "printer.hpp"

void game::Printer::PrintCurrent(const entity::Piece &current, WINDOW *win) {
    auto layout = current.GetLayout();
    short color = current.GetColor();

    for (auto &block : layout) {
        wattron(win, COLOR_PAIR(color));
        mvwaddch(win, block.first, block.second, '#');
        wattroff(win, COLOR_PAIR(color));
    }
}

void game::Printer::Clear(WINDOW *win) {
    for (int i = 1; i < win->_maxx; ++i) {
        for (int j = 1; j < win->_maxy; ++j) {
            mvwaddch(win, j, i, ' ');
        }
    }
}

void game::Printer::PrintLegacy(const Pieces &legacy, WINDOW *win) {
    for (const auto &piece : legacy) {
        auto layout = piece.GetLayout();
        short color = piece.GetColor();

        for (auto &block : layout) {
            wattron(win, COLOR_PAIR(color));
            mvwaddch(win, block.first, block.second, '#');
            wattroff(win, COLOR_PAIR(color));
        }
    }
}
