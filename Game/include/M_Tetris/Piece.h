#pragma once

#include "Core/Component.h"
#include "Maths/Vector2.h"
#include "TetrominoData.h"

#include <SFML/Graphics/Color.hpp>
#include <array>

class GameObject;

namespace Tetris
{
    class Grid;

    class Piece : public Component
    {
    public:
        Piece(TetrominoType _type, Grid* _grid);

        void Awake() override;

        bool TryMove(int _dx, int _dy);
        bool TryRotate(int _dir);   // -1 (CCW) ou +1 (CW)
        bool TryFall();             // descend d'1 case ; false si bloqué

        // Verrouille la pièce dans la grille (transfert des blocs) puis détruit la pièce
        void Lock();

        // Calcule les 4 cases occupées dans un état (col, row, rotation) donné
        void GetCellsAt(int _col, int _row, int _rotation, Maths::Vector2i _out[4]) const;
        void GetCells(Maths::Vector2i _out[4]) const { GetCellsAt(col, row, rotation, _out); }

        TetrominoType GetType() const { return type; }
        int GetCol() const { return col; }
        int GetRow() const { return row; }
        int GetRotation() const { return rotation; }

    private:
        bool IsValidState(int _col, int _row, int _rotation) const;
        void UpdateBlockPositions();

        TetrominoType type;
        Grid* grid = nullptr;

        int col = 0;
        int row = 0;
        int rotation = 0;

        sf::Color color;
        std::array<GameObject*, 4> blocks{ nullptr, nullptr, nullptr, nullptr };
    };
}
