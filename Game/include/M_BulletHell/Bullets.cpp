#include "pch.h"
#include "Bullets.h"
#include "GameObject.h"
#include "WindowModule.h"

M_BulletHell::Bullets::Bullets(const Maths::Vector2f& _direction, RectangleShapeRenderer* _renderer, BulletOwner _owner, float _speed)
    :direction(_direction), speed(_speed), bulletOwner(_owner), rectangle(_renderer)
{

}


void M_BulletHell::Bullets::Update(float _deltatime) {


    Maths::Vector2f position = GetOwner()->GetPosition();
    position.x += direction.x * speed * _deltatime;
    position.y += direction.y * speed * _deltatime;

    GetOwner()->SetPosition(position);

    Maths::Vector2u windowsize = GetModule<WindowModule>()->GetSize();
    if (position.x < 0.f || position.x > static_cast<float>(windowsize.x) ||
        position.y < 0.f || position.y > static_cast<float>(windowsize.y))
    {
        GetOwner()->MarkForDeletion();
    }

}