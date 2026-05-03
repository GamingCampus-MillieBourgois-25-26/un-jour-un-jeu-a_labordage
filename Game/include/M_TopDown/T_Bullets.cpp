#include "pch.h"
#include "T_Bullets.h"

#include "Core/GameObject.h"
#include "WindowModule.h"

M_TopDown::Bullets::Bullets(const Maths::Vector2f& _direction, BulletOwner _owner, float _speed)
    : direction(_direction), speed(_speed), bulletOwner(_owner)
{
}

void M_TopDown::Bullets::Update(float _delta_time)
{
    Maths::Vector2f position = GetOwner()->GetPosition();
    position.x += direction.x * speed * _delta_time;
    position.y += direction.y * speed * _delta_time;

    GetOwner()->SetPosition(position);

    Maths::Vector2u window_size = GetModule<WindowModule>()->GetSize();
    if (position.x < -50.f || position.x > static_cast<float>(window_size.x) + 50.f ||
        position.y < -50.f || position.y > static_cast<float>(window_size.y) + 50.f)
    {
        GetOwner()->MarkForDeletion();
    }
}