#pragma once

#include "Core/Component.h"
#include <SFML/Graphics/Color.hpp>
#include <string>
#include <vector>

#include "RectangleShapeRenderer.h"
#include "GameObject.h"
#include "Asset.h"
#include "Texture.h"
#include "AssetsModule.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"

class TextRenderer;

namespace Runner
{
    class R_Level : public Component
    {
    private:
        float x = 1100;
        float m_cooldownTimer = 0.f;
        const float COOLDOWN_DURATION = 10.f;
        std::vector<GameObject*> m_obstacles;

      
        float elapsedTime = 0.f;
        int lastDisplayedSecond = -1;
        bool gameOver = false;

        TextRenderer* scoreText = nullptr;
        TextRenderer* resultText = nullptr;

        void CreateUI();
        void UpdateScoreText();
        void EndGame(const std::string& _message, sf::Color _color);

    public:
        virtual void Start() override;
        virtual void Update(float deltaTime) override;
        void CreateObstacle1(Scene* scene, float spawnY = 500.f, int index = 0);
    };
}