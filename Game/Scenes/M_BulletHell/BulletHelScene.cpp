#include "BulletHelScene.h"
#include "M_BulletHell/Enemy.h"
#include "M_BulletHell/B_Player.h"
#include "M_BulletHell/Bullets.h"
#include "M_BulletHell/B_CollisionManager.h"
#include "AssetsModule.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "Texture.h"
#include "RectangleShapeRenderer.h"

M_BulletHell::BulletHelScene::BulletHelScene() : Scene("BulletHell")
{
    AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
    Texture* logo_texture = assets_module->LoadAsset<Texture>("fish_red.png");

  
    GameObject* enemy = CreateGameObject("Enemy");
    GameObject* player = CreateGameObject("Player");

    enemy->CreateComponent<Enemy>(
        1.0f, 
        [this](const Maths::Vector2f& pos, const Maths::Vector2f& dir)
        {
            GameObject* bullet = CreateGameObject("Bullet");
            bullet->SetPosition(pos);

            AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
            Texture* logo_texture = assets_module->LoadAsset<Texture>("fish_red.png");

            auto* renderer = bullet->CreateComponent<RectangleShapeRenderer>();
            bullet->CreateComponent<Bullets>(dir, renderer, BulletOwner::Enemy, 300.f);

            
            SpriteRenderer* bullet_sprite = bullet->CreateComponent<SpriteRenderer>(logo_texture);

           
            bullet->CreateComponent<SquareCollider>(bullet_sprite);
        },
        3.0f  
    );

   
    player->CreateComponent<Player>();
    SpriteRenderer* player_sprite = player->CreateComponent<SpriteRenderer>(logo_texture);

    
    player->CreateComponent<SquareCollider>(player_sprite);

    
    CollisionManager* coll_manager = player->CreateComponent<CollisionManager>();
    coll_manager->SetSurvivalDuration(60.f);  

  
    enemy->CreateComponent<SpriteRenderer>(logo_texture);
    enemy->SetPosition({ 300.f, 50.f });
}