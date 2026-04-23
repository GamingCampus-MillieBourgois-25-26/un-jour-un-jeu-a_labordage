#include "TetrisScene.h"




#include "AssetsModule.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "Tetris/Pièce.h"
#include "Demo/Player.h"
#include "Texture.h"


Tetris::TetrisScene::TetrisScene(): Scene("Tetris") {

	GameObject* rec = CreateGameObject("O");

	rec->CreateComponent<Pièce>();
	
}