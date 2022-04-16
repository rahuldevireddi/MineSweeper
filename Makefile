all: MineSweeper MineSweeperDebug test
LD_LIBRARIES = -lCppUTest

MineSweeper: MineSweeper.o MineSweeperMain.o
	g++ -g -o MineSweeper MineSweeper.o MineSweeperMain.o

MineSweeperDebug: MineSweeperDebug.o MineSweeperMain.o
	g++ -g -o MineSweeperDebug MineSweeperDebug.o MineSweeperMain.o

test: ut_MineSweeper.o MineSweeper.o
	g++ -g -o ut_MineSweeper ut_MineSweeper.o MineSweeper.o $(LD_LIBRARIES)

ut_MineSweeper.o: ut_MineSweeper.cpp
	g++ -DUNIT_TEST -g -c ut_MineSweeper.cpp

MineSweeper.o: MineSweeper.cpp
	g++ -DNDEBUG -g -c MineSweeper.cpp

MineSweeperDebug.o: MineSweeper.cpp
	g++ -g -c MineSweeper.cpp -o MineSweeperDebug.o

MineSweeperMain.o: MineSweeperMain.cpp
	g++ -g -c MineSweeperMain.cpp

clean:
	rm -f *.o MineSweeper MineSweeperDebug ut_MineSweeper