#pragma once
#include "Core/Component.h"
#include "InputModule.h"
#include "Bullet.h"
#include "RectangleShapeRenderer.h"
#include "SquareCollider.h"
namespace BulletHell
{
    class Player : public Component
    {
    private:
        

    public:
        Maths::Vector2f angle;

       

        void Update(const float _delta_time) override
        {
            
            

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
            Component::Start();
            SquareCollider* col = GetOwner()->CreateComponent<SquareCollider>();
            SpriteRenderer* sr = GetOwner()->GetComponent<SpriteRenderer>();
            col->SetWidth(40.f);
            col->SetHeight(40.f);
            col->SetPivot(sr->GetSize());

            if (sr)
                sr->SetPivot(sr->GetSize() / 2.f);
        }

        float speed = 150.0f;
    };

}
