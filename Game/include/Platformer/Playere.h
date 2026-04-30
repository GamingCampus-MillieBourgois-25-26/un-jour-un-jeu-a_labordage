#pragma once

#include "Core/Component.h"
#include "Modules/InputModule.h"
#include "Core/GameObject.h"
#include "CollisionManagere.h"


namespace Platformer {

    class Playere : public Component
    {

    public:

        Maths::Vector2<float> positione;
        Maths::Vector2f velocity;
        

        void Setspeed(float spee) { speed = spee; }

        bool isJump;
        bool left;
        bool right;
        void Update(const float _delta_time) override
        {


            




            if (InputModule::GetKey(sf::Keyboard::Key::Space))
            {
                isJump = true;

            }
            else isJump = false;




            if (InputModule::GetKey(sf::Keyboard::Key::D))
            {
                positione.x += velocity.x + speed * _delta_time;
                right = true;
            }
            else right = false;
            if (InputModule::GetKey(sf::Keyboard::Key::Q))
            {
                positione.x -= velocity.x + speed * _delta_time;
                left = true;
            }
            else left = false;

           

          


            if (InputModule::GetKeyDown(sf::Keyboard::Key::Escape))
            {
                Engine::GetInstance()->RequestQuit();
            }
        }
        float speed = 200.f;

    };

}