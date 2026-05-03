#include "Collision.h"
#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "Components/SquareCollider.h"
#include "iostream"

void Collision::Start()
{
    Component::Start();
}

void Collision::Update(float _delta_time)
{
    Component::Update(_delta_time);

    Scene* scene = GetOwner()->GetScene();
    const auto& gameObjects = scene->GetGameObjects();

    GameObject* player = scene->FindGameObject("Player");
    if (!player) return;

    SquareCollider* pc = player->GetComponent<SquareCollider>();
    if (!pc) return;

    for (const auto& go : gameObjects)
    {
        if (go->IsMarkedForDeletion()) continue;
        if (go->GetName() != "Bullet") continue;

        SquareCollider* bc = go->GetComponent<SquareCollider>();
        if (!bc) continue;

        if (SquareCollider::IsColliding(*pc, *bc))
        {
            std::cout << "collision" << std::endl;
            go->MarkForDeletion();
        }
    }
}