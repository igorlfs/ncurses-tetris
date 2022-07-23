#pragma once

#include "piece.hpp"
#include <array>
#include <vector>

namespace logic {

// using std::array;
// using std::pair;
using std::vector;

using Pieces = vector<entity::Piece>;

class Logic {
  public:
    bool GeneratePiece();

    entity::Piece GetCurrent() const { return this->currentPiece_; };
    entity::piece *GetCurrentLayout() {
        return this->currentPiece_.GetLayoutAddr();
    }
    Pieces GetLegacy() const { return this->legacyPieces_; }
    bool GetGravity() const { return this->hasCollided_; }
    bool GetLateral() const { return this->lateralCollision_; }
    void ResetCollision();

    void Place() { this->legacyPieces_.push_back(this->currentPiece_); };
    void Replace() { this->currentPiece_ = this->newPos_; }

    bool CheckCollision(const bool &lateral = false);

    bool MoveDown(const int &height);
    void MoveLeft();
    void MoveRight(const int &width);

  private:
    entity::Piece newPos_;
    entity::Piece currentPiece_;
    bool hasCollided_{false};
    bool lateralCollision_{false};
    Pieces legacyPieces_;
};
} // namespace logic
