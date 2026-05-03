#include "Demo/Mechant.h"

#include "Modules/AssetsModule.h"
#include "Components/SpriteRenderer.h"
#include "Assets/Texture.h"
#include <cmath>
#include "SquareCollider.h"
void Mechant::Start()
{
    Component::Start();

    AssetsModule* assets = GetModule<AssetsModule>();
    if (!assets) return;

    Texture* tex = assets->LoadAsset<Texture>("fish_red.png");
    if (tex)
        GetOwner()->CreateComponent<SpriteRenderer>(tex);


    SquareCollider* col = GetOwner()->CreateComponent<SquareCollider>();
    col->SetWidth(50.f);
    col->SetHeight(50.f);
}

void Mechant::Update(float _delta_time)
{
    Component::Update(_delta_time);

    if (!player) return;

    const Maths::Vector2f myPos = GetOwner()->GetPosition();
    const Maths::Vector2f targPos = player->GetPosition();

    Maths::Vector2f dir = Maths::Vector2f(targPos.x - myPos.x, targPos.y - myPos.y);
    if (dir.Magnitude() < 1.f) return;

    dir = dir.Normalize();

    GetOwner()->SetPosition(Maths::Vector2f(myPos.x + dir.x * speed * _delta_time,
        myPos.y + dir.y * speed * _delta_time));

    GetOwner()->SetRotation(sf::radians(std::atan2(dir.y, dir.x)));
}