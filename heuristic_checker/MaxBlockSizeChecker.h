#pragma once

#include "HeuristicCheckerInterface.h"
using namespace std;

class MaxBlockSizeChecker : public HeuristicCheckerInterface
{
	public:
		MaxBlockSizeChecker();
		MaxBlockSizeChecker(int rowSize, int colSize);
	
		void adopt_techniqueInRow(int rowIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData);
		void adopt_techniqueInCol(int colIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData);
	
	private:
		pair<int,int> get_continousSetConfirmedDotRangeInRow(int rowIndex, int colIndex, ConfirmedDotData& confirmedDotData);		
		pair<int,int> get_continousSetConfirmedDotRangeInCol(int rowIndex, int colIndex, ConfirmedDotData& confirmedDotData);
		int get_possibleRowBlockSize(int rowIndex, int colStartIndex, int colEndIndex, Board& board, BlockRangeData& blockRangeData);
		int get_possibleColBlockSize(int rowStartIndex, int rowEndIndex, int colIndex, Board& board, BlockRangeData& blockRangeData);
};

