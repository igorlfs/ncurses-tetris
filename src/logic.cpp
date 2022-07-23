#include "logic.hpp"
#include <algorithm>

bool logic::Logic::GeneratePiece() {
    const entity::Piece NEW_PIECE;
    this->currentPiece_ = NEW_PIECE;
    this->newPos_ = this->currentPiece_;

    return !CheckCollision();
}

bool logic::Logic::MoveDown(const int &height) {
    this->newPos_ = GetCurrent();
    auto *layout = GetCurrentLayout();

    for (auto &block : *layout) {
        if (block.first + 1 > height) {
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
    auto *layout = GetCurrentLayout();

    for (auto &block : *layout) {
        if (block.second - 1 < 1) {
            return;
        }
    }

    this->newPos_.MoveLeft();

    CheckCollision(true);
}

void logic::Logic::MoveRight(const int &width) {
    this->newPos_ = GetCurrent();
    auto *layout = GetCurrentLayout();

    for (auto &block : *layout) {
        if (block.second + 1 > width) {
            return;
        }
    }

    this->newPos_.MoveRight();

    CheckCollision(true);
}

bool logic::Logic::CheckCollision(const bool &lateral) {
    auto *layout = this->newPos_.GetLayoutAddr();

    for (const auto &piece : this->legacyPieces_) {
        auto legacyLayout = piece.GetLayout();
        for (auto &legacyBlock : legacyLayout) {
            for (auto &block : *layout) {
                if (block == legacyBlock) {
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
