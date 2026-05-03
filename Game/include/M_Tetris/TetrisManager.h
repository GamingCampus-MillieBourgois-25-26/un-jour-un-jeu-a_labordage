#pragma once

#include "Core/Component.h"

namespace Tetris
{
    class Grid;
    class Piece;

    class TetrisManager : public Component
    {
    public:
        void SetGrid(Grid* _grid) { grid = _grid; }

        void Start() override;
        void Update(float _delta_time) override;

        bool IsGameOver() const { return gameOver; }

    private:
        void SpawnPiece();
        void HandleInput();

        Grid* grid = nullptr;
        Piece* currentPiece = nullptr;

        float gravityTimer = 0.f;
        float gravityInterval = 0.5f;     // 1 case toutes les 0.5s
        float softDropInterval = 0.05f;   // accelere quand S est tenu

        bool gameOver = false;
    };
}
