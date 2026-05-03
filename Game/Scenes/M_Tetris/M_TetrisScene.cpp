#include "pch.h"
#include "M_TetrisScene.h"

#include "M_Tetris/Grid.h"
#include "M_Tetris/TetrisManager.h"

#include "Core/GameObject.h"

namespace Tetris
{
    M_TetrisScene::M_TetrisScene() : Scene("M_TetrisScene")
    {
        // --- Grid ---
        GameObject* grid_go = CreateGameObject("Grid");
        Grid* grid = grid_go->CreateComponent<Grid>();

        // --- Manager ---
        GameObject* mgr_go = CreateGameObject("TetrisManager");
        TetrisManager* mgr = mgr_go->CreateComponent<TetrisManager>();
        mgr->SetGrid(grid);
    }
}