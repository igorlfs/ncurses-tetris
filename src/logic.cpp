#include "logic.hpp"
#include <algorithm>

bool logic::Logic::GeneratePiece() {
    const entity::Piece NEW_PIECE;
    this->currentPiece_ = NEW_PIECE;
    this->newPos_ = this->currentPiece_;

    return !CheckCollision();
}

bool logic::Logic::MoveDown() {
    this->newPos_ = GetCurrent();
    const auto *layout = GetCurrentLayout();

    for (const auto &block : *layout) {
        if (block.first + 1 > this->height_) {
            Place();
            this->hasCollided_ = true;
            return true;
        }
    }

    this->newPos_.MoveDown();
    if (CheckCollision()) {
        Place();
    }

    return false;
}

void logic::Logic::MoveLeft() {
    this->newPos_ = GetCurrent();
    const auto *layout = GetCurrentLayout();

    for (const auto &block : *layout) {
        if (block.second - 1 < 1) {
            return;
        }
    }

    this->newPos_.MoveLeft();

    CheckCollision(true);
}

void logic::Logic::MoveRight() {
    this->newPos_ = GetCurrent();
    const auto *layout = GetCurrentLayout();

    for (const auto &block : *layout) {
        if (block.second + 1 > this->width_) {
            return;
        }
    }

    this->newPos_.MoveRight();

    CheckCollision(true);
}

bool logic::Logic::CheckCollision(const bool &lateral) {
    const auto *layout = this->newPos_.GetLayoutAddr();

    for (const auto &piece : this->previousPieces_) {
        const auto PREVIOUS_LAYOUT = piece.GetLayout();
        for (const auto &previous : PREVIOUS_LAYOUT) {
            for (const auto &block : *layout) {
                if (block == previous) {
                    lateral ? this->lateralCollision_ = true
                            : this->hasCollided_ = true;
                    return true;
                }
            }
        }
    }

    return false;
}

void logic::Logic::ResetCollision() {
    this->hasCollided_ = false;
    this->lateralCollision_ = false;
}

logic::vector<unsigned> logic::Logic::CheckTetris() {
    vector<vector<bool>> map(this->height_);

    for (auto &row : map) {
        row.resize(this->width_, false);
    }

    for (const auto &piece : this->previousPieces_) {
        const auto LAYOUT = piece.GetLayout();
        for (const auto &block : LAYOUT) {
            // Subtract 1 from the dimensions as the first row
            // and the first column are the border
            map[block.first - 1][block.second - 1] = true;
        }
    }

    vector<unsigned> completeRows;
    int iterator = 0;
    for (const auto &row : map) {
        namespace ranges = std::ranges;
        if (ranges::all_of(row.begin(), row.end(),
                           [](const bool &item) { return item; })) {
            completeRows.push_back(iterator + 1);
        }
        iterator++;
    }

    return completeRows;
}

void logic::Logic::Tetris() {
    const vector<unsigned> COMPLETE_ROWS = CheckTetris();
    for (const auto &row : COMPLETE_ROWS) {
        for (auto &piece : this->previousPieces_) {
            auto *layout = piece.GetLayoutAddr();
            for (auto it = layout->begin(); it != layout->end();) {
                if (it->first == static_cast<int>(row)) {
                    layout->erase(it);
                } else {
                    it++;
                }
            }
        }
    }
}
