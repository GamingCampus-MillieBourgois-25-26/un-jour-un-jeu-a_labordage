#include "Shooter.h"
#include "BulletHell/Shooter.h"
#include "BulletHell/Bullet.h"
#include "Core/GameObject.h"
#include "Core/Scene.h"
#include "Engine.h"
#include "SquareCollider.h"
#include <numbers>

void Shooter::Update(float _delta_time)
{
    survivalTime += _delta_time;
    timer += _delta_time;

    if (currentMode == EFireMode::Burst)
    {
        if (inPause)
        {
            if (timer >= pauseBetweenBursts)
            {
                timer = 0.f;
                wavesShot = 0;
                inPause = false;
                currentMode = EFireMode::Spiral;
                spiralAngle = 0.f;
                spiralTimer = 0.f;
            }
            return;
        }

        if (timer >= timeBetweenWaves)
        {
            timer = 0.f;
            SpawnWave();
            wavesShot++;

            if (wavesShot >= wavesPerBurst)
                inPause = true;
        }
    }
    else if (currentMode == EFireMode::Spiral)
    {
        spiralAngle += spiralSpeed * _delta_time;
        spiralTimer += _delta_time;

        if (spiralTimer >= spiralFireRate)
        {
            spiralTimer = 0.f;
            SpawnSpiral();
            wavesShot++;

            if (wavesShot >= 40)
            {
                wavesShot = 0;
                ringCount = 0;
                currentMode = EFireMode::Ring;
                timer = 0.f;
                inPause = true;
            }
        }
    }
    else 
    {
        if (inPause)
        {
            if (timer >= pauseBetweenBursts)
            {
                timer = 0.f;
                inPause = false;
            }
            return;
        }

        ringTimer += _delta_time;
        if (ringTimer >= ringFireRate)
        {
            ringTimer = 0.f;
            SpawnRing();
            ringCount++;

            if (ringCount >= ringsPerPhase)
            {
                ringCount = 0;
                wavesShot = 0;
                inPause = true;
                timer = 0.f;
                currentMode = EFireMode::Burst;
            }
        }
    }
}

void Shooter::SpawnWave()
{
    Scene* scene = GetOwner()->GetScene();
    const Maths::Vector2f origin = GetOwner()->GetPosition();

    const float angleStep = (2.f * std::numbers::pi_v<float>) / bulletsPerBurst;
    const float waveOffset = wavesShot * (angleStep / 2.f);

    for (int i = 0; i < bulletsPerBurst; ++i)
    {
        const float angle = i * angleStep + waveOffset;
        Maths::Vector2f dir(std::cos(angle), std::sin(angle));

        GameObject* bulletGO = scene->CreateGameObject("Bullet");
        bulletGO->SetPosition(origin);
        bulletGO->SetScale(Maths::Vector2f(0.05f, 0.05f));
        bulletGO->CreateComponent<Bullet>(dir, bulletSpeed);
        bulletGO->CreateComponent<SquareCollider>();
        SquareCollider* col = bulletGO->GetComponent<SquareCollider>();
        col->SetWidth(20.f);
        col->SetHeight(20.f);
    }
}

void Shooter::SpawnSpiral()
{
    Scene* scene = GetOwner()->GetScene();
    const Maths::Vector2f origin = GetOwner()->GetPosition();

    const float armStep = (2.f * std::numbers::pi_v<float>) / spiralArms;

    for (int i = 0; i < spiralArms; ++i)
    {
        const float angle = spiralAngle + i * armStep;
        Maths::Vector2f dir(std::cos(angle), std::sin(angle));

        GameObject* bulletGO = scene->CreateGameObject("Bullet");
        bulletGO->SetPosition(origin);
        bulletGO->SetScale(Maths::Vector2f(0.05f, 0.05f));
        bulletGO->CreateComponent<Bullet>(dir, bulletSpeed);
        bulletGO->CreateComponent<SquareCollider>();
        SquareCollider* col = bulletGO->GetComponent<SquareCollider>();
        col->SetWidth(20.f);
        col->SetHeight(20.f);
    }
}

void Shooter::SpawnRing()
{
    Scene* scene = GetOwner()->GetScene();
    const Maths::Vector2f origin = GetOwner()->GetPosition();

    const float offset = ringCount * (std::numbers::pi_v<float> / bulletsPerRing);
    const float angleStep = (2.f * std::numbers::pi_v<float>) / bulletsPerRing;

    for (int i = 0; i < bulletsPerRing; ++i)
    {
        const float angle = i * angleStep + offset;
        Maths::Vector2f dir(std::cos(angle), std::sin(angle));

        GameObject* bulletGO = scene->CreateGameObject("Bullet");
        bulletGO->SetPosition(origin);
        bulletGO->SetScale(Maths::Vector2f(0.05f, 0.05f));
        bulletGO->CreateComponent<Bullet>(dir, ringBulletSpeed);
        bulletGO->CreateComponent<SquareCollider>();
        SquareCollider* col = bulletGO->GetComponent<SquareCollider>();
        col->SetWidth(20.f);
        col->SetHeight(20.f);
    }
}