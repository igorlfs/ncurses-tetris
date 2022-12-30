#include "game.hpp"
#include "msgassert.hpp"
#include "windowHandler.hpp"

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

void Colors() {
    constexpr int kTotalColors = 7;
    for (short i = 1; i <= kTotalColors; ++i) {
        init_pair(i, i, i);
    }
}

int main() {
    Initialize();
    Colors();

    WINDOW *gameWindow =
        WindowHandler::CentralizedWindow(kWindowCols, kWindowRows);
    WINDOW *scoreWindow = WindowHandler::MakeScoreWindow(gameWindow);
    game::Game tetris({gameWindow, scoreWindow});

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
