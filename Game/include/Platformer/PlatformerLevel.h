#pragma once

#include "Core/Component.h"

#include <SFML/Graphics/Color.hpp>
#include <string>

class TextRenderer;

namespace Platformer
{
    class PlatformerLevel : public Component
    {
    public:
        void Start() override;
        void Update(float _delta_time) override;

        void SetTimeLimit(float _seconds) { timeLimit = _seconds; }
        bool HasWon() const { return won; }
        bool IsGameOver() const { return gameOver; }

    private:
        void CreateUI();
        void UpdateTimerText();
        void EndGame(const std::string& _message, sf::Color _color);

        float elapsed = 0.f;
        float timeLimit = 60.f;
        int lastDisplayedSecond = -1;

        bool won = false;
        bool gameOver = false;

        TextRenderer* timerText = nullptr;
        TextRenderer* resultText = nullptr;
    };
}