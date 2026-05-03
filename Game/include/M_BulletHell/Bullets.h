#pragma once
#include "Core/Component.h"
#include "RectangleShapeRenderer.h"
#include "Maths/Vector2.h"


namespace M_BulletHell {

	enum class BulletOwner { Player, Enemy };


	class Bullets : public Component
	{



	public:


		Bullets(const Maths::Vector2f& _direction, RectangleShapeRenderer* _renderer, BulletOwner _owner = BulletOwner::Player, float _speed = 500.f);


		void Update(float _deltatime)override;


		BulletOwner GetBulletOwner() const { return bulletOwner; }


	private:

		Maths::Vector2f direction;
		float speed;
		BulletOwner bulletOwner;
		RectangleShapeRenderer* rectangle = nullptr;
	};

}