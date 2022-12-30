#include "piece.hpp"
#include "random.hpp"
#include <algorithm>

entity::Piece::Piece() {
    ulong index = Random::Rng(0, kNumLayouts - 1);

    this->layout_ = kLayouts[index];
    this->color_ = static_cast<short>(index + 1);
}

int entity::Piece::GetWidth() const {
    const int TOP =
        std::max_element(this->layout_.begin(), this->layout_.end(),
                         [](pair<int, int> lhs, pair<int, int> rhs) {
                             return lhs.second < rhs.second;
                         })
            ->second;
    const int BOTTOM =
        std::max_element(this->layout_.begin(), this->layout_.end(),
                         [](pair<int, int> lhs, pair<int, int> rhs) {
                             return !(lhs.second < rhs.second);
                         })
            ->second;
    return TOP - BOTTOM + 1;
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
