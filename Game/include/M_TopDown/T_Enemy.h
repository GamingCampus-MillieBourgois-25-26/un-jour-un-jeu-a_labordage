#pragma once

#include "Core/Component.h"
#include "Core/GameObject.h"
#include "Maths/Vector2.h"

#include <functional>

namespace M_TopDown
{
    class Enemy : public Component
    {
    public:
        using SpawnBulletFn = std::function<void(const Maths::Vector2f&, const Maths::Vector2f&)>;

        // _fireInterval : temps entre 2 tirs (3s par défaut)
        // _startupDelay : délai avant le 1er tir (utile pour pas tirer dès le spawn)
        Enemy(SpawnBulletFn _spawnFn, float _fireInterval = 3.f, float _startupDelay = 1.f);

        void Update(float _delta_time) override;

        bool IsDead() const { return dead; }
        void Kill()
        {
            dead = true;
            GetOwner()->MarkForDeletion();
        }

    private:
        SpawnBulletFn spawnBullet;

        float fireInterval;
        float fireTimer = 0.f;

        float startupDelay;
        float startupTimer = 0.f;

        bool dead = false;
    };
}