#include "game.hpp"
#include "printer.hpp"
#include <curses.h>
#include <sys/types.h>

game::Game::Game(WINDOW *win)
    : grid_(win), gate_({win->_maxx - 1, win->_maxy - 1}) {}

void game::Game::ReadInput() {
    const int USER_INPUT_KEY = wgetch(this->grid_.GetWin());

    switch (USER_INPUT_KEY) {
        case kQuit: this->gameOver_ = true; break;
        default: this->input_ = USER_INPUT_KEY;
    }
}

void game::Game::Update() {
    switch (this->input_) {
        case KEY_LEFT: this->gate_.MoveLeft(); break;
        case KEY_RIGHT: this->gate_.MoveRight(); break;
        case kAction: this->gate_.PlaceDown(); break;
        default: this->gate_.MoveDown();
    }

    const bool GRAVITY_COLLISION = this->gate_.GetGravity();
    const bool LATERAL_COLLISION = this->gate_.GetLateral();
    this->gate_.ResetCollision();

    if (GRAVITY_COLLISION) {
        if (!this->gate_.GeneratePiece()) {
            this->gameOver_ = true;
        };
    } else if (!LATERAL_COLLISION) {
        this->gate_.Replace();
    }

    this->gate_.Tetris();
}

void game::Game::Print() const {
    const auto CURRENT = this->gate_.GetCurrent();
    const auto PREVIOUS = this->gate_.GetPrevious();
    WINDOW *gameWin = this->grid_.GetWin();

    game::Printer::Clear(gameWin);
    game::Printer::PrintCurrent(CURRENT, gameWin);
    game::Printer::PrintPrevious(PREVIOUS, gameWin);
}
