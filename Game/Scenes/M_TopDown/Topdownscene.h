#pragma once

#include "Core/Scene.h"
#include "Maths/Vector2.h"

class GameObject;

namespace M_TopDown
{
    class TopDownScene : public Scene
    {
    public:
        TopDownScene();

    private:
        GameObject* CreateEnemy(const Maths::Vector2f& _position);
    };
}