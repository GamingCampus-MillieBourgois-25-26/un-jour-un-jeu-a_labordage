#pragma once

#include <SFML/Graphics/Color.hpp>
#include "Maths/Vector2.h"

namespace Tetris
{
    enum class TetrominoType { I, O, T, L, J, S, Z };

    constexpr int TETROMINO_COUNT = 7;
    constexpr int ROTATION_COUNT = 4;
    constexpr int BLOCKS_PER_PIECE = 4;

    struct PieceData
    {
        sf::Color color;
        // [rotation][block index] = offset (col, row) depuis l'ancre de la pièce
        Maths::Vector2i blocks[ROTATION_COUNT][BLOCKS_PER_PIECE];
    };

    extern const PieceData TETROMINO_DATA[TETROMINO_COUNT];
}
