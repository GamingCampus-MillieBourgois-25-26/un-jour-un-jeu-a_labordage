#pragma once
#include "Core/Component.h"
#include "RectangleShapeRenderer.h"
#include "Maths/Vector2.h"


namespace BulletHell{

enum class BulletOwner {Player,Enemy};


class Bullet : public Component
{



public:


	Bullet(const Maths::Vector2f& _direction, RectangleShapeRenderer* _renderer, BulletOwner _owner = BulletOwner::Player, float _speed = 500.f);


	void Update(float _deltatime)override;


	BulletOwner GetBulletOwner() const { return bulletOwner; }


private:

	Maths::Vector2f direction;
	float speed;
	BulletOwner bulletOwner;
	RectangleShapeRenderer* rectangle = nullptr;
};

}