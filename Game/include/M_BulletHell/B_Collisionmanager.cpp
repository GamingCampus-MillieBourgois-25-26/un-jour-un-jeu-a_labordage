#include "pch.h"
#include "B_CollisionManager.h"

#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "SquareCollider.h"
#include "Bullets.h"
#include "Enemy.h"

#include <iostream>

void M_BulletHell::CollisionManager::Update(float _delta_time)
{
    // Si la partie est terminée (victoire ou défaite), on ne fait plus rien
    if (gameOver)
        return;

    GameObject* player = GetOwner();

    // --- Timer de survie ---
    elapsedTime += _delta_time;
    if (elapsedTime >= survivalDuration)
    {
        std::cout << "VICTOIRE ! Le joueur a survecu " << survivalDuration << " secondes !" << std::endl;

        // On parcourt la scène pour tuer l'enemy + nettoyer les bullets
        for (const auto& go : player->GetScene()->GetGameObjects())
        {
            if (go->GetName() == "Enemy")
            {
                Enemy* enemy = go->GetComponent<Enemy>();
                if (enemy != nullptr)
                    enemy->Kill();   // stoppe le tir + MarkForDeletion
            }
            else if (go->GetName() == "Bullet")
            {
                go->MarkForDeletion();
            }
        }

        won = true;
        gameOver = true;
        return;
    }

    SquareCollider* player_collider = player->GetComponent<SquareCollider>();
    if (player_collider == nullptr)
        return;

    // 1. Récupérer toutes les bullets de la scène
    bullets.clear();
    for (const auto& go : player->GetScene()->GetGameObjects())
    {
        if (go->GetName() == "Bullet" && !go->IsMarkedForDeletion())
        {
            bullets.push_back(go.get());
        }
    }

    // 2. Tester la collision avec le player
    for (GameObject* bullet : bullets)
    {
        SquareCollider* bullet_collider = bullet->GetComponent<SquareCollider>();
        if (bullet_collider == nullptr)
            continue;

        // On ne meurt que des bullets ennemies
        Bullets* bullet_comp = bullet->GetComponent<Bullets>();
        if (bullet_comp != nullptr && bullet_comp->GetBulletOwner() != BulletOwner::Enemy)
            continue;

        if (SquareCollider::IsColliding(*player_collider, *bullet_collider))
        {
            std::cout << "DEFAITE ! Le player a ete touche apres " << elapsedTime << " secondes." << std::endl;

            player->MarkForDeletion();
            bullet->MarkForDeletion();

            gameOver = true;
            return;
        }
    }
}