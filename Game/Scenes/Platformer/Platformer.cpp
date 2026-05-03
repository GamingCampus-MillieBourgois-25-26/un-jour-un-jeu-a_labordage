#include "pch.h"
#include "Platformer.h"
#include "AssetsModule.h"
#include "RectangleShapeRenderer.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "Texture.h"
#include "WindowModule.h"

#include "Demo/Player.h"
#include "Platformer/Playere.h"
#include "Platformer/CollisionManagere.h"
#include <iostream>



Platformer::Platformer::Platformer() : Scene("platformer") {

	AssetsModule* asset = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();

	Texture* player_texture = asset->LoadAsset<Texture>("tanks_tankNavy1.png");

	GameObject* player = CreateGameObject("player");
	GameObject* obj = CreateGameObject("obj");

	



	player->SetPosition(Maths::Vector2f(300, 150));
	player->CreateComponent<Playere>();
	SpriteRenderer* render = player->CreateComponent<SpriteRenderer>(player_texture);
	player->CreateComponent<SquareCollider>(render);
	player->CreateComponent<CollisionManagere>();



	RectangleShapeRenderer* rec = obj->CreateComponent<RectangleShapeRenderer>();
	obj->SetPosition(Maths::Vector2f(0, 500));
	rec->SetSize(Maths::Vector2f(800, 20));
	rec->SetColor(sf::Color::Red);
	SquareCollider* coll = obj->CreateComponent<SquareCollider>();
	coll->SetSize(Maths::Vector2f(800, 20));


	
	CreateGround({ 50,350 }, { 50,50 });
	CreateGround({ 150,350 }, { 50,50 });
	CreateGround({ 250,350 }, { 50,50 });
	CreateGround({ 350,350 }, { 50,50 });
	CreateGround({ 450,350 }, { 50,50 });

}



GameObject* Platformer::Platformer::CreateGround(Maths::Vector2<float> position, Maths::Vector2<float> size) {



	GameObject* ground = CreateGameObject("obj");
	ground->SetPosition(position);
	RectangleShapeRenderer* rec = ground->CreateComponent<RectangleShapeRenderer>();
	rec->SetSize(size);
	rec->SetColor(sf::Color::Red);
	SquareCollider* coll = ground->CreateComponent<SquareCollider>();
	coll->SetSize(size);

	return ground;
}

