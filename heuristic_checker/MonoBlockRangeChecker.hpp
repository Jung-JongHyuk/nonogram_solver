#pragma once

#include "HeuristicCheckerInterface.hpp"
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

//MonoBlockRangeChecker class

MonoBlockRangeChecker::MonoBlockRangeChecker() : MonoBlockRangeChecker(0,0) {}

MonoBlockRangeChecker::MonoBlockRangeChecker(int rowSize, int colSize) : HeuristicCheckerInterface(rowSize, colSize)
{
	checkerInfo = CheckerInfo(true, false, true, false, true, false, "MonoBlockRangeChecekr");
}

void MonoBlockRangeChecker::adopt_techniqueInRow(int rowIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
	int numOfBlock = board.get_numOfRowHint(rowIndex);
	
	for(int i = 0; i < numOfBlock; i++) //for each block in row
	{
		pair<int,int> currentBlockRange = blockRangeData.get_rowBlockRange(rowIndex, i);
		int blockRangeStartIndex = currentBlockRange.first;
		
		if(!confirmedDotData.get_isSetConfirmed(rowIndex, blockRangeStartIndex))
		{
			continue;
		}
		
		bool isInSingleBlockRange = check_isInSingleBlockRangeInRow(rowIndex, blockRangeStartIndex, i, board, blockRangeData);
		bool isInMonoBlockRangeOnly = check_isInMonoBlockRangeOnlyInRow(rowIndex, blockRangeStartIndex, i, board, blockRangeData);
		
		if((isInSingleBlockRange || (!isInSingleBlockRange && isInMonoBlockRangeOnly)) && blockRangeStartIndex > 0)
		{
			confirm_blank_inRowTechnique(rowIndex, blockRangeStartIndex - 1, confirmedDotData);
		}
	}
	
	for(int i = 0; i < numOfBlock; i++) //for each block in row
	{
		pair<int,int> currentBlockRange = blockRangeData.get_rowBlockRange(rowIndex, i);
		int blockRangeEndIndex = currentBlockRange.second;
		
		if(!confirmedDotData.get_isSetConfirmed(rowIndex, blockRangeEndIndex))
		{
			continue;
		}
		
		bool isInSingleBlockRange = check_isInSingleBlockRangeInRow(rowIndex, blockRangeEndIndex, i, board, blockRangeData);
		bool isInMonoBlockRangeOnly = check_isInMonoBlockRangeOnlyInRow(rowIndex, blockRangeEndIndex, i, board, blockRangeData);
		
		if((isInSingleBlockRange || (!isInSingleBlockRange && isInMonoBlockRangeOnly)) && blockRangeEndIndex < colSize - 1)
		{
			confirm_blank_inRowTechnique(rowIndex, blockRangeEndIndex + 1, confirmedDotData);
		}
	}
}

void MonoBlockRangeChecker::adopt_techniqueInCol(int colIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
	int numOfBlock = board.get_numOfColHint(colIndex);
	
	for(int i = 0; i < numOfBlock; i++) //for each block in col
	{
		pair<int,int> currentBlockRange = blockRangeData.get_colBlockRange(colIndex, i);
		int blockRangeStartIndex = currentBlockRange.first;
	
		if(!confirmedDotData.get_isSetConfirmed(blockRangeStartIndex, colIndex))
		{
			continue;
		}
		
		bool isInSingleBlockRange = check_isInSingleBlockRangeInCol(blockRangeStartIndex, colIndex, i, board, blockRangeData);
		bool isInMonoBlockRangeOnly = check_isInMonoBlockRangeOnlyInCol(blockRangeStartIndex, colIndex, i, board, blockRangeData);
		
		if((isInSingleBlockRange || (!isInSingleBlockRange && isInMonoBlockRangeOnly)) && blockRangeStartIndex > 0)
		{
			confirm_blank_inColTechnique(blockRangeStartIndex - 1, colIndex, confirmedDotData);
		}
	}
	
	for(int i = 0; i < numOfBlock; i++) //for each block in col
	{
		pair<int,int> currentBlockRange = blockRangeData.get_colBlockRange(colIndex, i);
		int blockRangeEndIndex = currentBlockRange.second;
		
		if(!confirmedDotData.get_isSetConfirmed(blockRangeEndIndex, colIndex))
		{
			continue;
		}
		
		bool isInSingleBlockRange = check_isInSingleBlockRangeInCol(blockRangeEndIndex, colIndex, i, board, blockRangeData);
		bool isInMonoBlockRangeOnly = check_isInMonoBlockRangeOnlyInCol(blockRangeEndIndex, colIndex, i, board, blockRangeData);
		
		if((isInSingleBlockRange || (!isInSingleBlockRange && isInMonoBlockRangeOnly)) && blockRangeEndIndex < rowSize - 1)
		{
			confirm_blank_inColTechnique(blockRangeEndIndex + 1, colIndex, confirmedDotData);
		}
	}
}

bool MonoBlockRangeChecker::check_isInMonoBlockRangeOnlyInRow(int rowIndex, int colIndex, int blockIndex, Board& board, BlockRangeData& blockRangeData)
{
	int numOfBlock = board.get_numOfRowHint(rowIndex);
	
	for(int i = 0; i < numOfBlock; i++)
	{
		pair<int,int> currentBlockRange = blockRangeData.get_rowBlockRange(rowIndex, i);
		int currentBlockSize = board.get_rowHint(rowIndex, i);
			
		if(i == blockIndex || colIndex > currentBlockRange.second)
		{
			continue;
		}
		else if(colIndex < currentBlockRange.first)
		{
			return true;
		}
		else if(colIndex >= currentBlockRange.first && colIndex <= currentBlockRange.second)
		{
			if(currentBlockSize != 1)
			{
				return false;
			}
		}
	}
	
	return true;
}

bool MonoBlockRangeChecker::check_isInMonoBlockRangeOnlyInCol(int rowIndex, int colIndex, int blockIndex, Board& board, BlockRangeData& blockRangeData)
{
	int numOfBlock = board.get_numOfColHint(colIndex);
	
	for(int i = 0; i < numOfBlock; i++)
	{
		pair<int,int> currentBlockRange = blockRangeData.get_colBlockRange(colIndex, i);
		int currentBlockSize = board.get_colHint(colIndex, i);
			
		if(i == blockIndex || rowIndex > currentBlockRange.second)
		{
			continue;
		}
		else if(rowIndex < currentBlockRange.first)
		{
			return true;
		}
		else if(rowIndex >= currentBlockRange.first && rowIndex <= currentBlockRange.second)
		{
			if(currentBlockSize != 1)
			{
				return false;
			}
		}
	}
	
	return true;
}

bool MonoBlockRangeChecker::check_isInSingleBlockRangeInRow(int rowIndex, int colIndex, int blockIndex, Board& board, BlockRangeData& blockRangeData)
{
	int numOfBlock = board.get_numOfRowHint(rowIndex);
	
	for(int i = 0; i < numOfBlock; i++)
	{
		pair<int,int> currentBlockRange = blockRangeData.get_rowBlockRange(rowIndex, i);
		int currentBlockSize = board.get_rowHint(rowIndex, i);
			
		if(i == blockIndex || colIndex > currentBlockRange.second)
		{
			continue;
		}
		else if(colIndex < currentBlockRange.first)
		{
			return true;
		}
		else if(colIndex >= currentBlockRange.first && colIndex <= currentBlockRange.second)
		{
			return false;
		}
	}
	
	return true;
}

bool MonoBlockRangeChecker::check_isInSingleBlockRangeInCol(int rowIndex, int colIndex, int blockIndex, Board& board, BlockRangeData& blockRangeData)
{
	int numOfBlock = board.get_numOfColHint(colIndex);
	
	for(int i = 0; i < numOfBlock; i++)
	{
		pair<int,int> currentBlockRange = blockRangeData.get_colBlockRange(colIndex, i);
		int currentBlockSize = board.get_colHint(colIndex, i);
			
		if(i == blockIndex || rowIndex > currentBlockRange.second)
		{
			continue;
		}
		else if(rowIndex < currentBlockRange.first)
		{
			return true;
		}
		else if(rowIndex >= currentBlockRange.first && rowIndex <= currentBlockRange.second)
		{
			return false;
		}
	}
	
	return true;
}

