#include "pch.h"
#include "B_Collisionmanager.h"

#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "SquareCollider.h"
#include "TextRenderer.h"
#include "Bullets.h"
#include "Enemy.h"

#include <algorithm>
#include <cmath>
#include <iostream>

void M_BulletHell::CollisionManager::Start()
{
    Component::Start();
    CreateUI();
    UpdateTimerText();
}

void M_BulletHell::CollisionManager::CreateUI()
{
    Scene* scene = GetOwner()->GetScene();

    GameObject* timer_go = scene->CreateGameObject("UI_Timer");
    timer_go->SetPosition(Maths::Vector2f(10.f, 10.f));
    timerText = timer_go->CreateComponent<TextRenderer>("Temps : 60s");
    timerText->SetCharacterSize(28);
    timerText->SetColor(sf::Color::White);

    GameObject* result_go = scene->CreateGameObject("UI_Result");
    result_go->SetPosition(Maths::Vector2f(140.f, 250.f));
    resultText = result_go->CreateComponent<TextRenderer>("");
    resultText->SetCharacterSize(50);
}

void M_BulletHell::CollisionManager::UpdateTimerText()
{
    if (timerText == nullptr) return;

    const int remaining = std::max(0, static_cast<int>(std::ceil(survivalDuration - elapsedTime)));
    if (remaining == lastDisplayedSecond) return;

    timerText->SetText("Temps : " + std::to_string(remaining) + "s");
    timerText->SetColor(remaining <= 10 ? sf::Color::Red : sf::Color::White);
    lastDisplayedSecond = remaining;
}

void M_BulletHell::CollisionManager::EndGame(const std::string& _message, sf::Color _color)
{
    gameOver = true;
    if (resultText != nullptr)
    {
        resultText->SetText(_message);
        resultText->SetColor(_color);
    }
    std::cout << "[BulletHell] " << _message << std::endl;

    
    for (const auto& go : GetOwner()->GetScene()->GetGameObjects())
    {
        if (go->GetName() == "Enemy")
        {
            Enemy* enemy = go->GetComponent<Enemy>();
            if (enemy != nullptr) enemy->Kill();
        }
        else if (go->GetName() == "Bullet")
        {
            go->MarkForDeletion();
        }
    }
}

void M_BulletHell::CollisionManager::Update(float _delta_time)
{
    if (gameOver) return;

    GameObject* player = GetOwner();
    SquareCollider* player_collider = player->GetComponent<SquareCollider>();
    if (player_collider == nullptr) return;


    elapsedTime += _delta_time;
    UpdateTimerText();

    if (elapsedTime >= survivalDuration)
    {
        won = true;
        EndGame("VICTOIRE !", sf::Color::Yellow);
        return;
    }

   
    bullets.clear();
    for (const auto& go : player->GetScene()->GetGameObjects())
    {
        if (go->GetName() == "Bullet" && !go->IsMarkedForDeletion())
            bullets.push_back(go.get());
    }

    for (GameObject* bullet : bullets)
    {
        SquareCollider* bullet_collider = bullet->GetComponent<SquareCollider>();
        if (bullet_collider == nullptr) continue;

        Bullets* bullet_comp = bullet->GetComponent<Bullets>();
        if (bullet_comp != nullptr && bullet_comp->GetBulletOwner() != BulletOwner::Enemy)
            continue;

        if (SquareCollider::IsColliding(*player_collider, *bullet_collider))
        {
            EndGame("GAME OVER", sf::Color::Red);
            player->MarkForDeletion();
            return;
        }
    }
}