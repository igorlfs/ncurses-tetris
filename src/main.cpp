#include "game.hpp"
#include "msgassert.hpp"

static constexpr int kWindowCols = 12;
static constexpr int kWindowRows = 18;

void Initialize() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    refresh();
    assert(has_colors(), "No color support!");
    start_color();
    use_default_colors();
}

WINDOW *CentralizeWindow() {
    int yMax;
    int xMax;

    getmaxyx(stdscr, yMax, xMax);

    return newwin(kWindowCols, kWindowRows, (yMax - kWindowCols) / 2,
                  (xMax - kWindowRows) / 2);
}

void Colors() {
    constexpr int kTotalColors = 7;
    for (short i = 1; i <= kTotalColors; ++i) {
        init_pair(i, i, i);
    }
}

int main() {
    Initialize();
    Colors();

    WINDOW *gameWindow = CentralizeWindow();
    game::Game tetris(gameWindow);

    while (!tetris.IsGameOver()) {
        tetris.Print();
        tetris.ReadInput();
        tetris.Update();
    }
    getch();

    delwin(gameWindow);
    refresh();
    endwin();
}
