#include "logic.hpp"
#include <algorithm>

bool logic::Logic::GeneratePiece() {
    entity::Piece newPiece;
    int pWidth = newPiece.GetWidth();
    entity::tetramino *layout = newPiece.GetLayoutAddr();
    for (auto &part : *layout) {
        part.second += (this->width_ - pWidth) / 2;
    }
    this->currentPiece_ = newPiece;
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
            map.at(block.first - 1).at(block.second - 1) = true;
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

void logic::Logic::ClearRows(const int &row, entity::tetramino *layout) {
    for (auto it = layout->begin(); it != layout->end();) {
        if (it->first == row) {
            layout->erase(it);
        } else {
            it++;
        }
    }
}

void logic::Logic::PushDown(const int &row, entity::tetramino *layout) {
    for (auto &part : *layout) {
        if (part.first <= row) {
            part.first++;
        }
    }
}

int logic::Logic::Tetris() {
    const vector<unsigned> COMPLETE_ROWS = CheckTetris();
    for (const auto &row : COMPLETE_ROWS) {
        for (auto &piece : this->previousPieces_) {
            entity::tetramino *layout = piece.GetLayoutAddr();
            ClearRows(static_cast<int>(row), layout);
            PushDown(static_cast<int>(row), layout);
        }
    }
    this->scoreMultiplier_ = COMPLETE_ROWS.size();
    return K_SCORE_MAP.at(this->scoreMultiplier_);
}

void logic::Logic::PlaceDown() {
    while (!this->hasCollided_) {
        MoveDown();
        Replace();
    }
}
