#pragma once
#include "Core/Component.h"
#include "Core/GameObject.h"

class Mechant : public Component
{
public:
    void Start() override;
    void Update(float _delta_time) override;

    void SetPlayer(GameObject* _player) { player = _player; }

private:
    GameObject* player = nullptr;
    float speed = 80.f;
    int hp = 3;
};