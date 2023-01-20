#include "printer.hpp"

void game::Printer::PrintPiece(const entity::Piece &piece, WINDOW *win) {
    const auto LAYOUT = piece.GetLayout();
    const short COLOR = piece.GetColor();

    AuxPrint(LAYOUT, COLOR, win);
}

void game::Printer::PrintPrevious(const Pieces &previous, WINDOW *win) {
    for (const auto &piece : previous) {
        const auto LAYOUT = piece.GetLayout();
        const short COLOR = piece.GetColor();

        AuxPrint(LAYOUT, COLOR, win);
    }
}

void game::Printer::PrintScore(const int &score, WINDOW *win) {
    mvwprintw(win, 1, 1, "SCORE %d", score);
    wrefresh(win);
}

void game::Printer::Clear(WINDOW *win) {
    for (int i = 1; i < win->_maxx; ++i) {
        for (int j = 1; j < win->_maxy; ++j) {
            mvwaddch(win, j, i, kChar);
        }
    }
}

void game::Printer::AuxPrint(const entity::tetramino &layout, const int &color,
                             WINDOW *win) {
    wattron(win, COLOR_PAIR(color));
    for (const auto &block : layout) {
        mvwaddch(win, block.first, block.second, kChar);
    }
    wattroff(win, COLOR_PAIR(color));
}
