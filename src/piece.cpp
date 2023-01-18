#include "piece.hpp"
#include "random.hpp"
#include <algorithm>

entity::Piece::Piece() {
    this->index_ = Random::Rng(0, kLayouts.size() - 1);
    this->layout_ = kLayouts.at(this->index_);
    this->color_ = static_cast<short>(this->index_ % kNumColors + 1);
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

entity::pair<int, int> entity::Piece::GetTopLeft() const {
    return *std::min_element(
        this->layout_.begin(), this->layout_.end(),
        [](const pair<int, int> &lhs, const pair<int, int> &rhs) {
            return lhs.first < rhs.first ||
                   (lhs.first == rhs.first && lhs.second < rhs.second);
        });
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

bool entity::Piece::Rotate(const pair<int, int> &start) {
    entity::tetramino *layout = GetLayoutAddr();
    const entity::tetramino INVERSE_LAYOUT = GetInverseLayout();

    uint index = 0;
    for (auto &part : *layout) {
        part.first = start.first - 1 + INVERSE_LAYOUT[index].first;
        part.second = start.second - 1 + INVERSE_LAYOUT[index].second;
        if (part.first > edge.first || part.second > edge.second) {
            return true;
        }
        index++;
    }

    this->index_ = (this->index_ + kNumColors) % kLayouts.size();
    return false;
}
