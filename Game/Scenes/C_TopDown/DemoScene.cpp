#include "DemoScene.h"

#include <random>

#include "AssetsModule.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "TextRenderer.h"
#include "Texture.h"
#include "WindowModule.h"
#include "Demo/player.h"
#include "Demo/WaveManager.h"
#include "Demo/collision.h"

Demo::DemoScene::DemoScene() : Scene("DemoScene")
{
    AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();

    GameObject* poolGO = CreateGameObject("BulletPool");
    Demo::BulletPool* pool = poolGO->CreateComponent<Demo::BulletPool>();
    pool->CreateBullets(this);


    Texture* sr_player = assets_module->LoadAsset<Texture>("player.png");
    GameObject* player = CreateGameObject("Player");
    Demo::Player* playerComp = player->CreateComponent<Demo::Player>();
    playerComp->SetBulletPool(pool);
    player->CreateComponent<SpriteRenderer>(sr_player);

    GameObject* mechant = CreateGameObject("mechant");
    mechant->CreateComponent<WaveManager>();

    GameObject* coll_manager = CreateGameObject("Collsion Manager");
    coll_manager->CreateComponent<Collision>();
}
