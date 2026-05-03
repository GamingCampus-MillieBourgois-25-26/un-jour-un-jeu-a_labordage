#include "WaveManager.h"

#include "Modules/WindowModule.h"
#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "Demo/Mechant.h"

void WaveManager::Start()
{
    Component::Start();
    player = GetOwner()->GetScene()->FindGameObject("Player");
    SpawnWave();
}

void WaveManager::Update(float _delta_time)
{
    Component::Update(_delta_time);

    waveTimer += _delta_time;
    if (waveTimer >= waveInterval)
    {
        waveTimer = 0.f;
        SpawnWave();
    }
}

void WaveManager::SpawnWave()
{
    for (int i = 0; i < mechantPerWave; ++i)
        SpawnMechant();
}

void WaveManager::SpawnMechant()
{
    const Maths::Vector2u windowSize = GetModule<WindowModule>()->GetSize();
    const float w = static_cast<float>(windowSize.x);
    const float h = static_cast<float>(windowSize.y);
    const float margin = 60.f;

    const int side = RandomInt(0, 3);
    float sx = 0.f, sy = 0.f;

    switch (side)
    {
    case 0: sx = RandomFloat(0.f, w); sy = -margin;    break; // haut
    case 1: sx = RandomFloat(0.f, w); sy = h + margin; break; // bas
    case 2: sx = -margin;    sy = RandomFloat(0.f, h); break; // gauche
    default: sx = w + margin; sy = RandomFloat(0.f, h); break; // droite
    }

    Scene* scene = GetOwner()->GetScene();
    GameObject* go = scene->CreateGameObject("Mechant");
    go->SetPosition(Maths::Vector2f(sx, sy));

    Mechant* mechant = go->CreateComponent<Mechant>();
    mechant->SetPlayer(player);
}

int WaveManager::RandomInt(const int _min, const int _max)
{
    thread_local std::mt19937_64 gen(
        static_cast<uint64_t>(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::uniform_int_distribution dist(_min, _max);
    return dist(gen);
}

float WaveManager::RandomFloat(const float _min, const float _max)
{
    thread_local std::mt19937_64 gen(
        static_cast<uint64_t>(std::chrono::steady_clock::now().time_since_epoch().count()));
    std::uniform_real_distribution dist(_min, _max);
    return dist(gen);
}