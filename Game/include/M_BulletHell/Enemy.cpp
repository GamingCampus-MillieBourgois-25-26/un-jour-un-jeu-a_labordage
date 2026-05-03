#include "pch.h"
#include "Enemy.h"
#include "GameObject.h"

M_BulletHell::Enemy::Enemy(float _fireinterval, SpawnBulletFn _spawnFn, float _startupDelay)
	: spawnBullet(std::move(_spawnFn)), fireInterval(_fireinterval), startupDelay(_startupDelay)
{
}

void M_BulletHell::Enemy::Update(float _deltatime) {
	if (dead) return;


	if (startupTimer < startupDelay)
	{
		startupTimer += _deltatime;
		return;
	}

	fireTimer += _deltatime;

	if (fireTimer <= fireInterval) return;

	fireTimer = 0.f;


	if (patternStep < 20)
	{
		FireCircle(16, patternStep * (PI / 32.f));
	}
	else if (patternStep < 40)
	{
		FireCircle(8, spireAngle);
		FireCircle(8, spireAngle);
		spireAngle += PI / 16.f;

	}
	else if (patternStep < 60)
	{
		FireCircle(3, spireAngle);
		spireAngle += PI / 8.f;
	}
	else
	{
		patternStep = 0;
		spireAngle = 0.f;
	}
	patternStep++;

	for (const auto& b : pendingBullets)
		spawnBullet(b.position, b.direction);

	pendingBullets.clear();
}




void M_BulletHell::Enemy::FireCircle(int _count, float _angleOffsetRad) {
	if (_count <= 0) return;

	const Maths::Vector2f pos = GetOwner()->GetPosition();
	const float step = (2.f * PI) / static_cast<float>(_count);

	for (int i = 0; i < _count; i++) {
		const float angle = _angleOffsetRad + step * static_cast<float>(i);
		const Maths::Vector2f dir(std::cos(angle), std::sin(angle));
		pendingBullets.push_back({ pos,dir });
	}
}