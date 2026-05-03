#pragma once

#include "Core/Component.h"
#include "Maths/Vector2.h"

class GameObject;

namespace Tetris
{
    class Grid : public Component
    {
    public:
        static constexpr int COLS = 10;
        static constexpr int ROWS = 20;
        static constexpr float CELL_SIZE = 28.f;

        void Awake() override;

        bool IsInBounds(int _col, int _row) const;
        bool IsCellEmpty(int _col, int _row) const;

        // Quand une pièce verrouille : on transfère ses 4 blocs (GameObject*) à la grille
        void PlaceBlocks(const Maths::Vector2i _cells[4], GameObject* const _blocks[4]);

        // Renvoie le nombre de lignes nettoyées
        int ClearCompletedLines();

        Maths::Vector2f GridToWorld(int _col, int _row) const;
        Maths::Vector2f GridToWorld(const Maths::Vector2i& _cell) const;

        Maths::Vector2f GetOffset() const { return offset; }
        void SetOffset(const Maths::Vector2f& _off) { offset = _off; }

    private:
        bool IsRowComplete(int _row) const;
        void RemoveRow(int _rowToRemove);

        // cells[row][col] = pointeur vers le bloc placé à cette case (ou nullptr)
        GameObject* cells[ROWS][COLS] = {};

        // Centre la grille dans une fenêtre 600x600 :
        // grid width  = 10 * 28 = 280  →  offset.x = (600 - 280) / 2 = 160
        // grid height = 20 * 28 = 560  →  offset.y = (600 - 560) / 2 = 20
        Maths::Vector2f offset = { 160.f, 20.f };
    };
}