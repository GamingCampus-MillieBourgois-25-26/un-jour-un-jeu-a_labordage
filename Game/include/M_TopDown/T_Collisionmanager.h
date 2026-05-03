#pragma once

#include "Core/Component.h"
#include <vector>

class GameObject;

namespace M_TopDown
{
    class CollisionManager : public Component
    {
    public:
        void Update(float _delta_time) override;

        bool HasWon() const { return won; }
        bool IsGameOver() const { return gameOver; }

    private:
        bool gameOver = false;
        bool won = false;

        // Garde la trace : on a déjà vu au moins un enemy → permet la détection "tous morts"
        bool everSawEnemies = false;

        std::vector<GameObject*> bullets;
        std::vector<GameObject*> enemies;
    };
}