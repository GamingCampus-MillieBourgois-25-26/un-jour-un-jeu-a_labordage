#include "pch.h"
#include "TopDownScene.h"

#include "AssetsModule.h"
#include "SpriteRenderer.h"
#include "RectangleShapeRenderer.h"
#include "SquareCollider.h"
#include "Texture.h"
#include "Engine.h"
#include "ModuleManager.h"

#include "M_TopDown/T_Player.h"
#include "M_TopDown/T_Enemy.h"
#include "M_TopDown/T_Bullets.h"
#include "M_TopDown/T_CollisionManager.h"

namespace
{
    
    void CreateBullet(Scene* _scene, const Maths::Vector2f& _pos, const Maths::Vector2f& _dir,
        M_TopDown::BulletOwner _owner, float _speed)
    {
        AssetsModule* assets = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
        Texture* texture = assets->LoadAsset<Texture>("fish_red.png");

        GameObject* bullet = _scene->CreateGameObject("Bullet");
        bullet->SetPosition(_pos);

        SpriteRenderer* sprite = bullet->CreateComponent<SpriteRenderer>(texture);
        bullet->CreateComponent<SquareCollider>(sprite);
        bullet->CreateComponent<M_TopDown::Bullets>(_dir, _owner, _speed);

        
        if (_owner == M_TopDown::BulletOwner::Player)
            bullet->SetScale({ 0.5f, 0.5f });
        else
            bullet->SetScale({ 0.4f, 0.4f });
    }
}

M_TopDown::TopDownScene::TopDownScene() : Scene("TopDown")
{
    AssetsModule* assets = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
    Texture* texture = assets->LoadAsset<Texture>("fish_red.png");


    GameObject* player = CreateGameObject("Player");
    player->SetPosition({ 300.f, 450.f });

    auto player_spawn_fn = [this](const Maths::Vector2f& pos, const Maths::Vector2f& dir)
        {
            CreateBullet(this, pos, dir, BulletOwner::Player, 700.f);
        };

    player->CreateComponent<Player>(player_spawn_fn);
    SpriteRenderer* player_sprite = player->CreateComponent<SpriteRenderer>(texture);
    player->CreateComponent<SquareCollider>(player_sprite);
    player->CreateComponent<CollisionManager>();

   
    CreateEnemy({ 100.f, 100.f });
    CreateEnemy({ 300.f, 100.f });
    CreateEnemy({ 500.f, 100.f });
    CreateEnemy({ 200.f, 200.f });
    CreateEnemy({ 400.f, 200.f });
}

GameObject* M_TopDown::TopDownScene::CreateEnemy(const Maths::Vector2f& _position)
{
    AssetsModule* assets = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
    Texture* texture = assets->LoadAsset<Texture>("fish_red.png");

    GameObject* enemy = CreateGameObject("Enemy");
    enemy->SetPosition(_position);

    auto enemy_spawn_fn = [this](const Maths::Vector2f& pos, const Maths::Vector2f& dir)
        {
            CreateBullet(this, pos, dir, BulletOwner::Enemy, 350.f);
        };

    
    enemy->CreateComponent<Enemy>(enemy_spawn_fn, 3.f, 1.5f);

    SpriteRenderer* enemy_sprite = enemy->CreateComponent<SpriteRenderer>(texture);
    enemy->CreateComponent<SquareCollider>(enemy_sprite);

    return enemy;
}