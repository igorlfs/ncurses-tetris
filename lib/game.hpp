#pragma once

#include "logic.hpp"
#include "window.hpp"
#include <vector>

static constexpr int kQuit{static_cast<int>('x')};
static constexpr int kAction{static_cast<int>(' ')};

namespace game {

using std::pair;

class Game {
  public:
    /// Constructors
    explicit Game(pair<WINDOW *, WINDOW *> windows);

    /// Getters
    bool IsGameOver() const { return this->gameOver_; }

    /// Operations

    /// @brief reads user input
    void ReadInput();

    /// @brief update game based on input
    void Update();

    /// @brief print changes in memory to screen
    void Print() const;

    /// @brief print exit message
    void Quit() const;

  private:
    bool gameOver_{false};
    int input_;
    int score_{0};
    Window grid_;
    Window scoreWindow_;
    logic::Logic gate_;
};

} // namespace game
