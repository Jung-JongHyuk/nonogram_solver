#pragma once

#include "HeuristicCheckerInterface.h"
using namespace std;

class ConfirmCompleteChecker : public HeuristicCheckerInterface
{
	public:
		ConfirmCompleteChecker();
		ConfirmCompleteChecker(int rowSize, int colSize);	
	
		void adopt_techniqueInRow(int rowIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData);
		void adopt_techniqueInCol(int colIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData);
};

