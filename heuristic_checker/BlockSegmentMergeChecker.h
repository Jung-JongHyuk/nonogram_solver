#pragma once

#include "HeuristicCheckerInterface.h"
using namespace std;

class BlockSegmentMergeChecker : public HeuristicCheckerInterface
{
	public:
		BlockSegmentMergeChecker();
		BlockSegmentMergeChecker(int rowSize, int colSize);
	
		void adopt_techniqueInRow(int rowIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData);
		void adopt_techniqueInCol(int colIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData);
	
	private:
		//find range of continous set confirmed dot
		pair<int,int> find_rowBlockSegment(int rowIndex, int startColIndex, int endColIndex, ConfirmedDotData& confirmedDotData);
		pair<int,int> find_colBlockSegment(int colIndex, int startRowIndex, int endRowIndex, ConfirmedDotData& confirmedDotData);
};

