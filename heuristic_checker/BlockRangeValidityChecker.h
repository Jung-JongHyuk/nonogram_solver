#pragma once

#include "HeuristicCheckerInterface.h"
using namespace std;

class BlockRangeValidityChecker : public HeuristicCheckerInterface
{
	public:
		BlockRangeValidityChecker();
		BlockRangeValidityChecker(int rowSize, int colSize);
		
		void adopt_techniqueInRow(int rowIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData);
		void adopt_techniqueInCol(int colIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData);
	
	private:
		//find range of continous set confirmed dot
		pair<int,int> find_rowBlockSegment(int rowIndex, int startColIndex, int endColIndex, ConfirmedDotData& confirmedDotData);
		pair<int,int> find_colBlockSegment(int colIndex, int startRowIndex, int endRowIndex, ConfirmedDotData& confirmedDotData);
	
		//check is block segment is in right / left blockRange
		bool is_rowBlockSegmentIncludedInRightBlockRange(int rowIndex, int blockIndex, int numOfBlock, pair<int,int> blockSegmentRange, BlockRangeData& blockRangeData);
		bool is_rowBlockSegmentIncludedInLeftBlockRange(int rowIndex, int blockIndex, int numOfBlock, pair<int,int> blockSegmentRange, BlockRangeData& blockRangeData);
		bool is_colBlockSegmentIncludedInLowerBlockRange(int colIndex, int blockIndex, int numOfBlock, pair<int,int> blockSegmentRange, BlockRangeData& blockRangeData);
		bool is_colBlockSegmentIncludedInUpperBlockRange(int colIndex, int blockIndex, int numOfBlock, pair<int,int> blockSegmentRange, BlockRangeData& blockRangeData);
};

