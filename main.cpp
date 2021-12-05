#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "data_structure/Board.h"
#include "PuzzleSolver.h"
#include "BoardViewer.h"
using namespace std;

int main(int argc, char* argv[])
{
	int rowSize, colSize;
	string buffer;
	ifstream txtFileInput;
    if(argc == 1)
    {
        cout << "Enter puzzle data path" << endl;
        return 0;
    }
    txtFileInput.open(string(argv[1]));
	txtFileInput >> buffer;
	txtFileInput >> buffer;
	rowSize = stoi(buffer);
	txtFileInput >> buffer;
	colSize = stoi(buffer);
    
    Board board(rowSize, colSize);
    txtFileInput >> board;
    
    PuzzleSolver solver(rowSize, colSize);
    clock_t solveStartedTime = clock();
    solver.solve_puzzle(board);
    BoardViewer(rowSize, colSize).print_board(board);
    cout << "time : " << static_cast<float>((clock() - solveStartedTime)) / CLOCKS_PER_SEC << " second" << endl;
    
	return 0;
}

