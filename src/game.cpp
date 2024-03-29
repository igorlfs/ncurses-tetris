#include "game.hpp"
#include "piece.hpp"
#include "printer.hpp"
#include <curses.h>
#include <string>
#include <sys/types.h>

using std::string;

game::Game::Game(pair<WINDOW *, WINDOW *> windows)
    : grid_(windows.first), scoreWindow_(windows.second),
      gate_({windows.first->_maxx - 1, windows.first->_maxy - 1}) {}

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
        case kRotate: this->gate_.Rotate(); break;
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

    this->gate_.PlaceDown(true);

    this->score_ += this->gate_.Tetris();
}

void game::Game::Print() const {
    const auto CURRENT = this->gate_.GetCurrent();
    auto ghost = this->gate_.GetGhost();
    const int COLOR = 8;
    ghost.SetColor(COLOR);
    const auto PREVIOUS = this->gate_.GetPrevious();
    WINDOW *gameWin = this->grid_.GetWin();
    WINDOW *scoreWin = this->scoreWindow_.GetWin();

    game::Printer::Clear(gameWin);
    game::Printer::PrintPiece(ghost, gameWin);
    game::Printer::PrintPiece(CURRENT, gameWin);
    game::Printer::PrintPrevious(PREVIOUS, gameWin);
    game::Printer::PrintScore(this->score_, scoreWin);
}

void game::Game::Quit() const {
    WINDOW *scoreWin = this->scoreWindow_.GetWin();

    const string MESSAGE = "GAME OVER";
    const int M_SIZE = static_cast<int>(MESSAGE.size());
    mvwprintw(scoreWin, 1, scoreWin->_maxx - M_SIZE, "%s", MESSAGE.c_str());
    wrefresh(scoreWin);
    wgetch(scoreWin);
}
