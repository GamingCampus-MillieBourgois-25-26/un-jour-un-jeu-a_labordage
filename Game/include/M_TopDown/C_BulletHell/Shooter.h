#pragma once
#include "Core/Component.h"
#include "Maths/Vector2.h"

class Shooter : public Component
{
public:
    void Update(float _delta_time) override;
    void SpawnWave();
    void SpawnSpiral();
    void SpawnRing();  

    float GetSurvivalTime() const { return survivalTime; }

private:
    enum class EFireMode { Burst, Spiral, Ring };
    EFireMode currentMode = EFireMode::Burst;

    float survivalTime = 0.f;

    float timer = 0.f;
    float timeBetweenWaves = 0.3f;
    float pauseBetweenBursts = 0.5f;
    int   wavesPerBurst = 5;
    int   wavesShot = 0;
    bool  inPause = false;
    int   bulletsPerBurst = 8;
    float bulletSpeed = 200.f;

    float spiralAngle = 0.f;
    float spiralSpeed = 3.f;
    float spiralFireRate = 0.05f;
    float spiralTimer = 0.f;
    int   spiralArms = 3;

    float ringTimer = 0.f;
    float ringFireRate = 0.6f;
    int   ringCount = 0;
    int   ringsPerPhase = 6;
    int   bulletsPerRing = 16;
    float ringBulletSpeed = 150.f;
};