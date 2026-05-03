#include "pch.h"
#include "Platformer.h"

#include "AssetsModule.h"
#include "RectangleShapeRenderer.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "Texture.h"

#include "Platformer/Playere.h"
#include "Platformer/CollisionManagere.h"
#include "Platformer/PlatformerCamera.h"
#include "Platformer/PlatformerLevel.h"

namespace
{
    constexpr float kLockX = 200.f;
    constexpr float kStartY = 150.f;
    constexpr float kGroundY = 500.f;
}

Platformer::Platformer::Platformer() : Scene("platformer")
{
    AssetsModule* asset = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
    Texture* player_texture = asset->LoadAsset<Texture>("tanks_tankNavy1.png");

    // --- Player ---
    GameObject* player = CreateGameObject("player");
    player->SetPosition(Maths::Vector2f(kLockX, kStartY));

    Playere* p = player->CreateComponent<Playere>();
    p->positione = Maths::Vector2f(kLockX, kStartY);

    SpriteRenderer* render = player->CreateComponent<SpriteRenderer>(player_texture);
    player->CreateComponent<SquareCollider>(render);

    CollisionManagere* cm = player->CreateComponent<CollisionManagere>();
    cm->position = Maths::Vector2f(kLockX, kStartY);

    PlatformerCamera* cam = player->CreateComponent<PlatformerCamera>();
    cam->SetLockX(kLockX);

    // --- Parkour : 12 plateformes avec variete (gaps simples / petites plateformes / gros gaps) ---
    CreateGround({ -200.f, kGroundY }, { 600.f, 100.f });   //  1. Sol de depart
    CreateGround({ 550.f, kGroundY }, { 300.f, 100.f });   //  2. gap 150
    CreateGround({ 1000.f, kGroundY }, { 300.f, 100.f });   //  3. gap 150
    CreateGround({ 1450.f, kGroundY }, { 100.f, 100.f });   //  4. PETITE - precision
    CreateGround({ 1700.f, kGroundY }, { 300.f, 100.f });   //  5. gap 150
    CreateGround({ 2150.f, kGroundY }, { 250.f, 100.f });   //  6. gap 150
    CreateGround({ 2600.f, kGroundY }, { 300.f, 100.f });   //  7. GROS GAP 200
    CreateGround({ 3050.f, kGroundY }, { 300.f, 100.f });   //  8. gap 150
    CreateGround({ 3500.f, kGroundY }, { 100.f, 100.f });   //  9. PETITE - precision
    CreateGround({ 3750.f, kGroundY }, { 300.f, 100.f });   // 10. gap 150
    CreateGround({ 4250.f, kGroundY }, { 300.f, 100.f });   // 11. GROS GAP 200
    CreateGround({ 4700.f, kGroundY }, { 400.f, 100.f });   // 12. plateforme finale

    // --- Drapeau sur la plateforme finale ---
    GameObject* goal = CreateGameObject("goal");
    const Maths::Vector2f goal_size(40.f, 80.f);
    goal->SetPosition(Maths::Vector2f(4950.f, kGroundY - goal_size.y));

    RectangleShapeRenderer* goal_rec = goal->CreateComponent<RectangleShapeRenderer>();
    goal_rec->SetSize(goal_size);
    goal_rec->SetColor(sf::Color::Yellow);

    SquareCollider* goal_col = goal->CreateComponent<SquareCollider>();
    goal_col->SetSize(goal_size);

    // --- Level manager ---
    GameObject* level_mgr = CreateGameObject("LevelManager");
    PlatformerLevel* lvl = level_mgr->CreateComponent<PlatformerLevel>();
    lvl->SetTimeLimit(60.f);   // 1 minute
}

GameObject* Platformer::Platformer::CreateGround(Maths::Vector2<float> position, Maths::Vector2<float> size)
{
    GameObject* ground = CreateGameObject("obj");
    ground->SetPosition(position);

    RectangleShapeRenderer* rec = ground->CreateComponent<RectangleShapeRenderer>();
    rec->SetSize(size);
    rec->SetColor(sf::Color::Red);

    SquareCollider* coll = ground->CreateComponent<SquareCollider>();
    coll->SetSize(size);

    return ground;
}