#pragma once
#include "Core/Component.h"
#include "InputModule.h"
#include "Bullet.h"
#include "RectangleShapeRenderer.h"
#include "BulletPool.h"
namespace Demo
{
    class Player : public Component
    {
    private:
        

        float fireCooldown = 0.f;
        float fireCooldownMax = 0.2f;
        BulletPool* bulletPool = nullptr;

    public:
        Maths::Vector2f angle;

        void Shoot()
        {
            GameObject* bulletGO = bulletPool->GetAvailable();
            if (!bulletGO) return;

            const float rad = GetOwner()->GetRotation().asRadians();
            Maths::Vector2f direction(std::cos(rad), std::sin(rad));

            bulletGO->SetPosition(GetOwner()->GetPosition());
            bulletGO->GetComponent<Bullet>()->SetDirection(direction);
            bulletGO->Enable();
        }

        void SetBulletPool(Demo::BulletPool* _pool)
        {
            bulletPool = _pool;
        }

        void Update(const float _delta_time) override
        {
            
            //shoot
            fireCooldown -= _delta_time;
            if (fireCooldown <= 0.f)
            {
                Shoot();
                fireCooldown = fireCooldownMax;
            }

            Maths::Vector2<float> position = GetOwner()->GetPosition();

            
            Maths::Vector2<float> center(position.x + 12.f, position.y + 12.f);

            Maths::Vector2i mouse_position = InputModule::GetMousePosition();
            Maths::Vector2<float> mouseFloat(
                static_cast<float>(mouse_position.x),
                static_cast<float>(mouse_position.y)
            );

            angle = mouseFloat - center; 

            if (angle.Magnitude() > 5.f)
            {
                float a = atan2(angle.y, angle.x);
                GetOwner()->SetRotation(sf::radians(a)); 
            }

           

            if (InputModule::GetKey(sf::Keyboard::Key::D))
            {
                position.x += speed * _delta_time;
            }
            if (InputModule::GetKey(sf::Keyboard::Key::Q))
            {
                position.x -= speed * _delta_time;
            }

            if (InputModule::GetKey(sf::Keyboard::Key::Z))
            {
                position.y -= speed * _delta_time;
            }
            if (InputModule::GetKey(sf::Keyboard::Key::S))
            {
                position.y += speed * _delta_time;
            }

            if (InputModule::GetMouseButton(sf::Mouse::Button::Left)) {

            }

            GetOwner()->SetPosition(position);
            

            if (InputModule::GetKeyDown(sf::Keyboard::Key::Escape))
            {
                Engine::GetInstance()->RequestQuit();
            }
        }

        void Start() override {
            SquareCollider* col = GetOwner()->CreateComponent<SquareCollider>();
            col->SetWidth(50.f);
            col->SetHeight(50.f);
        }

        float speed = 100.0f;
    };

}
