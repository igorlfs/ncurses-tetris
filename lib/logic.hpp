#pragma once

#include "piece.hpp"
#include <map>

namespace logic {

using std::map;
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
    static void ClearRows(const int &row, entity::tetramino *layout);
    static void PushDown(const int &row, entity::tetramino *layout);
    int Tetris();

  private:
    int height_;
    int width_;
    entity::Piece newPos_;
    entity::Piece currentPiece_;
    bool hasCollided_{false};
    bool lateralCollision_{false};
    unsigned scoreMultiplier_{0};
    const map<unsigned, int> K_SCORE_MAP = {
        {0, 0}, {1, 40}, {2, 100}, {3, 300}, {4, 1200}};
    Pieces previousPieces_;
};
} // namespace logic
