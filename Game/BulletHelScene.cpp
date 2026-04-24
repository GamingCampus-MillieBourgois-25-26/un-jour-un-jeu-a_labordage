#include "BulletHelScene.h"
#include "BulletHell/Enemy.h"
#include "BulletHell/Player.h"
#include "BulletHell/Bullet.h"
#include "AssetsModule.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "Texture.h"
#include "RectangleShapeRenderer.h"

BulletHell::BulletHelScene::BulletHelScene() : Scene("BulletHell")
{
    AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
    Texture* logo_texture = assets_module->LoadAsset<Texture>("logo.png");

    // --- Ennemi ---
    GameObject* enemy = CreateGameObject("Enemy");

    enemy->CreateComponent<Enemy>(
        1.0f, // fireInterval
        [this](const Maths::Vector2f& pos, const Maths::Vector2f& dir)
        {
            GameObject* bullet = CreateGameObject("Bullet");
            bullet->SetPosition(pos);

            AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
            Texture* logo_texture = assets_module->LoadAsset<Texture>("logo.png");
            auto* renderer = bullet->CreateComponent<RectangleShapeRenderer>();
            bullet->CreateComponent<Bullet>(dir, renderer, BulletOwner::Enemy, 300.f);
            bullet->CreateComponent<SpriteRenderer>(logo_texture);
        }
    );
    enemy->CreateComponent<SpriteRenderer>(logo_texture);

    // --- Joueur ---
    GameObject* player = CreateGameObject("Player");
    player->CreateComponent<Player>();
}