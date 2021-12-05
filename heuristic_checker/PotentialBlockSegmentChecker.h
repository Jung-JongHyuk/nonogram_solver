#pragma once

#include "HeuristicCheckerInterface.h"
using namespace std;

class PotentialBlockSegmentChecker : public HeuristicCheckerInterface
{
	public:
		PotentialBlockSegmentChecker();
		PotentialBlockSegmentChecker(int rowSize, int colSize);
	
		void adopt_techniqueInRow(int rowIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData);
		void adopt_techniqueInCol(int colIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData);
	
	private:
		//find range of continous not blank confirmed dot
		pair<int,int> find_rowPotentialBlockSegment(int rowIndex, int startColIndex, int endColIndex, ConfirmedDotData& confirmedDotData);
		pair<int,int> find_colPotentialBlockSegment(int colIndex, int startRowIndex, int endRowIndex, ConfirmedDotData& confirmedDotData);
	
		//isInSingleBlockRange : true if there is no other blockRange includes dot except blockIndex
		bool check_isInSingleBlockRangeInRow(int rowIndex, int colIndex, int blockIndex, Board& board, BlockRangeData& blockRangeData);
		bool check_isInSingleBlockRangeInCol(int rowIndex, int colIndex, int blockIndex, Board& board, BlockRangeData& blockRangeData);
};

