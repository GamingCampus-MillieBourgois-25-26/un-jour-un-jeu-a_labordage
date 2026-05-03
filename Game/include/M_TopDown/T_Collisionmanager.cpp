#include "pch.h"
#include "T_CollisionManager.h"

#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "SquareCollider.h"
#include "T_Bullets.h"
#include "T_Enemy.h"

#include <iostream>

void M_TopDown::CollisionManager::Update(float _delta_time)
{
    if (gameOver) return;

    GameObject* player = GetOwner();
    SquareCollider* player_collider = player->GetComponent<SquareCollider>();
    if (player_collider == nullptr) return;

    // 1. Récupérer toutes les bullets et tous les enemies de la scène
    bullets.clear();
    enemies.clear();
    for (const auto& go : player->GetScene()->GetGameObjects())
    {
        if (go->IsMarkedForDeletion()) continue;

        const std::string& name = go->GetName();
        if (name == "Bullet")        bullets.push_back(go.get());
        else if (name == "Enemy")    enemies.push_back(go.get());
    }

    if (!enemies.empty())
        everSawEnemies = true;

    // 2. Condition de victoire : on a vu des enemies, et il n'en reste plus
    if (everSawEnemies && enemies.empty())
    {
        std::cout << "VICTOIRE ! Tous les enemies ont ete elimines !" << std::endl;
        won = true;
        gameOver = true;

        // Nettoyer les bullets restantes
        for (GameObject* b : bullets)
            b->MarkForDeletion();

        return;
    }

    // 3. Traiter les collisions de chaque bullet
    for (GameObject* bullet : bullets)
    {
        SquareCollider* bullet_collider = bullet->GetComponent<SquareCollider>();
        if (bullet_collider == nullptr) continue;

        Bullets* bullet_comp = bullet->GetComponent<Bullets>();
        if (bullet_comp == nullptr) continue;

        if (bullet_comp->GetBulletOwner() == BulletOwner::Enemy)
        {
            // Bullet enemy → check vs player
            if (SquareCollider::IsColliding(*player_collider, *bullet_collider))
            {
                std::cout << "DEFAITE ! Le player a ete touche." << std::endl;

                player->MarkForDeletion();
                bullet->MarkForDeletion();

                gameOver = true;
                return;
            }
        }
        else // BulletOwner::Player
        {
            // Bullet player → check vs chaque enemy
            for (GameObject* enemy : enemies)
            {
                if (enemy->IsMarkedForDeletion()) continue;

                SquareCollider* enemy_collider = enemy->GetComponent<SquareCollider>();
                if (enemy_collider == nullptr) continue;

                if (SquareCollider::IsColliding(*enemy_collider, *bullet_collider))
                {
                    Enemy* enemy_comp = enemy->GetComponent<Enemy>();
                    if (enemy_comp != nullptr) enemy_comp->Kill();
                    else                        enemy->MarkForDeletion();

                    bullet->MarkForDeletion();
                    std::cout << "Enemy elimine !" << std::endl;
                    break; // une bullet ne tue qu'un seul enemy
                }
            }
        }
    }
}