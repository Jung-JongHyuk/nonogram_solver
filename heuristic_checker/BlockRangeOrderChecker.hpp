#pragma once

#include "HeuristicCheckerInterface.hpp"
using namespace std;

class BlockRangeOrderChecker : public HeuristicCheckerInterface
{
	public:
		BlockRangeOrderChecker();
		BlockRangeOrderChecker(int rowSize, int colSize);
		
		void adopt_techniqueInRow(int rowIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData);
		void adopt_techniqueInCol(int colIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData);	
};

//BlockRangeOrderChecker class

BlockRangeOrderChecker::BlockRangeOrderChecker() : BlockRangeOrderChecker(0,0) {}

BlockRangeOrderChecker::BlockRangeOrderChecker(int rowSize, int colSize) : HeuristicCheckerInterface(rowSize, colSize)
{
	checkerInfo = CheckerInfo(false, false, true, false, false, true, "BlockRangeOrderChecker");
}

void BlockRangeOrderChecker::adopt_techniqueInRow(int rowIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
	int numOfBlock = board.get_numOfRowHint(rowIndex);
	
	for(int i = 1; i < numOfBlock; i++)
	{
		pair<int,int> prevBlockRange = blockRangeData.get_rowBlockRange(rowIndex, i - 1);
		pair<int,int> currentBlockRange = blockRangeData.get_rowBlockRange(rowIndex, i);
		
		if(prevBlockRange.first >= currentBlockRange.first)
		{
			currentBlockRange.first = prevBlockRange.first + board.get_rowHint(rowIndex, i - 1) + 1;
			change_rowBlockRange(rowIndex, i, currentBlockRange, blockRangeData);
		}
	}
	
	for(int i = 0; i < numOfBlock - 1; i++)
	{
		pair<int,int> currentBlockRange = blockRangeData.get_rowBlockRange(rowIndex, i);
		pair<int,int> nextBlockRange = blockRangeData.get_rowBlockRange(rowIndex, i + 1);
		
		if(currentBlockRange.second >= nextBlockRange.second)
		{
			currentBlockRange.second = nextBlockRange.second - board.get_rowHint(rowIndex, i + 1) + 1;
			change_rowBlockRange(rowIndex, i, currentBlockRange, blockRangeData);
		}
	}
}

void BlockRangeOrderChecker::adopt_techniqueInCol(int colIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
	int numOfBlock = board.get_numOfColHint(colIndex);
	
	for(int i = 1; i < numOfBlock; i++)
	{
		pair<int,int> prevBlockRange = blockRangeData.get_colBlockRange(colIndex, i - 1);
		pair<int,int> currentBlockRange = blockRangeData.get_colBlockRange(colIndex, i);
		
		if(prevBlockRange.first >= currentBlockRange.first)
		{
			currentBlockRange.first = prevBlockRange.first + board.get_colHint(colIndex, i - 1) + 1;
			change_colBlockRange(colIndex, i, currentBlockRange, blockRangeData);
		}
	}
	
	for(int i = 0; i < numOfBlock - 1; i++)
	{
		pair<int,int> currentBlockRange = blockRangeData.get_colBlockRange(colIndex, i);
		pair<int,int> nextBlockRange = blockRangeData.get_colBlockRange(colIndex, i + 1);
		
		if(currentBlockRange.second >= nextBlockRange.second)
		{
			currentBlockRange.second = nextBlockRange.second - board.get_colHint(colIndex, i + 1) + 1;
			change_colBlockRange(colIndex, i, currentBlockRange, blockRangeData);
		}
	}
}

