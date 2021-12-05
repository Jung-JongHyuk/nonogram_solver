#pragma once

#include <iostream>
#include "data_structure/Board.h"
#include "data_structure/ConfirmedDotData.h"
#include "RuleChecker.h"
#include "DotConfirmEngine.h"
#include "BoardViewer.h"
using namespace std;

class PuzzleSolver
{
	public:
		PuzzleSolver();
		PuzzleSolver(int rowSize, int colSize);
	
		bool solve_puzzle(Board& board);
	
	private:
		void solve_puzzle(int indexCount, int rowHintIndexToApply, Board& board, bool& isSolved); //recursion function of solve_puzzle
		int set_block(int rowIndex, int colIndex, int blockSize, Board& board) const; //set blockSize row block form (rowIndex, colIndex) and return colIndex which dot value is finialy set
		void adopt_heuristicTechnique(int rowIndex, int startColIndex, int endColIndex, int& unconfirmedLowestIndexCount, int currentIndexCount, Board& board);
		bool adopt_absurdityTechnique(int rowIndex, int startColIndex, int endColIndex, Board& board);
		int find_unconfirmedLowestIndexCount(int currentIndexCount);

		//transform function between indexCount and index
		pair<int,int> get_index(int indexCount) const;
		int get_indexCount(int rowIndex, int colIndex) const;
		
		int rowSize, colSize;
		RuleChecker ruleChecker;
		ConfirmedDotData confirmedDotData;
		DotConfirmEngine dotConfirmEngine;
};
