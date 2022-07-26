#include "game.hpp"
#include "printer.hpp"
#include <curses.h>
#include <sys/types.h>

game::Game::Game(WINDOW *win)
    : grid_(win), gate_({win->_maxx - 1, win->_maxy - 1}) {}

void game::Game::ReadInput() {
    int userInputKey = wgetch(this->grid_.GetWin());

    switch (userInputKey) {
        case kQuit: this->gameOver_ = true; break;
        default: this->input_ = userInputKey;
    }
}

void game::Game::Update() {
    switch (this->input_) {
        case KEY_LEFT: this->gate_.MoveLeft(); break;
        case KEY_RIGHT: this->gate_.MoveRight(); break;
        default: this->gate_.MoveDown();
    }

    bool gravityCollision = this->gate_.GetGravity();
    bool lateralCollision = this->gate_.GetLateral();
    this->gate_.ResetCollision();

    if (gravityCollision) {
        if (!this->gate_.GeneratePiece()) {
            this->gameOver_ = true;
        };
    } else if (!lateralCollision) {
        this->gate_.Replace();
    }
}

void game::Game::Print() const {
    auto current = this->gate_.GetCurrent();
    auto legacy = this->gate_.GetLegacy();
    WINDOW *gameWin = this->grid_.GetWin();

    game::Printer::Clear(gameWin);
    game::Printer::PrintCurrent(current, gameWin);
    game::Printer::PrintLegacy(legacy, gameWin);
}
