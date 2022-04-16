/*******************************************************************
 * FILE NAME  : MineSweeperMain.cpp
 * 
 * Author: Rahul Devireddy
 * 
 ********************************************************************/

#include "MineSweeper.h"

/*****************************************************************
DESCRIPTION : Starts from here
******************************************************************/
int main()
{
    MineSweeper mineSweeper;

    mineSweeper.SetGridSize();
    mineSweeper.InsertMinesRandom();
    mineSweeper.StartMineSweeper();
    return 0;
}
