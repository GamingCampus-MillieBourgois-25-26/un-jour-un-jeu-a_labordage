#pragma once
#include "Core/Component.h"
#include "Maths/Vector2.h"
#include "GameObject.h"
#include <vector>

#include "AssetsModule.h"
#include "RectangleShapeRenderer.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "Texture.h"
#include "WindowModule.h"


class Level : public Component
{
public:
	GameObject* ContructLevel(Scene* sc, Maths::Vector2<float> position, Maths::Vector2<float> size);
	void DrawLevel();
private:
	
};

