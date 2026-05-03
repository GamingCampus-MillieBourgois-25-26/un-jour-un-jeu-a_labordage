#include "Collision.h"
#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "Components/SquareCollider.h"

void Collision::Start()
{
    Component::Start();
}

void Collision::Update(float _delta_time)
{
    Component::Update(_delta_time);

    Scene* scene = GetOwner()->GetScene();
    const auto& gameObjects = scene->GetGameObjects();
    std::vector<GameObject*> bullets;
    std::vector<GameObject*> mechants;

    for (const auto& go : gameObjects)
    {
        if (go->IsMarkedForDeletion()) continue;

        if (go->GetName() == "Bullet")   bullets.push_back(go.get());
        if (go->GetName() == "Mechant")  mechants.push_back(go.get());
    }
    for (GameObject* bullet : bullets)
    {
        SquareCollider* bc = bullet->GetComponent<SquareCollider>();
        if (!bc) continue;

        for (GameObject* mechant : mechants)
        {
            SquareCollider* mc = mechant->GetComponent<SquareCollider>();
            if (!mc) continue;

            if (SquareCollider::IsColliding(*bc, *mc))
            {
                Logger::Log(ELogLevel::Debug, "Collision détectée !");
                bullet->MarkForDeletion();
                mechant->MarkForDeletion();
                break; 
            }
        }
    }
}