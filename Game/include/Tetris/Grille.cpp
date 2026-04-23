#include "Grille.h"
#include "RectangleShapeRenderer.h"
// TetrisGrid.cpp
void TetrisGrid::Start() {
    InitGrid();
}

void TetrisGrid::InitGrid() {
    // Initialise toutes les cellules à nullptr
    cells.assign(ROWS, std::vector<GameObject*>(COLS, nullptr));
}

bool TetrisGrid::IsValidPosition(int _col, int _row) const {
    // Hors des bornes = invalide
    if (_col < 0 || _col >= COLS) return false;
    if (_row < 0 || _row >= ROWS) return false;
    return true;
}

bool TetrisGrid::IsEmpty(int _col, int _row) const {
    if (!IsValidPosition(_col, _row)) return false;
    return cells[_row][_col] == nullptr;
}

void TetrisGrid::PlaceBlock(int _col, int _row, GameObject* _existing_block) {
    if (!IsEmpty(_col, _row)) return;

    // On snap la position sur la grille
    _existing_block->SetPosition(
        Maths::Vector2f(_col * CELL_SIZE, _row * CELL_SIZE)
    );

    cells[_row][_col] = _existing_block;
}

int TetrisGrid::ClearFullLines() {
    int cleared = 0;

    for (int row = ROWS - 1; row >= 0; row--) {
        // Vérifie si la ligne est pleine
        bool full = true;
        for (int col = 0; col < COLS; col++) {
            if (cells[row][col] == nullptr) { full = false; break; }
        }

        if (!full) continue;

        // Supprime les blocs de la ligne
        for (int col = 0; col < COLS; col++) {
            cells[row][col]->MarkForDeletion();
            cells[row][col] = nullptr;
        }

        // Fait descendre toutes les lignes au-dessus
        for (int r = row; r > 0; r--) {
            for (int col = 0; col < COLS; col++) {
                cells[r][col] = cells[r - 1][col];
                if (cells[r][col]) {
                    // Met à jour la position visuelle
                    cells[r][col]->SetPosition(
                        Maths::Vector2f(col * CELL_SIZE, r * CELL_SIZE)
                    );
                }
            }
        }

        cleared++;
        row++; // Re-vérifie la même ligne (qui a changé)
    }

    return cleared;
}