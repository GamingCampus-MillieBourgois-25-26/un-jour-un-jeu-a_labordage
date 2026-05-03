#include "pch.h"
#include "T_Collisionmanager.h"

#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "SquareCollider.h"
#include "TextRenderer.h"
#include "T_Bullets.h"
#include "T_Enemy.h"

#include <iostream>

void M_TopDown::CollisionManager::Start()
{
    Component::Start();
    CreateUI();
    UpdateTimerText();
}

void M_TopDown::CollisionManager::CreateUI()
{
    Scene* scene = GetOwner()->GetScene();

    GameObject* timer_go = scene->CreateGameObject("UI_Timer");
    timer_go->SetPosition(Maths::Vector2f(10.f, 10.f));
    timerText = timer_go->CreateComponent<TextRenderer>("Temps : 0s");
    timerText->SetCharacterSize(28);
    timerText->SetColor(sf::Color::White);

    GameObject* result_go = scene->CreateGameObject("UI_Result");
    result_go->SetPosition(Maths::Vector2f(140.f, 250.f));
    resultText = result_go->CreateComponent<TextRenderer>("");
    resultText->SetCharacterSize(50);
}

void M_TopDown::CollisionManager::UpdateTimerText()
{
    if (timerText == nullptr) return;

    const int seconds = static_cast<int>(elapsedTime);
    if (seconds == lastDisplayedSecond) return;

    timerText->SetText("Temps : " + std::to_string(seconds) + "s");
    lastDisplayedSecond = seconds;
}

void M_TopDown::CollisionManager::EndGame(const std::string& _message, sf::Color _color)
{
    gameOver = true;
    if (resultText != nullptr)
    {
        resultText->SetText(_message);
        resultText->SetColor(_color);
    }
    std::cout << "[TopDown] " << _message << std::endl;

    
    for (const auto& go : GetOwner()->GetScene()->GetGameObjects())
    {
        if (go->GetName() == "Enemy" || go->GetName() == "Bullet")
            go->MarkForDeletion();
    }
}

void M_TopDown::CollisionManager::Update(float _delta_time)
{
    if (gameOver) return;

    GameObject* player = GetOwner();
    SquareCollider* player_collider = player->GetComponent<SquareCollider>();
    if (player_collider == nullptr) return;

    
    elapsedTime += _delta_time;
    UpdateTimerText();

    bullets.clear();
    enemies.clear();
    for (const auto& go : player->GetScene()->GetGameObjects())
    {
        if (go->IsMarkedForDeletion()) continue;
        const std::string& name = go->GetName();
        if (name == "Bullet")     bullets.push_back(go.get());
        else if (name == "Enemy") enemies.push_back(go.get());
    }

    if (!enemies.empty()) everSawEnemies = true;

    
    if (everSawEnemies && enemies.empty())
    {
        won = true;
        EndGame("VICTOIRE !", sf::Color::Yellow);
        return;
    }

   
    for (GameObject* bullet : bullets)
    {
        SquareCollider* bullet_collider = bullet->GetComponent<SquareCollider>();
        if (bullet_collider == nullptr) continue;

        Bullets* bullet_comp = bullet->GetComponent<Bullets>();
        if (bullet_comp == nullptr) continue;

        if (bullet_comp->GetBulletOwner() == BulletOwner::Enemy)
        {
            
            if (SquareCollider::IsColliding(*player_collider, *bullet_collider))
            {
                EndGame("GAME OVER", sf::Color::Red);
                player->MarkForDeletion();
                return;
            }
        }
        else
        {
           
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
                    std::cout << "[TopDown] Enemy elimine !" << std::endl;
                    break;
                }
            }
        }
    }
}