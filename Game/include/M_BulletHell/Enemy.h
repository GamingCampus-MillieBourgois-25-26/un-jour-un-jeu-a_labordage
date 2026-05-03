#pragma once
#include "Core/Component.h"
#include "GameObject.h"
#include "SquareCollider.h"
#include "Maths/Vector2.h"
#include <functional>
#include <vector>
#include <cmath>

struct EnemyBulletSpawnRequest
{
	Maths::Vector2f position;
	Maths::Vector2f direction;
};


namespace M_BulletHell {

	class Enemy : public Component
	{

	public:
		using SpawnBulletFn = std::function<void(const Maths::Vector2f&, const Maths::Vector2f&)>;

		Enemy(float _fireInterval, SpawnBulletFn _spawnFn, float _startupDelay = 3.f);

		void Update(float _deltatime)override;

		void SetCollider(SquareCollider* _col) { collider = _col; }
		SquareCollider GetCollider() const { return *collider; }

		std::vector<EnemyBulletSpawnRequest> FlushBullet() const {
			std::vector<EnemyBulletSpawnRequest> out = std::move(pendingBullets);
			pendingBullets.clear();
			return out;
		}


		bool isDead() const { return dead; }
		void Kill() {
			dead = true;
			GetOwner()->MarkForDeletion();
		}
	private:

		void FireCircle(int _count, float);
		void FireSpira(int _count);

		SpawnBulletFn spawnBullet;

		float fireInterval;
		float fireTimer = 0.f;
		float spireAngle = 0.f;
		int patternStep = 0;

	
		float startupDelay;
		float startupTimer = 0.f;

		bool dead = false;

		SquareCollider* collider = nullptr;

		mutable std::vector<EnemyBulletSpawnRequest> pendingBullets;

		static constexpr float PI = 3.14159265f;

	};

}