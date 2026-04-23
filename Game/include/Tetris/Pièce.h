// Pièce.h
#pragma once
#include "Scene.h"
#include "Component.h"
#include "Grille.h"
#include <vector>

class TetrisGrid;

namespace Tetris {

    struct BlockCell {
        GameObject* gameObject = nullptr;
        int col = 0;
        int row = 0;
    };

    class Pièce : public Component {
    public:
        void Start() override { Tetris::Pièce::CreateO(GetOwner()->GetScene()); };
        void Update(float _delta_time) override;
        void CreateO(Scene* scene);
        void LandPiece(TetrisGrid* _grid);

    private:
        std::vector<BlockCell> blocks; // ← struct au lieu de GameObject* direct
        float speed = 150.f;
    };
}