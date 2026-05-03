#pragma once
#include "Core/Component.h"
#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "Maths/Vector2.h"
#include <chrono>
#include <cstdint>
#include <random>

class WaveManager : public Component
{
public:
    void Start() override;
    void Update(float _delta_time) override;

    void SpawnWave();
    void SpawnMechant();

    int RandomInt(int _min, int _max);
    float RandomFloat(float _min, float _max);

private:
    GameObject* player = nullptr;

    float waveTimer = 0.f;
    float waveInterval = 5.f;
    int mechantPerWave = 5;
};