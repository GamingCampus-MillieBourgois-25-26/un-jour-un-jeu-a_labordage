#pragma once
#include "Core/Component.h"
#include "Maths/Vector2.h"

class SquareCollider;
class GameObject;

namespace Runner {
    class Player; // forward declaration, pas d'include

    class CollisionManager : public Component
    {
    public:
        bool isBackflipping = false;
        float currentRotation = 0.f;
        const float backflipSpeed = 720.f;
        void Start() override;
        void Update(float deltatime) override;

    private:
        SquareCollider* my_collider = nullptr;
        SquareCollider* obj_collider = nullptr;
        GameObject* obj = nullptr;
        Player* p = nullptr;
        GameObject* player;

        Maths::Vector2f velocity;
        Maths::Vector2f position;
        bool isOnGround = false;

        const float gravity = 500.f;
        const float jumpForce = -300.f; // négatif car Y vers le bas en SFML
    };
}