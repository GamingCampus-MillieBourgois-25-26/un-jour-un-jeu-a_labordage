#pragma once

#include "Core/Component.h"
#include "Modules/InputModule.h"
#include "Core/GameObject.h"
#include "CollisionManager.h"


namespace Runner{

class Player : public Component
{
public:
    void Setspeed(float spee) { speed = spee; }

    bool isJump;
    void Update(const float _delta_time) override
    {
        

     
        Maths::Vector2<float> position = GetOwner()->GetPosition();
        


        if (InputModule::GetKey(sf::Keyboard::Key::Space))
        {
            isJump = true;
        }
        else isJump = false;
        
        

        if (InputModule::GetMouseButton(sf::Mouse::Button::Left)) {

        }

        GetOwner()->SetPosition(position);
    

        if (InputModule::GetKeyDown(sf::Keyboard::Key::Escape))
        {
            Engine::GetInstance()->RequestQuit();
        }
    }
    float speed = 100.f;
    
};

}