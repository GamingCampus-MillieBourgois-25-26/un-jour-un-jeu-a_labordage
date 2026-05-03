#pragma once

#include "Core/Component.h"

#include <SFML/Graphics/Color.hpp>
#include <string>
#include <vector>

class GameObject;
class TextRenderer;

namespace M_BulletHell
{
    class CollisionManager : public Component
    {
    public:
        void Start() override;
        void Update(float _delta_time) override;

        void SetSurvivalDuration(float _duration) { survivalDuration = _duration; }

        bool HasWon() const { return won; }
        bool IsGameOver() const { return gameOver; }

    private:
        void CreateUI();
        void UpdateTimerText();
        void EndGame(const std::string& _message, sf::Color _color);

        std::vector<GameObject*> bullets;

        float survivalDuration = 60.f;
        float elapsedTime = 0.f;
        int lastDisplayedSecond = -1;

        bool gameOver = false;
        bool won = false;

        TextRenderer* timerText = nullptr;
        TextRenderer* resultText = nullptr;
    };
}