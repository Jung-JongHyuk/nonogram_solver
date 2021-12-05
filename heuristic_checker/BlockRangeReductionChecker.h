#pragma once

#include "HeuristicCheckerInterface.h"
using namespace std;

class BlockRangeReductionChecker : public HeuristicCheckerInterface
{
	public:
		BlockRangeReductionChecker();
		BlockRangeReductionChecker(int rowSize, int colSize);
	
		void adopt_techniqueInRow(int rowIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData);
		void adopt_techniqueInCol(int colIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData);
};

