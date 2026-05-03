#include "BulletScene.h"
#include "AssetsModule.h"
#include "SpriteRenderer.h"
#include "Texture.h"
#include "WindowModule.h"
#include "BulletHell/Bullet.h"
#include "BulletHell/Shooter.h"
#include "BulletHell/Player.h"

BulletHell::BulletScene::BulletScene() : Scene("BulletScene")
{
    AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();

    Texture* sr_mechant = assets_module->LoadAsset<Texture>("fish_red.png");
    GameObject* mechant = CreateGameObject("mechant");
    mechant->SetRotation(sf::degrees(90));
    mechant->SetPosition(Maths::Vector2f(500, 100));
    mechant->CreateComponent<SpriteRenderer>(sr_mechant);
    mechant->CreateComponent<Shooter>();
    

    Texture* sr_player = assets_module->LoadAsset<Texture>("player.png");
    GameObject* player = CreateGameObject("Player");
    player->CreateComponent<Player>();
    
    player->SetScale(Maths::Vector2f(0.4f, 0.4f));
    player->CreateComponent<SpriteRenderer>(sr_player);
    
}