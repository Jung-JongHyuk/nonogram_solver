#pragma once

#include "HeuristicCheckerInterface.h"
using namespace std;

class BlockRangeBorderChecker : public HeuristicCheckerInterface
{
	public:
		BlockRangeBorderChecker();
		BlockRangeBorderChecker(int rowSize, int colSize);
	
		BlockRangeBorderChecker& operator=(const BlockRangeBorderChecker& blockRangeBorderChecker);	
	
		void adopt_techniqueInRow(int rowIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData);
		void adopt_techniqueInCol(int colIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData);
	
	private:
		void set_isBlockRangeCheckNeeded(Board& board, BlockRangeData& blockRangeData);
	
		vector<vector<bool>> isBlockRangeLeftBorderCheckNeeded, isBlockRangeRightBorderCheckNeeded, isBlockRangeUpperBorderCheckNeeded, isBlockRangeLowerBorderCheckNeeded;
		bool isBlockRangeCheckNeededSet;
};

