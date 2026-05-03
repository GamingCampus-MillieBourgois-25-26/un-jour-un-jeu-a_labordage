#include "pch.h"
#include "R_Level.h"

#include "Core/Scene.h"
#include "Engine.h"
#include "TextRenderer.h"

#include <iostream>

void Runner::R_Level::Start()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    CreateUI();
    UpdateScoreText();
}

void Runner::R_Level::CreateUI()
{
    Scene* scene = GetOwner()->GetScene();

    GameObject* score_go = scene->CreateGameObject("UI_Timer");
    score_go->SetPosition(Maths::Vector2f(10.f, 10.f));
    scoreText = score_go->CreateComponent<TextRenderer>("Score : 0s");
    scoreText->SetCharacterSize(28);
    scoreText->SetColor(sf::Color::White);

    GameObject* result_go = scene->CreateGameObject("UI_Result");
    result_go->SetPosition(Maths::Vector2f(140.f, 250.f));
    resultText = result_go->CreateComponent<TextRenderer>("");
    resultText->SetCharacterSize(50);
}

void Runner::R_Level::UpdateScoreText()
{
    if (scoreText == nullptr) return;

    const int seconds = static_cast<int>(elapsedTime);
    if (seconds == lastDisplayedSecond) return;

    scoreText->SetText("Score : " + std::to_string(seconds) + "s");
    lastDisplayedSecond = seconds;
}

void Runner::R_Level::EndGame(const std::string& _message, sf::Color _color)
{
    gameOver = true;
    if (resultText != nullptr)
    {
        
        resultText->SetText(_message + "\nScore : " + std::to_string(static_cast<int>(elapsedTime)) + "s");
        resultText->SetColor(_color);
    }
    std::cout << "[Runner] " << _message << " - Score : " << static_cast<int>(elapsedTime) << "s" << std::endl;
}

void Runner::R_Level::Update(float deltaTime)
{
    if (gameOver) return;

    GameObject* player = GetOwner()->GetScene()->FindGameObject("player");
    if (player == nullptr || player->IsMarkedForDeletion())
    {
        EndGame("GAME OVER", sf::Color::Red);
        return;
    }

    SquareCollider* player_col = player->GetComponent<SquareCollider>();

    
    elapsedTime += deltaTime;
    UpdateScoreText();

   
    for (auto it = m_obstacles.begin(); it != m_obstacles.end(); )
    {
        GameObject* obs = *it;

        if (obs == nullptr || obs->IsMarkedForDeletion())
        {
            it = m_obstacles.erase(it);
            continue;
        }

        
        Maths::Vector2f pos = obs->GetPosition();
        pos.x -= 200.f * deltaTime;
        obs->SetPosition(pos);

     
        if (pos.x < -100.f)
        {
            obs->MarkForDeletion();
            it = m_obstacles.erase(it);
            continue;
        }

    
        if (player_col != nullptr)
        {
            SquareCollider* obs_col = obs->GetComponent<SquareCollider>();
            if (obs_col != nullptr && SquareCollider::IsColliding(*player_col, *obs_col))
            {
                EndGame("GAME OVER", sf::Color::Red);
                player->MarkForDeletion();
                return;
            }
        }

        ++it;
    }


    if (m_cooldownTimer > 0.f)
    {
        m_cooldownTimer -= deltaTime;
    }
    else
    {
        float randomY = (rand() % 4 == 0) ? 500.f : 672.f;
        int count = 1 + rand() % 3;
        for (int i = 0; i < count; i++)
        {
            CreateObstacle1(GetOwner()->GetScene(), randomY, i);
        }
        m_cooldownTimer = 2.f + static_cast<float>(rand() % 4);
    }
}

void Runner::R_Level::CreateObstacle1(Scene* scene, float spawnY, int index)
{
    AssetsModule* assets = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
    if (!assets) return;

    Texture* obstacle1_texture = assets->LoadAsset<Texture>("fish_red.png");
    if (!obstacle1_texture) return;

    GameObject* obstacle1 = scene->CreateGameObject("obstacle1");
    obstacle1->SetScale(Maths::Vector2f(1, 1));
    obstacle1->SetPosition(Maths::Vector2f(1100.f + index * 64.f, spawnY));

    SpriteRenderer* render = obstacle1->CreateComponent<SpriteRenderer>(obstacle1_texture);
    obstacle1->CreateComponent<SquareCollider>(render);

    m_obstacles.push_back(obstacle1);
}