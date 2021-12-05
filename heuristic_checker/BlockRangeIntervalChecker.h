#pragma once

#include "HeuristicCheckerInterface.h"
using namespace std;

class BlockRangeIntervalChecker : public HeuristicCheckerInterface
{
	public:
		BlockRangeIntervalChecker();
		BlockRangeIntervalChecker(int rowSize, int colSize);
	
		void adopt_techniqueInRow(int rowIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData);
		void adopt_techniqueInCol(int colIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData);
};

