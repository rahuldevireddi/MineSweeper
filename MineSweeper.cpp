/*******************************************************************
 * CLASS NAME  : MineSweeper
 * Implemenatation of MineSweeper game
 *
 * Author: Rahul Devireddy
 * 
 ********************************************************************/
#include<iostream>
#include<cstring>

#include "MineSweeper.h"

using namespace std;

#ifdef UNIT_TEST
int setRow;
int setCol;
#endif


/*****************************************************************
DESCRIPTION : Constructor
******************************************************************/
MineSweeper::MineSweeper()
{
    // set the seed value for random number generation
    srand(time(NULL));
    gridSize = MAX_GRID_SIZE;
    numMines = MAX_NUM_MINES;

    for (int row = 0; row < MAX_GRID_SIZE; row++)
    {
        for (int col = 0; col < MAX_GRID_SIZE; col++)
        {
            boardCoordinates[row][col] = '.';
        }
    }
}


/*****************************************************************
DESCRIPTION : Get a random number (0 to gridSize*gridSize)
******************************************************************/
int MineSweeper::GetRandomNumber()
{
    return (rand() % (gridSize * gridSize));
}


/*****************************************************************
DESCRIPTION : Display the current game progress
******************************************************************/
void MineSweeper::DisplayProgress(bool showMines)
{
    int row = 0;
    int col = 0;

    cout << "\n    ";
    while (col++ < gridSize) cout << col - 1 << " ";
    cout << "\n\n";

    for (row = 0; row < gridSize; row++)
    {
        cout << row << "   ";
        for (col = 0; col < gridSize; col++)
        {
            if (IsMine(row, col) == true)
            {
                if (showMines == true) cout << boardCoordinates[row][col] << " ";
                else cout << ". ";
            }
            else
            {
                cout << boardCoordinates[row][col] << " ";
            }

            // print extra space if column number is two digits
            if (col >= 10)
            {
                cout << " ";
            }
        }
        cout << '\n';
    }
}


/*****************************************************************
DESCRIPTION : Validate whether the given co-ordinates are within the given grid size or not
******************************************************************/
bool MineSweeper::IsCoordinatesValid(int row, int col)
{
    if ((row >= 0) && (row < gridSize) && (col >= 0) && (col < gridSize)) return true;

    return false;
}


/*****************************************************************
DESCRIPTION : Determine whether the mine is located at the given co-ordinates or not
******************************************************************/
bool MineSweeper::IsMine(int row, int col)
{
    return (boardCoordinates[row][col] == '*') ? true : false;
}


/*****************************************************************
DESCRIPTION : Calculate the adjacent mines count for the given co-ordinates
******************************************************************/
int MineSweeper::CalculateAdjacentMinesCount(int row, int col)
{
    int count = 0;

    if (IsCoordinatesValid(row - 1, col) && IsMine(row - 1, col)) count++;   // N
    if (IsCoordinatesValid(row, col + 1) && IsMine(row, col + 1)) count++;   // E
    if (IsCoordinatesValid(row, col - 1) && IsMine(row, col - 1)) count++;   // W
    if (IsCoordinatesValid(row + 1, col) && IsMine(row + 1, col)) count++;   // S
    if (IsCoordinatesValid(row - 1, col + 1) && IsMine(row - 1, col + 1)) count++;   // NE
    if (IsCoordinatesValid(row - 1, col - 1) && IsMine(row - 1, col - 1)) count++;   // NW
    if (IsCoordinatesValid(row + 1, col + 1) && IsMine(row + 1, col + 1)) count++;   // SE
    if (IsCoordinatesValid(row + 1, col - 1) && IsMine(row + 1, col - 1)) count++;   // SW

    return (count);
}


/*****************************************************************
DESCRIPTION : Main driver method which does most of the job
              INPUT: (row, column) co-oridinates
                     totalMovesLeft; number of moves remaining
              OUTPUT: true; Hit mine, game end
                      false: still few moves left (set in totalMovesLeft)
******************************************************************/
bool MineSweeper::ValidateCoordinatesRecursive(int row, int col, int &totalMovesLeft)
{
    int adjMinesCount;

    // if its a number means we have already visited this cell, continue with next
    if (boardCoordinates[row][col] >= '0' && boardCoordinates[row][col] <= '8') {
        // cout << boardCoordinates[row][col] << " boardCoordinates[" << row << "][" << col << "] ret false\n"; 
        return false;
    }

    // clicked on mine means game over!!
    if (boardCoordinates[row][col] == '*')
    {
        DisplayProgress(true);
        cout << "\n\nYou hit the mine, game end\n";
        return true;
    }

    // calculate the number of adjacent mines and reveal to the user
    adjMinesCount = CalculateAdjacentMinesCount(row, col);
    (totalMovesLeft)--;
    boardCoordinates[row][col] = '0' + adjMinesCount;    // store ASCII value of char

    // if there are no adjasent mines, then reveal all of its neighbours count untill the presence of mine
    if (adjMinesCount == 0)
    {
        // visit all 8 adjacent cells until we reach the mine
        // goto end of North recursively
        if (IsCoordinatesValid(row - 1, col) && !IsMine(row - 1, col))
        {
            ValidateCoordinatesRecursive(row - 1, col, totalMovesLeft);
        }
        // next goto East
        if (IsCoordinatesValid(row, col + 1) && !IsMine(row, col + 1))
        {
            ValidateCoordinatesRecursive(row, col + 1, totalMovesLeft);
        }
        // next goto West
        if (IsCoordinatesValid(row, col - 1) && !IsMine(row, col - 1))
        {
            ValidateCoordinatesRecursive(row, col - 1, totalMovesLeft);
        }
        // next goto South
        if (IsCoordinatesValid(row + 1, col) && !IsMine(row + 1, col))
        {
            ValidateCoordinatesRecursive(row + 1, col, totalMovesLeft);
        }

        // next goto corners
        // goto NE
        if (IsCoordinatesValid(row - 1, col + 1) && !IsMine(row - 1, col + 1))
        {
            ValidateCoordinatesRecursive(row - 1, col + 1, totalMovesLeft);
        }
        // goto NW
        if (IsCoordinatesValid(row - 1, col - 1) && !IsMine(row - 1, col - 1))
        {
            ValidateCoordinatesRecursive(row - 1, col - 1, totalMovesLeft);
        }
        // goto SE
        if (IsCoordinatesValid(row + 1, col + 1) && !IsMine(row + 1, col + 1))
        {
            ValidateCoordinatesRecursive(row + 1, col + 1, totalMovesLeft);
        }
        // goto SW
        if (IsCoordinatesValid(row + 1, col - 1) && !IsMine(row + 1, col - 1))
        {
            ValidateCoordinatesRecursive(row + 1, col - 1, totalMovesLeft);
        }
    }

    return false;
}


/*****************************************************************
DESCRIPTION : Move mine from the given position to the first available position
******************************************************************/
void MineSweeper::ReplaceMinePosition(int row, int col)
{
    for (int r = 0; r < gridSize; r++)
    {
        for (int c = 0; c < gridSize; c++)
        {
            // pick up the first location where the mine is not present and
            // swap it with the given co-ordinates
            if (boardCoordinates[r][c] != '*')
            {
                boardCoordinates[r][c] = '*';
                boardCoordinates[row][col] = '.';
#ifndef NDEBUG
                cout << "You hit the mine at first click, relocatint to different cell..\n";
                cout << "Old mine was at (" << row << ", " << col << "), new (" << r << ", " << c << ")\n";
#endif
                return;
            }
        }
    }
}


/*****************************************************************
DESCRIPTION : Get the input coordinates/click location from the player
******************************************************************/
void MineSweeper::GetUserCoordinates(int &row, int &col)
{
#ifndef UNIT_TEST
    cout << "Enter (row, column) seperated by space: ";
    (cin >> row >> col).get();  // consume '\n' 
#else
    row = setRow;
    col = setCol;
#endif
}


/*****************************************************************
DESCRIPTION : Start the game by seeking the input from the player
******************************************************************/
void MineSweeper::StartMineSweeper(void)
{
    int row;
    int col;
    int totalMovesLeft = ((gridSize * gridSize) - numMines);
    bool isFirstMove = true;
    bool isGameFinished = false;

    while (isGameFinished == false)
    {
#ifdef NDEBUG
        DisplayProgress(false);
#else
        DisplayProgress(true);
#endif


        GetUserCoordinates(row, col);
        if (IsCoordinatesValid(row, col) == false)
        {
            cout << "ERROR: Invalid co-ordinates.. Please try again\n";
            continue;
        }
        if ((isFirstMove == true) && (IsMine(row, col) == true))
        {
            ReplaceMinePosition(row, col);
        }
        isFirstMove = false;

        isGameFinished = ValidateCoordinatesRecursive(row, col, totalMovesLeft);
        if ((isGameFinished == false) && (totalMovesLeft == 0))
        {
            // reveal the final layout with all of the mines
            DisplayProgress(true);
            isGameFinished = true;
            cout << "\n\n** You won the game **\n";
        }
#ifndef NDEBUG
        if (isGameFinished == false) cout << "totalMovesLeft=" << totalMovesLeft << '\n';
#endif
    }
}


/*****************************************************************
DESCRIPTION : Insert the mines in random location
              OUTPUT: Mark mine location as '*' in the given board co-ordinates
******************************************************************/
void MineSweeper::InsertMinesRandom(void)
{
    int mineIndex = 0;

    do
    {
        int location = GetRandomNumber();
        int row = location / gridSize;
        int col = location % gridSize;

        if (boardCoordinates[row][col] != '*')
        {
#ifndef NDEBUG
            cout << "mine-" << mineIndex << " Location(row, col)=(" << row << ", " << col << ")\n";
#endif
            boardCoordinates[row][col] = '*';
            mineIndex++;
        }
    } while (mineIndex < numMines);
}


/*****************************************************************
DESCRIPTION : Get player input regarding grid size/number of mines
              ASSUMPTIONS: grid size = number of mines
                           Max grid size is limited to 16 * 16
                           Min grid size is set to 9 * 9
******************************************************************/
void MineSweeper::SetGridSize(void)
{
    cout << "Enter grid size (min 9, max 16): ";
    (cin >> gridSize).get();  // consume '\n'

    if (gridSize > 16) gridSize = 16;
    else if (gridSize < 9) gridSize = 9;

    numMines = gridSize;
}

