#include "pch.h"
#include "Grid.h"

#include "Core/Scene.h"
#include "Core/GameObject.h"
#include "RectangleShapeRenderer.h"

namespace Tetris
{
    void Grid::Awake()
    {
        Component::Awake();

        // --- Fond de grille (cases grises pour visualiser le board) ---
        Scene* scene = GetOwner()->GetScene();
        for (int row = 0; row < ROWS; ++row)
        {
            for (int col = 0; col < COLS; ++col)
            {
                GameObject* bg = scene->CreateGameObject("GridBg");
                RectangleShapeRenderer* r = bg->CreateComponent<RectangleShapeRenderer>();
                r->SetSize(Maths::Vector2f(CELL_SIZE - 2.f, CELL_SIZE - 2.f));
                r->SetColor(sf::Color(30, 30, 35));
                bg->SetPosition(GridToWorld(col, row));
            }
        }
    }

    bool Grid::IsInBounds(int _col, int _row) const
    {
        return _col >= 0 && _col < COLS && _row >= 0 && _row < ROWS;
    }

    bool Grid::IsCellEmpty(int _col, int _row) const
    {
        if (!IsInBounds(_col, _row)) return false;
        return cells[_row][_col] == nullptr;
    }

    void Grid::PlaceBlocks(const Maths::Vector2i _cells[4], GameObject* const _blocks[4])
    {
        for (int i = 0; i < 4; ++i)
        {
            const int c = _cells[i].x;
            const int r = _cells[i].y;

            if (IsInBounds(c, r))
            {
                cells[r][c] = _blocks[i];
                _blocks[i]->SetPosition(GridToWorld(c, r));
            }
            else
            {
                // Hors-grille (top-out par exemple) : on supprime le bloc orphelin
                _blocks[i]->MarkForDeletion();
            }
        }
    }

    int Grid::ClearCompletedLines()
    {
        int cleared = 0;
        for (int row = ROWS - 1; row >= 0; --row)
        {
            // While : si plusieurs lignes consécutives sont complètes, le shift les ramène ici
            while (IsRowComplete(row))
            {
                RemoveRow(row);
                cleared++;
            }
        }
        return cleared;
    }

    bool Grid::IsRowComplete(int _row) const
    {
        for (int col = 0; col < COLS; ++col)
        {
            if (cells[_row][col] == nullptr) return false;
        }
        return true;
    }

    void Grid::RemoveRow(int _rowToRemove)
    {
        // 1. Détruire les GameObjects de la ligne supprimée
        for (int col = 0; col < COLS; ++col)
        {
            if (cells[_rowToRemove][col] != nullptr)
            {
                cells[_rowToRemove][col]->MarkForDeletion();
                cells[_rowToRemove][col] = nullptr;
            }
        }

        // 2. Décaler tout ce qui est au-dessus d'une ligne vers le bas
        for (int row = _rowToRemove; row > 0; --row)
        {
            for (int col = 0; col < COLS; ++col)
            {
                cells[row][col] = cells[row - 1][col];
                if (cells[row][col] != nullptr)
                    cells[row][col]->SetPosition(GridToWorld(col, row));
            }
        }

        // 3. Vider la ligne du haut
        for (int col = 0; col < COLS; ++col)
            cells[0][col] = nullptr;
    }

    Maths::Vector2f Grid::GridToWorld(int _col, int _row) const
    {
        return Maths::Vector2f(
            offset.x + static_cast<float>(_col) * CELL_SIZE,
            offset.y + static_cast<float>(_row) * CELL_SIZE
        );
    }

    Maths::Vector2f Grid::GridToWorld(const Maths::Vector2i& _cell) const
    {
        return GridToWorld(_cell.x, _cell.y);
    }
}
