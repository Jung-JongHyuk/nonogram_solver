#pragma once

#include "HeuristicCheckerInterface.h"
using namespace std;

class BlockExpandableChecker : public HeuristicCheckerInterface
{
	public:
		BlockExpandableChecker();
		BlockExpandableChecker(int rowSize, int colSize);
		
		void adopt_techniqueInRow(int rowIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData);
		void adopt_techniqueInCol(int colIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData);
	
	private:
		//find most close blank confirmedDot in range given by parameter. if not exist, return -2, if end of board range is wall, return -1, row/colSize
		int get_leftWallIndex(int rowIndex, int colIndex, int colRangeStart, int colRangeEnd, ConfirmedDotData& confirmedDotData);
		int get_rightWallIndex(int rowIndex, int colIndex, int colRangeStart, int colRangeEnd, ConfirmedDotData& confirmedDotData);
		int get_upperWallIndex(int rowIndex, int colIndex, int rowRangeStart, int rowRangeEnd, ConfirmedDotData& confirmedDotData);
		int get_lowerWallIndex(int rowIndex, int colIndex, int rowRangeStart, int rowRangeEnd, ConfirmedDotData& confirmedDotData);
	
		//find minimum possible blockSize of current dot
		int get_minPossibleRowBlockSize(int rowIndex, int colIndex, Board& board, BlockRangeData& blockRangeData);
		int get_minPossibleColBlockSize(int rowIndex, int colIndex, Board& board, BlockRangeData& blockRangeData);
};

