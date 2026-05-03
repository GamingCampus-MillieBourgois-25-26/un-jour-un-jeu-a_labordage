#include "pch.h"
#include "PlatformerCamera.h"

#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "Playere.h"

#include <cmath>

void Platformer::PlatformerCamera::Start()
{
    Component::Start();
    lastPos = GetOwner()->GetPosition();
    initialized = true;
}

void Platformer::PlatformerCamera::Update(float _delta_time)
{
    if (!initialized)
    {
        lastPos = GetOwner()->GetPosition();
        initialized = true;
        return;
    }

    GameObject* player = GetOwner();
    Maths::Vector2f currentPos = player->GetPosition();
    const float deltaX = currentPos.x - lastPos.x;

    if (std::abs(deltaX) > 0.0001f)
    {
        
        for (const auto& go : player->GetScene()->GetGameObjects())
        {
            if (go.get() == player) continue;
            if (go->GetName().starts_with("UI_")) continue;

            Maths::Vector2f pos = go->GetPosition();
            pos.x -= deltaX;
            go->SetPosition(pos);
        }

        
        currentPos.x = lockX;
        player->SetPosition(currentPos);

        Playere* p = player->GetComponent<Playere>();
        if (p != nullptr)
            p->positione.x = lockX;
    }

    lastPos = player->GetPosition();
}