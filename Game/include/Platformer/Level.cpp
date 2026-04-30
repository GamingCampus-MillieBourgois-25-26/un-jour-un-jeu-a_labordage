#include "pch.h"
#include "Level.h"
#include "Core/Scene.h"


GameObject* Level::ContructLevel(Scene* sc, Maths::Vector2<float> position, Maths::Vector2<float> size)
{
	GameObject* ground = sc->CreateGameObject("obj");
	ground->SetPosition(position);
	RectangleShapeRenderer* rec = ground->CreateComponent<RectangleShapeRenderer>();
	rec->SetSize(size);
	rec->SetColor(sf::Color::Red);
	SquareCollider* coll = ground->CreateComponent<SquareCollider>();
	coll->SetSize(size);

	return ground;
}

void Level::DrawLevel()
{

}
