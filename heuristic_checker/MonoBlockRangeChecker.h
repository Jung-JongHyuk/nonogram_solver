#pragma once

#include "HeuristicCheckerInterface.h"
using namespace std;

class MonoBlockRangeChecker : public HeuristicCheckerInterface
{
	public:
		MonoBlockRangeChecker();
		MonoBlockRangeChecker(int rowSize, int colSize);
	
		void adopt_techniqueInRow(int rowIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData);
		void adopt_techniqueInCol(int colIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData);
	
	private:
		//isInMonoBlockRangeOnly : false if there is blockRange except blockIndex which includes dot and block size is over 1
		bool check_isInMonoBlockRangeOnlyInRow(int rowIndex, int colIndex, int blockIndex, Board& board, BlockRangeData& blockRangeData);
		bool check_isInMonoBlockRangeOnlyInCol(int rowIndex, int colIndex, int blockIndex, Board& board, BlockRangeData& blockRangeData);
	
		//isInSingleBlockRange : true if there is no other blockRange includes dot except blockIndex
		bool check_isInSingleBlockRangeInRow(int rowIndex, int colIndex, int blockIndex, Board& board, BlockRangeData& blockRangeData);
		bool check_isInSingleBlockRangeInCol(int rowIndex, int colIndex, int blockIndex, Board& board, BlockRangeData& blockRangeData);
};
