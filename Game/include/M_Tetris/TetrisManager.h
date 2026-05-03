#pragma once

#include "Core/Component.h"

#include <SFML/Graphics/Color.hpp>
#include <string>

class TextRenderer;

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

        void CreateUI();
        void UpdateScoreText();
        void EndGame(const std::string& _message, sf::Color _color);

        Grid* grid = nullptr;
        Piece* currentPiece = nullptr;

        float gravityTimer = 0.f;
        float gravityInterval = 0.5f;
        float softDropInterval = 0.05f;

        bool gameOver = false;

      
        int totalLinesCleared = 0;
        TextRenderer* scoreText = nullptr;
        TextRenderer* resultText = nullptr;
    };
}