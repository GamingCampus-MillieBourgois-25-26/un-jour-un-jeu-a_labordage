#include "pch.h"
#include "Piece.h"
#include "Grid.h"

#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "RectangleShapeRenderer.h"

namespace Tetris
{
    Piece::Piece(TetrominoType _type, Grid* _grid)
        : type(_type), grid(_grid)
    {
        color = TETROMINO_DATA[static_cast<int>(type)].color;
    }

    void Piece::Awake()
    {
        Component::Awake();

        // Position de spawn : centré en haut de la grille
        col = (Grid::COLS / 2) - 2;
        row = 0;
        rotation = 0;

        // Création des 4 blocs (1 GameObject par bloc)
        Scene* scene = GetOwner()->GetScene();
        for (int i = 0; i < 4; ++i)
        {
            blocks[i] = scene->CreateGameObject("Block");
            RectangleShapeRenderer* r = blocks[i]->CreateComponent<RectangleShapeRenderer>();
            r->SetSize(Maths::Vector2f(Grid::CELL_SIZE - 2.f, Grid::CELL_SIZE - 2.f));
            r->SetColor(color);
        }

        UpdateBlockPositions();
    }

    bool Piece::TryMove(int _dx, int _dy)
    {
        if (IsValidState(col + _dx, row + _dy, rotation))
        {
            col += _dx;
            row += _dy;
            UpdateBlockPositions();
            return true;
        }
        return false;
    }

    bool Piece::TryRotate(int _dir)
    {
        const int new_rot = (rotation + _dir + 4) % 4;
        if (IsValidState(col, row, new_rot))
        {
            rotation = new_rot;
            UpdateBlockPositions();
            return true;
        }
        return false;
    }

    bool Piece::TryFall()
    {
        return TryMove(0, 1);
    }

    void Piece::Lock()
    {
        Maths::Vector2i cells_pos[4];
        GetCells(cells_pos);

        GameObject* block_array[4];
        for (int i = 0; i < 4; ++i) block_array[i] = blocks[i];

        grid->PlaceBlocks(cells_pos, block_array);

        // Plus de référence aux blocs côté Piece (la grille en a la garde)
        for (int i = 0; i < 4; ++i) blocks[i] = nullptr;

        GetOwner()->MarkForDeletion();
    }

    void Piece::GetCellsAt(int _col, int _row, int _rotation, Maths::Vector2i _out[4]) const
    {
        const PieceData& data = TETROMINO_DATA[static_cast<int>(type)];
        for (int i = 0; i < 4; ++i)
        {
            const Maths::Vector2i offset = data.blocks[_rotation][i];
            _out[i] = Maths::Vector2i(_col + offset.x, _row + offset.y);
        }
    }

    bool Piece::IsValidState(int _col, int _row, int _rotation) const
    {
        Maths::Vector2i cells_pos[4];
        GetCellsAt(_col, _row, _rotation, cells_pos);

        for (int i = 0; i < 4; ++i)
        {
            if (!grid->IsInBounds(cells_pos[i].x, cells_pos[i].y)) return false;
            if (!grid->IsCellEmpty(cells_pos[i].x, cells_pos[i].y)) return false;
        }
        return true;
    }

    void Piece::UpdateBlockPositions()
    {
        Maths::Vector2i cells_pos[4];
        GetCells(cells_pos);

        for (int i = 0; i < 4; ++i)
        {
            if (blocks[i] != nullptr)
                blocks[i]->SetPosition(grid->GridToWorld(cells_pos[i]));
        }
    }
}
