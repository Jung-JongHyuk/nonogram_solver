#pragma once

#include "HeuristicCheckerInterface.hpp"
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

//BlockRangeBorderChecker class

BlockRangeBorderChecker::BlockRangeBorderChecker() : BlockRangeBorderChecker(0,0) {}

BlockRangeBorderChecker::BlockRangeBorderChecker(int rowSize, int colSize) : HeuristicCheckerInterface(rowSize, colSize)
{
	checkerInfo = CheckerInfo(true, false, true, true, true, true, "BlockRangeBorderChecker");
	isBlockRangeCheckNeededSet = false;
}

BlockRangeBorderChecker& BlockRangeBorderChecker::operator=(const BlockRangeBorderChecker& blockRangeBorderChecker)
{
	HeuristicCheckerInterface::operator=(blockRangeBorderChecker);
	
	if(this != &blockRangeBorderChecker)
	{
		isBlockRangeLeftBorderCheckNeeded = blockRangeBorderChecker.isBlockRangeLeftBorderCheckNeeded;
		isBlockRangeRightBorderCheckNeeded = blockRangeBorderChecker.isBlockRangeRightBorderCheckNeeded;
		isBlockRangeUpperBorderCheckNeeded = blockRangeBorderChecker.isBlockRangeUpperBorderCheckNeeded;
		isBlockRangeLowerBorderCheckNeeded = blockRangeBorderChecker.isBlockRangeLowerBorderCheckNeeded;
		isBlockRangeCheckNeededSet = blockRangeBorderChecker.isBlockRangeCheckNeededSet;
	}
	
	return *this;
}

void BlockRangeBorderChecker::adopt_techniqueInRow(int rowIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
	if(!isBlockRangeCheckNeededSet)
	{
		set_isBlockRangeCheckNeeded(board, blockRangeData);
		isBlockRangeCheckNeededSet = true;
	}
	
	int numOfBlock = board.get_numOfRowHint(rowIndex);
	
	for(int i = 0; i < numOfBlock; i++)
	{
		pair<int,int> currentBlockRange = blockRangeData.get_rowBlockRange(rowIndex, i);
		int currentBlockSize = board.get_rowHint(rowIndex, i);
		
		if(isBlockRangeLeftBorderCheckNeeded[rowIndex][i] && confirmedDotData.get_isSetConfirmed(rowIndex, currentBlockRange.first) && (i == 0 || currentBlockRange.first > blockRangeData.get_rowBlockRange(rowIndex, i - 1).second))
		{
			for(int j = currentBlockRange.first + 1; j <= currentBlockRange.first + currentBlockSize - 1; j++)
			{
				confirm_set_inRowTechnique(rowIndex, j, confirmedDotData);
			}
			
			if(currentBlockRange.first > 0)
			{
				confirm_blank_inRowTechnique(rowIndex, currentBlockRange.first - 1, confirmedDotData);
			}
			
			if(currentBlockRange.first + currentBlockSize < colSize)
			{
				confirm_blank_inRowTechnique(rowIndex, currentBlockRange.first + currentBlockSize, confirmedDotData);
			}
			
			if(currentBlockRange.second > currentBlockRange.first + currentBlockSize - 1)
			{
				currentBlockRange.second = currentBlockRange.first + currentBlockSize - 1;
				change_rowBlockRange(rowIndex, i, currentBlockRange, blockRangeData);
			}
			
			if(i < numOfBlock - 1)
			{
				pair<int,int> nextBlockRange = blockRangeData.get_rowBlockRange(rowIndex, i + 1);
				
				if(nextBlockRange.first < currentBlockRange.second + 2)
				{
					nextBlockRange.first = currentBlockRange.second + 2;
					change_rowBlockRange(rowIndex, i + 1, nextBlockRange, blockRangeData);
				}
			}
			
			if(i > 0)
			{
				pair<int,int> prevBlockRange = blockRangeData.get_rowBlockRange(rowIndex, i - 1);
				
				if(prevBlockRange.second > currentBlockRange.first - 2)
				{
					prevBlockRange.second = currentBlockRange.first - 2;
					change_rowBlockRange(rowIndex, i - 1, prevBlockRange, blockRangeData);
				}
			}
			
			isBlockRangeLeftBorderCheckNeeded[rowIndex][i] = false;
		}
		
		if(isBlockRangeRightBorderCheckNeeded[rowIndex][i] && confirmedDotData.get_isSetConfirmed(rowIndex, currentBlockRange.second) && (i == numOfBlock - 1 || currentBlockRange.second < blockRangeData.get_rowBlockRange(rowIndex, i + 1).first))
		{
			for(int j = currentBlockRange.second - currentBlockSize + 1; j <= currentBlockRange.second - 1; j++)
			{
				confirm_set_inRowTechnique(rowIndex, j, confirmedDotData);
			}
			
			if(currentBlockRange.second - currentBlockSize >= 0)
			{
				confirm_blank_inRowTechnique(rowIndex, currentBlockRange.second - currentBlockSize, confirmedDotData);
			}
			
			if(currentBlockRange.second + 1 < colSize)
			{
				confirm_blank_inRowTechnique(rowIndex, currentBlockRange.second + 1, confirmedDotData);
			}
			
			if(currentBlockRange.first < currentBlockRange.second - currentBlockSize + 1)
			{
				currentBlockRange.first = currentBlockRange.second - currentBlockSize + 1;
				change_rowBlockRange(rowIndex, i, currentBlockRange, blockRangeData);
			}
			
			if(i < numOfBlock - 1)
			{
				pair<int,int> nextBlockRange = blockRangeData.get_rowBlockRange(rowIndex, i + 1);
				
				if(nextBlockRange.first < currentBlockRange.second + 2)
				{
					nextBlockRange.first = currentBlockRange.second + 2;
					change_rowBlockRange(rowIndex, i + 1, nextBlockRange, blockRangeData);
				}
			}
			
			if(i > 0)
			{
				pair<int,int> prevBlockRange = blockRangeData.get_rowBlockRange(rowIndex, i - 1);
				
				if(prevBlockRange.second > currentBlockRange.first - 2)
				{
					prevBlockRange.second = currentBlockRange.first - 2;
					change_rowBlockRange(rowIndex, i - 1, prevBlockRange, blockRangeData);
				}
			}
			
			isBlockRangeRightBorderCheckNeeded[rowIndex][i] = false;
		}
	}
}

void BlockRangeBorderChecker::adopt_techniqueInCol(int colIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
	int numOfBlock = board.get_numOfColHint(colIndex);
	
	for(int i = 0; i < numOfBlock; i++)
	{
		pair<int,int> currentBlockRange = blockRangeData.get_colBlockRange(colIndex, i);
		int currentBlockSize = board.get_colHint(colIndex, i);
		
		if(isBlockRangeUpperBorderCheckNeeded[colIndex][i] && confirmedDotData.get_isSetConfirmed(currentBlockRange.first, colIndex) && (i == 0 || currentBlockRange.first > blockRangeData.get_colBlockRange(colIndex, i - 1).second))
		{
			for(int j = currentBlockRange.first + 1; j <= currentBlockRange.first + currentBlockSize - 1; j++)
			{
				confirm_set_inColTechnique(j, colIndex, confirmedDotData);
			}
			
			if(currentBlockRange.first > 0)
			{
				confirm_blank_inColTechnique(currentBlockRange.first - 1, colIndex, confirmedDotData);
			}
			
			if(currentBlockRange.first + currentBlockSize < rowSize)
			{
				confirm_blank_inRowTechnique(currentBlockRange.first + currentBlockSize, colIndex, confirmedDotData);
			}
			
			if(currentBlockRange.second > currentBlockRange.first + currentBlockSize - 1)
			{
				currentBlockRange.second = currentBlockRange.first + currentBlockSize - 1;
				change_colBlockRange(colIndex, i, currentBlockRange, blockRangeData);
			}
			
			if(i < numOfBlock - 1)
			{
				pair<int,int> nextBlockRange = blockRangeData.get_colBlockRange(colIndex, i + 1);
				
				if(nextBlockRange.first < currentBlockRange.second + 2)
				{
					nextBlockRange.first = currentBlockRange.second + 2;
					change_colBlockRange(colIndex, i + 1, nextBlockRange, blockRangeData);
				}
			}
			
			if(i > 0)
			{
				pair<int,int> prevBlockRange = blockRangeData.get_colBlockRange(colIndex, i - 1);
				
				if(prevBlockRange.second > currentBlockRange.first - 2)
				{
					prevBlockRange.second = currentBlockRange.first - 2;
					change_colBlockRange(colIndex, i - 1, prevBlockRange, blockRangeData);
				}
			}
			
			isBlockRangeUpperBorderCheckNeeded[colIndex][i] = false;
		}
		
		if(isBlockRangeLowerBorderCheckNeeded[colIndex][i] && confirmedDotData.get_isSetConfirmed(currentBlockRange.second, colIndex) && (i == numOfBlock - 1 || currentBlockRange.second < blockRangeData.get_colBlockRange(colIndex, i + 1).first))
		{
			for(int j = currentBlockRange.second - currentBlockSize + 1; j <= currentBlockRange.second - 1; j++)
			{
				confirm_set_inColTechnique(j, colIndex, confirmedDotData);
			}
			
			if(currentBlockRange.second - currentBlockSize >= 0)
			{
				confirm_blank_inColTechnique(currentBlockRange.second - currentBlockSize, colIndex, confirmedDotData);
			}
			
			if(currentBlockRange.second + 1 < rowSize)
			{
				confirm_blank_inColTechnique(currentBlockRange.second + 1, colIndex, confirmedDotData);
			}
			
			if(currentBlockRange.first < currentBlockRange.second - currentBlockSize + 1)
			{
				currentBlockRange.first = currentBlockRange.second - currentBlockSize + 1;
				change_colBlockRange(colIndex, i, currentBlockRange, blockRangeData);
			}
			
			if(i < numOfBlock - 1)
			{
				pair<int,int> nextBlockRange = blockRangeData.get_colBlockRange(colIndex, i + 1);
				
				if(nextBlockRange.first < currentBlockRange.second + 2)
				{
					nextBlockRange.first = currentBlockRange.second + 2;
					change_colBlockRange(colIndex, i + 1, nextBlockRange, blockRangeData);
				}
			}
			
			if(i > 0)
			{
				pair<int,int> prevBlockRange = blockRangeData.get_colBlockRange(colIndex, i - 1);
				
				if(prevBlockRange.second > currentBlockRange.first - 2)
				{
					prevBlockRange.second = currentBlockRange.first - 2;
					change_colBlockRange(colIndex, i - 1, prevBlockRange, blockRangeData);
				}
			}
			
			isBlockRangeLowerBorderCheckNeeded[colIndex][i] = false;
		}
	}
}

void BlockRangeBorderChecker::set_isBlockRangeCheckNeeded(Board& board, BlockRangeData& blockRangeData)
{
	isBlockRangeLeftBorderCheckNeeded.resize(rowSize);
	isBlockRangeRightBorderCheckNeeded.resize(rowSize);
	isBlockRangeUpperBorderCheckNeeded.resize(colSize);
	isBlockRangeLowerBorderCheckNeeded.resize(colSize);
	
	for(int i = 0; i < rowSize; i++)
	{
		int numOfBlock = board.get_numOfRowHint(i);
		isBlockRangeLeftBorderCheckNeeded[i].resize(numOfBlock, true);
		isBlockRangeRightBorderCheckNeeded[i].resize(numOfBlock, true);
	}
	
	for(int i = 0; i < colSize; i++)
	{
		int numOfBlock = board.get_numOfColHint(i);
		isBlockRangeUpperBorderCheckNeeded[i].resize(numOfBlock, true);
		isBlockRangeLowerBorderCheckNeeded[i].resize(numOfBlock, true);
	}
}

