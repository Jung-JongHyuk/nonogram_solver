#pragma once

#include "HeuristicCheckerInterface.h"
using namespace std;

class BorderChecker : public HeuristicCheckerInterface
{
	public:
		BorderChecker();
		BorderChecker(int rowSize, int colSize);
	
		void adopt_techniqueInRow(int rowIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData);
		void adopt_techniqueInCol(int colIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData);
	
	private:
		vector<bool> isUpperBorderCheckNeeded, isLowerBorderCheckNeeded, isLeftBorderCheckNeeded, isRightBorderCheckNeeded;
};
