#pragma once

#include <array>
#include <utility>

namespace entity {

using std::array;
using std::pair;

using piece = array<pair<int, int>, 4>;

class Piece {
  public:
    Piece();

    piece GetLayout() const { return this->layout_; }
    piece *GetLayoutAddr() { return &this->layout_; }
    short GetColor() const { return this->color_; }

    void MoveLeft();
    void MoveRight();
    void MoveDown();

  private:
    piece layout_;
    short color_;
};

static constexpr int kNumLayouts = 7;
const array<piece, kNumLayouts> kLayouts = {{
    {{{1, 1}, {1, 2}, {1, 3}, {1, 4}}},
    {{{1, 1}, {1, 2}, {2, 2}, {2, 3}}},
    {{{2, 1}, {2, 2}, {1, 2}, {1, 3}}},
    {{{1, 1}, {1, 2}, {1, 3}, {2, 2}}},
    {{{1, 1}, {1, 2}, {1, 3}, {2, 1}}},
    {{{2, 1}, {2, 2}, {2, 3}, {1, 2}}},
    {{{1, 1}, {1, 2}, {2, 1}, {2, 2}}},
}};

} // namespace entity
