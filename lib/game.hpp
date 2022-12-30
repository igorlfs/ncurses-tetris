#pragma once

#include "board.hpp"
#include "logic.hpp"
#include <vector>

static constexpr int kQuit{static_cast<int>('x')};
static constexpr int kAction{static_cast<int>(' ')};

namespace game {

class Game {
  public:
    /// Constructors
    explicit Game(WINDOW *win);

    /// Getters
    bool IsGameOver() const { return this->gameOver_; }

    /// Operations

    /// @brief reads user input
    void ReadInput();

    /// @brief update game based on input
    void Update();

    /// @brief print changes in memory to screen
    void Print() const;

  private:
    bool gameOver_{false};
    int input_;
    Board grid_;
    logic::Logic gate_;
};

} // namespace game
