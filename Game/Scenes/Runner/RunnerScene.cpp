#include "pch.h"
#include "RunnerScene.h"
#include "AssetsModule.h"
#include "RectangleShapeRenderer.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "Texture.h"
#include "WindowModule.h"

#include "Demo/Player.h"
#include "Runner/Player.h"
#include "Runner/CollisionManager.h"
#include <iostream>





Runner::RunnerScene::RunnerScene() : Scene("Scene courir") {

	AssetsModule* asset = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();

	Texture* player_texture = asset->LoadAsset<Texture>("tanks_tankNavy1.png");

	GameObject* player = CreateGameObject("player");
	GameObject* obj = CreateGameObject("obj");



	player->SetPosition(Maths::Vector2f(300, 150));
	player->CreateComponent<Player>();
	SpriteRenderer* render = player->CreateComponent<SpriteRenderer>(player_texture);
	player->CreateComponent<SquareCollider>(render);
	player->CreateComponent<CollisionManager>();


	
	RectangleShapeRenderer* rec =  obj->CreateComponent<RectangleShapeRenderer>();
	obj->SetPosition(Maths::Vector2f(0, 500));
	rec->SetSize(Maths::Vector2f(800, 20));
	rec->SetColor(sf::Color::Red);
	SquareCollider* coll = obj->CreateComponent<SquareCollider>();
	coll->SetSize(Maths::Vector2f(800, 20));
}