#include "Pièce.h"
#include <iostream>
#include "RectangleShapeRenderer.h"

// Pièce.cpp
void Tetris::Pièce::CreateO(Scene* scene) {
    for (int i = 0; i <= 1; i++) {
        for (int j = 0; j <= 1; j++) {
            GameObject* rect = scene->CreateGameObject("block");
            rect->CreateComponent<RectangleShapeRenderer>()->SetSize(
                Maths::Vector2f(64.f, 64.f)
            );
            rect->SetPosition(Maths::Vector2f(i * 64.f, j * 64.f));

            // On stocke le bloc avec sa position grille
            blocks.push_back(BlockCell{ rect, i, j });
        }
    }
}

void Tetris::Pièce::LandPiece(TetrisGrid* _grid) {
    for (BlockCell& cell : blocks) { // ← plus de structured binding sur GameObject*
        _grid->PlaceBlock(cell.col, cell.row, cell.gameObject);
    }
    GetOwner()->MarkForDeletion();
}

void Tetris::Pièce::Update(float _delta_time) {
    for (BlockCell& cell : blocks) {
        Maths::Vector2f pos = cell.gameObject->GetPosition();
        pos.y += speed * _delta_time;
        cell.gameObject->SetPosition(pos);

        // Met à jour la position grille aussi
        cell.row = static_cast<int>(pos.y / TetrisGrid::CELL_SIZE);
    }
}