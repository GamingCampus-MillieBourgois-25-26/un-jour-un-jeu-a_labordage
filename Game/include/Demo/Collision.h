#pragma once
#include "Core/Component.h"

class Collision : public Component
{
public:
    void Start() override;
    void Update(float _delta_time) override;
};