#include "piece.hpp"
#include "random.hpp"

entity::Piece::Piece() {
    int index = Random::rng(0, kNumLayouts - 1);

    this->layout_ = kLayouts[index];
    this->color_ = static_cast<short>(index + 1);
}

void entity::Piece::MoveLeft() {
    for (auto &block : this->layout_) {
        block.second--;
    }
}

void entity::Piece::MoveRight() {
    for (auto &block : this->layout_) {
        block.second++;
    }
}

void entity::Piece::MoveDown() {
    for (auto &block : this->layout_) {
        block.first++;
    }
}
