#include "BulletHelScene.h"
#include "M_BulletHell/Enemy.h"
#include "M_BulletHell/Player.h"
#include "M_BulletHell/Bullets.h"
#include "AssetsModule.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "Texture.h"
#include "RectangleShapeRenderer.h"

M_BulletHell::BulletHelScene::BulletHelScene() : Scene("BulletHell")
{
    AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
    Texture* logo_texture = assets_module->LoadAsset<Texture>("fish_red.png");

    // --- Ennemi ---
    GameObject* enemy = CreateGameObject("Enemy");
	GameObject* player = CreateGameObject("Player");
    enemy->CreateComponent<Enemy>(
        1.0f, // fireInterval
        [this](const Maths::Vector2f& pos, const Maths::Vector2f& dir)
        {
            GameObject* bullet = CreateGameObject("Bullet");
            bullet->SetPosition(pos);

            AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
            Texture* logo_texture = assets_module->LoadAsset<Texture>("fish_red.png");
            auto* renderer = bullet->CreateComponent<RectangleShapeRenderer>();
            bullet->CreateComponent<Bullets>(dir, renderer, BulletOwner::Enemy, 300.f);
            bullet->CreateComponent<SpriteRenderer>(logo_texture);
        }
    );

	player->CreateComponent<Player>();
	player->CreateComponent<SpriteRenderer>(logo_texture);
    enemy->CreateComponent<SpriteRenderer>(logo_texture);
	enemy->SetPosition({ 300.f, 50.f });

   
    
}