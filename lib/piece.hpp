#pragma once

#include <utility>
#include <vector>

namespace entity {

using std::pair;
using std::vector;

using tetramino = vector<pair<int, int>>;

static constexpr int kNumColors = 7;
static const vector<tetramino> kLayouts = {
    {{1, 1}, {1, 2}, {1, 3}, {1, 4}}, {{1, 1}, {1, 2}, {2, 2}, {2, 3}},
    {{2, 1}, {2, 2}, {1, 2}, {1, 3}}, {{1, 1}, {1, 2}, {1, 3}, {2, 2}},
    {{1, 1}, {1, 2}, {1, 3}, {2, 1}}, {{2, 1}, {2, 2}, {2, 3}, {1, 2}},
    {{1, 1}, {1, 2}, {2, 1}, {2, 2}}, {{1, 1}, {2, 1}, {3, 1}, {4, 1}},
    {{1, 1}, {2, 1}, {2, 2}, {3, 2}}, {{1, 2}, {2, 2}, {2, 1}, {3, 1}},
    {{1, 1}, {2, 1}, {3, 1}, {2, 2}}, {{1, 1}, {2, 1}, {3, 1}, {1, 2}},
    {{1, 2}, {2, 2}, {3, 2}, {2, 1}}, {{1, 1}, {1, 2}, {2, 1}, {2, 2}}};

class Piece {
  public:
    /// Constructors

    Piece();

    /// Getters

    tetramino GetLayout() const { return this->layout_; }
    tetramino *GetLayoutAddr() { return &this->layout_; }
    short GetColor() const { return this->color_; }
    int GetWidth() const;
    pair<int, int> GetTopLeft() const;
    tetramino GetInverseLayout() const {
        return kLayouts.at((this->index_ + kNumColors) % kLayouts.size());
    }

    /// Setters
    static void SetEdge(const pair<int, int> &node) { edge = node; }

    /// Actions

    void MoveLeft();
    void MoveRight();
    void MoveDown();

    bool Rotate(const pair<int, int> &start);

  private:
    inline static pair<int, int> edge;
    unsigned long index_;
    tetramino layout_;
    short color_;
};

} // namespace entity
