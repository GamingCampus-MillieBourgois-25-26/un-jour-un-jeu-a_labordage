#pragma once
#include "Core/Component.h"
#include "Maths/Vector2.h"
#include <vector>

class SquareCollider;
class GameObject;

namespace Platformer {
    
    class Playere;
    class CollisionManagere : public Component
    {
    public:
        bool isBackflipping = false;
        float currentRotation = 0.f;
        const float backflipSpeed = 720.f;
        void Start() override;
        void Update(float deltatime) override;
        std::vector<GameObject*> sol;
     
    private:
        SquareCollider* my_collider = nullptr;
        SquareCollider* obj_collider = nullptr;
        GameObject* obj = nullptr;
        Playere* p = nullptr;
        GameObject* player;
        
       
        Maths::Vector2f position;
        bool isOnGround = false;

        const float gravity = 500.f;
        const float jumpForce = -300.f; // négatif car Y vers le bas en SFML
    };
}