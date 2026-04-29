#pragma once
#include "core/Scene.h"

namespace Platformer{


class Platformer : public Scene
{
public:
	Platformer();
	GameObject CreateGround(Maths::Vector2<float> position,Maths::Vector2<float> size);



	

};

}