#pragma once

#include "Core/Component.h"
#include "Maths/Vector2.h"

namespace M_TopDown
{
    enum class BulletOwner { Player, Enemy };

    class Bullets : public Component
    {
    public:
        Bullets(const Maths::Vector2f& _direction, BulletOwner _owner = BulletOwner::Player, float _speed = 500.f);

        void Update(float _delta_time) override;

        BulletOwner GetBulletOwner() const { return bulletOwner; }

    private:
        Maths::Vector2f direction;
        float speed;
        BulletOwner bulletOwner;
    };
}