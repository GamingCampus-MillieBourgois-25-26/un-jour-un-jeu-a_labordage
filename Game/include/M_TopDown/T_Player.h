#pragma once

#include "Core/Component.h"
#include "Modules/InputModule.h"
#include "Core/GameObject.h"
#include "Engine.h"

#include "Maths/Vector2.h"
#include <functional>

namespace M_TopDown
{
    class Player : public Component
    {
    public:
        using SpawnBulletFn = std::function<void(const Maths::Vector2f&, const Maths::Vector2f&)>;

        explicit Player(SpawnBulletFn _spawnFn) : spawnBullet(std::move(_spawnFn)) {}

        void Update(const float _delta_time) override
        {
            Maths::Vector2<float> position = GetOwner()->GetPosition();

        
            if (InputModule::GetKey(sf::Keyboard::Key::D)) position.x += speed * _delta_time;
            if (InputModule::GetKey(sf::Keyboard::Key::Q)) position.x -= speed * _delta_time;
            if (InputModule::GetKey(sf::Keyboard::Key::Z)) position.y -= speed * _delta_time;
            if (InputModule::GetKey(sf::Keyboard::Key::S)) position.y += speed * _delta_time;

            GetOwner()->SetPosition(position);

        
            if (InputModule::GetKeyDown(sf::Keyboard::Key::Escape))
            {
                Engine::GetInstance()->RequestQuit();
            }

         
            fireTimer += _delta_time;
            if (InputModule::GetMouseButton(sf::Mouse::Button::Left) && fireTimer >= fireRate)
            {
                fireTimer = 0.f;

                const auto mouse_int = InputModule::GetMousePosition();
                const Maths::Vector2f mouse_pos(static_cast<float>(mouse_int.x), static_cast<float>(mouse_int.y));

                Maths::Vector2f dir = mouse_pos - position;
                if (dir.MagnitudeSquared() > 0.0001f)
                {
                    dir = dir.Normalize();
                    if (spawnBullet)
                        spawnBullet(position, dir);
                }
            }
        }

        void SetFireRate(float _rate) { fireRate = _rate; }
        void SetSpeed(float _speed) { speed = _speed; }

    private:
        SpawnBulletFn spawnBullet;

        float speed = 250.f;
        float fireRate = 0.2f;  
        float fireTimer = 0.f;
    };
}