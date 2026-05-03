#include "pch.h"
#include "PlatformerLevel.h"

#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "SquareCollider.h"
#include "TextRenderer.h"

#include <algorithm>
#include <cmath>
#include <iostream>

void Platformer::PlatformerLevel::Start()
{
    Component::Start();
    elapsed = 0.f;

    CreateUI();
    UpdateTimerText();

    std::cout << "[Platformer] Tu as " << timeLimit
        << " secondes pour atteindre le drapeau jaune !" << std::endl;
}

void Platformer::PlatformerLevel::CreateUI()
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

void Platformer::PlatformerLevel::UpdateTimerText()
{
    if (timerText == nullptr) return;

    const int remaining = std::max(0, static_cast<int>(std::ceil(timeLimit - elapsed)));
    if (remaining == lastDisplayedSecond) return;

    timerText->SetText("Temps : " + std::to_string(remaining) + "s");

   
    if (remaining <= 10)
        timerText->SetColor(sf::Color::Red);
    else
        timerText->SetColor(sf::Color::White);

    lastDisplayedSecond = remaining;
}

void Platformer::PlatformerLevel::EndGame(const std::string& _message, sf::Color _color)
{
    gameOver = true;
    if (resultText != nullptr)
    {
        resultText->SetText(_message);
        resultText->SetColor(_color);
    }
    std::cout << "[Platformer] " << _message << std::endl;
}

void Platformer::PlatformerLevel::Update(float _delta_time)
{
    if (gameOver) return;

    Scene* scene = GetOwner()->GetScene();
    GameObject* player = scene->FindGameObject("player");


    if (player == nullptr || player->IsMarkedForDeletion())
    {
        EndGame("GAME OVER", sf::Color::Red);
        return;
    }

   
    if (player->GetPosition().y > 800.f)
    {
        player->MarkForDeletion();
        EndGame("GAME OVER", sf::Color::Red);
        return;
    }


    elapsed += _delta_time;
    UpdateTimerText();

    if (elapsed >= timeLimit)
    {
        EndGame("TEMPS ECOULE", sf::Color::Red);
        return;
    }

  
    GameObject* goal = scene->FindGameObject("goal");
    if (goal == nullptr) return;

    SquareCollider* player_col = player->GetComponent<SquareCollider>();
    SquareCollider* goal_col = goal->GetComponent<SquareCollider>();
    if (player_col == nullptr || goal_col == nullptr) return;

    if (SquareCollider::IsColliding(*player_col, *goal_col))
    {
        won = true;
        EndGame("VICTOIRE !", sf::Color::Yellow);
    }
}