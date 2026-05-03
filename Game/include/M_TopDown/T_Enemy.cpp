#include "pch.h"
#include "T_Enemy.h"

#include "Core/Scene.h"
#include "Core/GameObject.h"

M_TopDown::Enemy::Enemy(SpawnBulletFn _spawnFn, float _fireInterval, float _startupDelay)
    : spawnBullet(std::move(_spawnFn)), fireInterval(_fireInterval), startupDelay(_startupDelay)
{
}

void M_TopDown::Enemy::Update(float _delta_time)
{
    if (dead) return;

    // Petit délai initial pour ne pas tirer immédiatement
    if (startupTimer < startupDelay)
    {
        startupTimer += _delta_time;
        return;
    }

    fireTimer += _delta_time;
    if (fireTimer < fireInterval) return;
    fireTimer = 0.f;

    // Trouver le player dans la scène
    GameObject* player = GetOwner()->GetScene()->FindGameObject("Player");
    if (player == nullptr || player->IsMarkedForDeletion())
        return;

    // Direction = (player - enemy) normalisée
    const Maths::Vector2f my_pos = GetOwner()->GetPosition();
    const Maths::Vector2f player_pos = player->GetPosition();

    Maths::Vector2f dir = player_pos - my_pos;
    if (dir.MagnitudeSquared() < 0.0001f) return;

    dir = dir.Normalize();

    if (spawnBullet)
        spawnBullet(my_pos, dir);
}