#pragma once
#include "Core/Component.h"
#include "Demo/Bullet.h"
#include "RectangleShapeRenderer.h"

namespace Demo
{
    class BulletPool : public Component
    {
    public:
        static constexpr int POOL_SIZE = 100;

        void CreateBullets(Scene* _scene)
        {
            for (int i = 0; i < POOL_SIZE; i++)
            {
                GameObject* bulletGO = _scene->CreateGameObject("Bullet");
                bulletGO->Disable();

                bulletGO->CreateComponent<Bullet>();
                RectangleShapeRenderer* rect = bulletGO->CreateComponent<RectangleShapeRenderer>();
                rect->SetSize(Maths::Vector2f(8.f, 8.f));
                rect->SetColor(sf::Color::Yellow);
                bulletGO->SetPosition(Maths::Vector2f(-10, -10));

                pool.push_back(bulletGO);
            }
        }

        GameObject* GetAvailable()
        {
            for (GameObject* go : pool)
            {
                if (!go->IsEnabled())
                    return go;
            }
            return nullptr;
        }

    private:
        std::vector<GameObject*> pool;
    };
}