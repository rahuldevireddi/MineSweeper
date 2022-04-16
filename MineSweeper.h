/*******************************************************************
* CLASS NAME  : MineSweep
********************************************************************/
#ifndef MINE_SWEEPER_H
#define MINE_SWEEPER_H

#define MAX_GRID_SIZE 16
#define MAX_NUM_MINES 16

class MineSweeper
{
    public:
        MineSweeper(void);
        int GetRandomNumber(void);
        void DisplayProgress(bool showMines);
        void GetUserCoordinates(int &row, int &col);
        void ReplaceMinePosition(int row, int col);
        bool IsMine(int row, int col);
        bool IsCoordinatesValid(int row, int col);
        bool ValidateCoordinatesRecursive(int row, int col, int &totalMovesLeft);
        int CalculateAdjacentMinesCount(int row, int col);
        void InsertMinesRandom(void);
        void SetGridSize(void);
        void StartMineSweeper(void);

#ifndef UNIT_TEST
    private:
#endif
        char boardCoordinates[MAX_GRID_SIZE][MAX_GRID_SIZE];
        int gridSize;
        int numMines;
};

#endif