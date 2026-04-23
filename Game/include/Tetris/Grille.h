// TetrisGrid.h
#pragma once
#include "Component.h"
#include <vector>

class TetrisGrid : public Component {
public:
    static constexpr int COLS = 10;
    static constexpr int ROWS = 20;
    static constexpr float CELL_SIZE = 64.f;

    void Start() override;

    bool IsEmpty(int _col, int _row) const;
    bool IsValidPosition(int _col, int _row) const;

    void PlaceBlock(int _col, int _row, GameObject* _existing_block);
    void ClearBlock(int _col, int _row);

    int ClearFullLines(); // retourne le nombre de lignes supprimées

private:
    // nullptr = vide, couleur stockée dans le GameObject
    std::vector<std::vector<GameObject*>> cells;

    void InitGrid();
};