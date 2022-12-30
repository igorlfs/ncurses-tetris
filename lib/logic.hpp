#pragma once

#include "piece.hpp"

namespace logic {

using std::pair;
using std::vector;

using Pieces = vector<entity::Piece>;

class Logic {
  public:
    /// Constructors

    explicit Logic(const pair<int, int> &dimensions)
        : height_(dimensions.second), width_(dimensions.first) {
        GeneratePiece();
    };

    /// Getters

    entity::Piece GetCurrent() const { return this->currentPiece_; };
    entity::tetramino *GetCurrentLayout() {
        return this->currentPiece_.GetLayoutAddr();
    }
    Pieces GetPrevious() const { return this->previousPieces_; }
    bool GetGravity() const { return this->hasCollided_; }
    bool GetLateral() const { return this->lateralCollision_; }

    /// Actions

    void ResetCollision();

    bool GeneratePiece();

    void Place() { this->previousPieces_.push_back(this->currentPiece_); };
    void PlaceDown();
    void Replace() { this->currentPiece_ = this->newPos_; }

    bool CheckCollision(const bool &lateral = false);

    bool MoveDown();
    void MoveLeft();
    void MoveRight();

    vector<unsigned> CheckTetris();
    void Tetris();
    static void ClearRows(const int &row, entity::tetramino *layout);
    static void PushDown(const int &row, entity::tetramino *layout);

  private:
    int height_;
    int width_;
    entity::Piece newPos_;
    entity::Piece currentPiece_;
    bool hasCollided_{false};
    bool lateralCollision_{false};
    Pieces previousPieces_;
};
} // namespace logic
