#include <iostream>
#include <CppUTest/CommandLineTestRunner.h>

#include "MineSweeper.h"

// #define UNIT_TEST

using namespace std;

extern int setRow;
extern int setCol;

TEST_GROUP(MineSweeper)
{
    MineSweeper ms;
    int minesLocation[MAX_NUM_MINES][2]; // All mines position (row, col)

    void setup(void)
    {
        memset(minesLocation, 0, sizeof(int) * MAX_NUM_MINES * 2);
        ms.gridSize = 9;
        ms.numMines = 9;
        ms.InsertMinesRandom();
        LocateMines();
    }

    void teardown(void)
    {
        
    }

    void ResetBoard(void)
    {
        for (int row = 0; row < MAX_GRID_SIZE; row++)
        {
            for (int col = 0; col < MAX_GRID_SIZE; col++)
            {
                ms.boardCoordinates[row][col] = '.';
            }
        }
    }

    void InsertMine(int row, int col)
    {
        static int mineIndex;
        ms.boardCoordinates[row][col] = '*';
        mineIndex++;
    }

    void LocateMines(void)
    {
        int mineIndex = 0;

        for (int row = 0; row < ms.gridSize; row++)
        {
            for (int col = 0; col < ms.gridSize; col++)
            {
                if (ms.IsMine(row, col))
                {
                    minesLocation[mineIndex][0] = row;
                    minesLocation[mineIndex][1] = col;
                    mineIndex++;
                }
            }
        }
    }
};


TEST(MineSweeper, CheckRandomNumbersInRange)
{
    // 9 * 9 board;
    int randomNumber = ms.GetRandomNumber();
    CHECK((randomNumber > 0) && randomNumber < (ms.gridSize * ms.gridSize));
    ms.gridSize = 16;
    randomNumber = ms.GetRandomNumber();
    CHECK((randomNumber > 0) && randomNumber < (ms.gridSize * ms.gridSize));
}


TEST(MineSweeper, ValidateBoardCooridnates)
{
    // 9 * 9 board
    CHECK(ms.IsCoordinatesValid(0, 0));
    CHECK(ms.IsCoordinatesValid(0, 8));
    CHECK(ms.IsCoordinatesValid(8, 0));
    CHECK(ms.IsCoordinatesValid(8, 8));
    CHECK_EQUAL(false, ms.IsCoordinatesValid(-1, 9));
    CHECK_EQUAL(false, ms.IsCoordinatesValid(-9, -9));
    CHECK_EQUAL(false, ms.IsCoordinatesValid(0, 9));
    CHECK_EQUAL(false, ms.IsCoordinatesValid(9, 9));
}


TEST(MineSweeper, VerifyMinesLocation)
{
    int mineIndex;

    for (mineIndex = 0; mineIndex < ms.numMines; mineIndex++)
        CHECK(ms.IsMine(minesLocation[mineIndex][0], minesLocation[mineIndex][1]));
    // Replace mines position
    for (mineIndex = 0; mineIndex < ms.numMines; mineIndex++)
        ms.ReplaceMinePosition(minesLocation[mineIndex][0], minesLocation[mineIndex][1]);
    // Re-verify its location
    LocateMines();
    for (mineIndex = 0; mineIndex < ms.numMines; mineIndex++)
        CHECK(ms.IsMine(minesLocation[mineIndex][0], minesLocation[mineIndex][1]));
}


TEST(MineSweeper, HitMineShouldEndTheGame)
{
    bool isGameFinished;
    int totalMovesLeft = 10;

    isGameFinished = ms.ValidateCoordinatesRecursive(minesLocation[1][0], minesLocation[1][1], totalMovesLeft);
    CHECK(isGameFinished);
}


TEST(MineSweeper, CalculateAdjacentMinesCount)
{
    ResetBoard();
    ms.numMines = 5;
    ms.gridSize = 5;

    InsertMine(0, 0);
    InsertMine(0, 2);
    InsertMine(1, 0);
    InsertMine(1, 1);
    InsertMine(1, 2);
    CHECK_EQUAL(ms.numMines, ms.CalculateAdjacentMinesCount(0, 1));
}


TEST(MineSweeper, RevealAdjacentCellsIncaseOfNoMine)
{
    ResetBoard();
    ms.numMines = 4;
    ms.gridSize = 5;
    

    InsertMine(0, 0);
    InsertMine(0, 4);
    InsertMine(4, 0);
    InsertMine(4, 4);
    int totalMovesLeft = ((ms.gridSize * ms.gridSize) - ms.numMines); 
    // Should win the game
    CHECK_EQUAL(false, ms.ValidateCoordinatesRecursive(2, 2, totalMovesLeft));
    ms.DisplayProgress(true);   // this will reveal all the adjacent cells
    CHECK_EQUAL(0, totalMovesLeft);
}


int main(int ac, char** av)
{
   return CommandLineTestRunner::RunAllTests(ac, av);
}
