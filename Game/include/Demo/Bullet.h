#pragma once
#include "Core/Component.h"
#include "Maths/Vector2.h"
#include "Core/GameObject.h"
#include "Components/RectangleShapeRenderer.h"

namespace Demo {
    class Bullet : public Component {
    public:
        void SetDirection(const Maths::Vector2f& _dir) { direction = _dir; }
        void SetSpeed(float _speed) { speed = _speed; }

        void Start() override {
            SquareCollider* col = GetOwner()->CreateComponent<SquareCollider>();
            col->SetWidth(10.f);
            col->SetHeight(10.f);
            RectangleShapeRenderer* rect = GetOwner()->GetComponent<RectangleShapeRenderer>();
            if (rect)
                rect->SetPivot(rect->GetSize() / 2.f);
        }

        void OnEnable() override
        {
            distanceTraveled = 0.f;
        }

        void Update(const float _delta_time) override
        {
            if (!IsEnabled()) return;

            Maths::Vector2f position = GetOwner()->GetPosition();
            position += direction * speed * _delta_time;
            GetOwner()->SetPosition(position);

            distanceTraveled += speed * _delta_time;
            if (distanceTraveled > maxDistance)
                GetOwner()->Disable();
        }

    private:
        Maths::Vector2f direction;
        float speed = 400.f;
        float distanceTraveled = 0.f;
        float maxDistance = 600.f;
    };
}