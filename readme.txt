MineSweeper console game
------------------------

1. Source code file
   There are total  4 source files. MainSweeperMain.cpp MainSweeper.cpp, MainSweeper.h belongs to
   MainSweeper console game, where as ut_MainSweeper.cpp contains unit tests

2. Pre-requirements
   a) I have used Ubuntu 21.04, g++ for complication. Used CppUTest (https://cpputest.github.io/) as a unit test framework.
      On Ubuntu if g++, make is not installed then run the below commands
        sudo apt-get install g++
        sudo apt-get install build-essential
      Install CppUTest framework to run the unittests
        sudo apt-get install cpputest
      
   b) I'm also able to compile the source files on Windows 10 machine with VSCode (g++), Visual Studio 2022 but not the unit test
      (I need to investigate more on installing CppUTest framework on Window 10)

3. How to compile
   a) On Ubuntu
      Download all of the files to home location, Ex: /home/rahul/MineSweeper and go to MineSweeper directory and run
        make
    b) To clean the exes run "make clean"; Other options include "make MineSweeper", "make MineSweeperDebug", "make test"

4. How to run
    a) Running "make" on the source directory will generate the following executable binaries
        MineSweeper
        MineSweeperDebug
        ut_MainSweeper
    b) MineSweeper is the main console application
       MineSweeperDebug is the debug console application with the actual mines showing on the output so its easy to debug
       ut_MainSweeper is the unit test application
    c) Run the individual binaries using './' prefix
       Example: ./MineSweeperDebug

5) Assumptions
    a) This program uses recurssion to calculate the adjacent mines location. In-order to minimise the stack usage, I have
       set the minimum, maximum board size to 9, 16
    b) User should only provide a single input
       Example: Entering 9 will make the board parameters as 9 x 9
                Entering 16 will make the board parameters as 16 x 16
    c) I have also set total numbers of mines equals to grid size
       Example: If the gridSize is 9, then the total numMines is set to 9
    d) Taking the user input co-ordinates
       For every click, the program will ask row, column numbers belongs to a particular cell. The board layout is as shown below

6) Board representation

        0 1 2 3 4 5 6 7 8 
    
    0   1 2 3 * 1 1 1 1 0 
    1   1 * * 2 1 1 * 1 0 
    2   2 3 2 1 0 1 1 1 0 
    3   * 1 0 0 0 0 0 0 0 
    4   1 1 0 0 0 0 0 0 0 
    5   1 1 0 0 1 1 1 0 0 
    6   * 2 1 1 1 * 2 1 0 
    7   1 2 * 1 1 2 * 1 0 
    8   0 1 1 1 0 1 1 1 0 

    In a 9 x 9 board, each cell is represented by (row, column) numbers
    The first row represents column numbers
    The first column represents row numbers
    Example: (row, column) = (1, 1) contains '*' (represents mine)
             (row, column) = (0, 2) contains '3' (indicating it has 3 adjacent mines) 