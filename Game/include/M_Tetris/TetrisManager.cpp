#include "pch.h"
#include "TetrisManager.h"

#include "Grid.h"
#include "Piece.h"
#include "TetrominoData.h"

#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "InputModule.h"
#include "Engine.h"
#include "TextRenderer.h"

#include <chrono>
#include <iostream>
#include <random>

namespace
{
    int RandomInt(int _min, int _max)
    {
        thread_local std::mt19937_64 gen(static_cast<uint64_t>(
            std::chrono::steady_clock::now().time_since_epoch().count()));
        std::uniform_int_distribution<int> dist(_min, _max);
        return dist(gen);
    }
}

namespace Tetris
{
    void TetrisManager::Start()
    {
        Component::Start();
        CreateUI();
        UpdateScoreText();
        SpawnPiece();
    }

    void TetrisManager::CreateUI()
    {
        Scene* scene = GetOwner()->GetScene();

     
        GameObject* score_go = scene->CreateGameObject("UI_Timer");
        score_go->SetPosition(Maths::Vector2f(5.f, 10.f));
        scoreText = score_go->CreateComponent<TextRenderer>("Lignes : 0");
        scoreText->SetCharacterSize(20);
        scoreText->SetColor(sf::Color::White);

        // Result au centre de l'écran
        GameObject* result_go = scene->CreateGameObject("UI_Result");
        result_go->SetPosition(Maths::Vector2f(160.f, 250.f));
        resultText = result_go->CreateComponent<TextRenderer>("");
        resultText->SetCharacterSize(40);
    }

    void TetrisManager::UpdateScoreText()
    {
        if (scoreText == nullptr) return;
        scoreText->SetText("Lignes : " + std::to_string(totalLinesCleared));
    }

    void TetrisManager::EndGame(const std::string& _message, sf::Color _color)
    {
        gameOver = true;
        if (resultText != nullptr)
        {
            resultText->SetText(_message + "\nLignes : " + std::to_string(totalLinesCleared));
            resultText->SetColor(_color);
        }
        std::cout << "[Tetris] " << _message << " - Lignes : " << totalLinesCleared << std::endl;
    }

    void TetrisManager::Update(float _delta_time)
    {
        if (gameOver || grid == nullptr) return;

        if (currentPiece == nullptr)
        {
            const int cleared = grid->ClearCompletedLines();
            if (cleared > 0)
            {
                totalLinesCleared += cleared;
                UpdateScoreText();
                std::cout << "[Tetris] " << cleared << " ligne(s) cleared !" << std::endl;
            }
            SpawnPiece();
            return;
        }

        HandleInput();

        const bool soft_drop = InputModule::GetKey(sf::Keyboard::Key::S);
        const float interval = soft_drop ? softDropInterval : gravityInterval;

        gravityTimer += _delta_time;
        if (gravityTimer >= interval)
        {
            gravityTimer = 0.f;
            if (!currentPiece->TryFall())
            {
                currentPiece->Lock();
                currentPiece = nullptr;
            }
        }
    }

    void TetrisManager::HandleInput()
    {
        if (currentPiece == nullptr) return;

        if (InputModule::GetKeyDown(sf::Keyboard::Key::Q))
            currentPiece->TryMove(-1, 0);

        if (InputModule::GetKeyDown(sf::Keyboard::Key::D))
            currentPiece->TryMove(1, 0);

        if (InputModule::GetKeyDown(sf::Keyboard::Key::Space))
            currentPiece->TryRotate(1);

        if (InputModule::GetKeyDown(sf::Keyboard::Key::Z))
        {
            while (currentPiece->TryFall()) {  }
            currentPiece->Lock();
            currentPiece = nullptr;
        }

        if (InputModule::GetKeyDown(sf::Keyboard::Key::Escape))
            Engine::GetInstance()->RequestQuit();
    }

    void TetrisManager::SpawnPiece()
    {
        if (grid == nullptr) return;

        const TetrominoType random_type = static_cast<TetrominoType>(RandomInt(0, TETROMINO_COUNT - 1));

        const PieceData& data = TETROMINO_DATA[static_cast<int>(random_type)];
        const int spawn_col = (Grid::COLS / 2) - 2;
        const int spawn_row = 0;

        for (int i = 0; i < 4; ++i)
        {
            const int c = spawn_col + data.blocks[0][i].x;
            const int r = spawn_row + data.blocks[0][i].y;
            if (!grid->IsInBounds(c, r) || !grid->IsCellEmpty(c, r))
            {
                EndGame("GAME OVER", sf::Color::Red);
                return;
            }
        }

        Scene* scene = GetOwner()->GetScene();
        GameObject* piece_go = scene->CreateGameObject("Piece");
        currentPiece = piece_go->CreateComponent<Piece>(random_type, grid);
    }
}