#pragma once

#include "Core/Component.h"
#include <vector>

class GameObject;
class SquareCollider;

namespace M_BulletHell
{
    class CollisionManager : public Component
    {
    public:
        void Update(float _delta_time) override;

        // Permet de configurer la durée de survie nécessaire pour gagner
        void SetSurvivalDuration(float _duration) { survivalDuration = _duration; }

        bool HasWon() const { return won; }
        bool IsGameOver() const { return gameOver; }

    private:
        std::vector<GameObject*> bullets;

        float survivalDuration = 60.f;  // 1 minute par défaut
        float elapsedTime = 0.f;

        bool gameOver = false;
        bool won = false;
    };
}