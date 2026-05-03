#pragma once

#include "Core/Component.h"
#include "Maths/Vector2.h"

namespace Platformer
{

    class PlatformerCamera : public Component
    {
    public:
        void Start() override;
        void Update(float _delta_time) override;

        void SetLockX(float _x) { lockX = _x; }
        float GetLockX() const { return lockX; }

    private:
        float lockX = 200.f;
        Maths::Vector2f lastPos;
        bool initialized = false;
    };
}
