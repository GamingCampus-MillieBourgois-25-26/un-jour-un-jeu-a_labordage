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
	GameObject* obj2 = CreateGameObject("obj");
	GameObject* obj3 = CreateGameObject("obj");
	



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



	RectangleShapeRenderer* rec1 = obj2->CreateComponent<RectangleShapeRenderer>();
	obj2->SetPosition(Maths::Vector2f(100, 450));
	rec1->SetSize(Maths::Vector2f(50, 20));
	rec1->SetColor(sf::Color::Red);
	SquareCollider* coll1 = obj2->CreateComponent<SquareCollider>();
	coll1->SetSize(Maths::Vector2f(50, 20));
	
	RectangleShapeRenderer* rec3 = obj3->CreateComponent<RectangleShapeRenderer>();
	obj3->SetPosition(Maths::Vector2f(150, 450));
	rec3->SetSize(Maths::Vector2f(50, 20));
	rec3->SetColor(sf::Color::Red);
	SquareCollider* coll3 = obj3->CreateComponent<SquareCollider>();
	coll1->SetSize(Maths::Vector2f(50, 20));
	CreateGround({ 50,450 }, { 50,50 });
	CreateGround({ 50,400 }, { 50,50 });
	CreateGround({ 100,400 }, { 50,50 });
	CreateGround({ 150,400 }, { 50,50 });
	CreateGround({ 200,400 }, { 50,50 });

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

