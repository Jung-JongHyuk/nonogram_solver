#pragma once

#include "HeuristicCheckerInterface.hpp"
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

//MaxBlockSizeChecker class

MaxBlockSizeChecker::MaxBlockSizeChecker() : MaxBlockSizeChecker(0,0) {}

MaxBlockSizeChecker::MaxBlockSizeChecker(int rowSize, int colSize) : HeuristicCheckerInterface(rowSize, colSize)
{
	checkerInfo = CheckerInfo(true, true, true, false, true, false, "MaxBlockSizeChecker");
}

void MaxBlockSizeChecker::adopt_techniqueInRow(int rowIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
	for(int i = 0; i < colSize; i++)
	{
		if(confirmedDotData.get_isSetConfirmed(rowIndex, i))
		{
			continue;
		}
		
		//check continuous set confirmed range if current dot is set confirmed
		pair<int,int> setConfirmedRange = get_continousSetConfirmedDotRangeInRow(rowIndex, i, confirmedDotData);
		
		if(setConfirmedRange.second - setConfirmedRange.first == 0)
		{
			continue; //if there is no set confirmed dot next to current dot, check next dot
		}
		
		//get maximun block size by checking intersection of maximum possible block size of each dot
		int maxPossibleBlockSize = get_possibleRowBlockSize(rowIndex, setConfirmedRange.first, setConfirmedRange.second, board, blockRangeData);
		
		//if block size is bigger than max possible blocksize, current dot must be blank confirmed 
		if(setConfirmedRange.second - setConfirmedRange.first >= maxPossibleBlockSize)
		{
			confirm_blank_inRowTechnique(rowIndex, i, confirmedDotData);
		}
	}
}

void MaxBlockSizeChecker::adopt_techniqueInCol(int colIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
	for(int i = 0; i < rowSize; i++)
	{
		if(confirmedDotData.get_isSetConfirmed(i, colIndex))
		{
			continue;
		}
		
		//check continuous set confirmed range if current dot is set confirmed
		pair<int,int> setConfirmedRange = get_continousSetConfirmedDotRangeInCol(i, colIndex, confirmedDotData);
		
		if(setConfirmedRange.second - setConfirmedRange.first == 0)
		{
			continue; //if there is no set confirmed dot next to current dot, check next dot
		}
		
		//get maximun block size by checking intersection of maximum possible block size of each dot
		int maxPossibleBlockSize = get_possibleColBlockSize(setConfirmedRange.first, setConfirmedRange.second, colIndex, board, blockRangeData);
		
		//if block size is bigger than max possible blocksize, current dot must be blank confirmed 
		if(setConfirmedRange.second - setConfirmedRange.first >= maxPossibleBlockSize)
		{
			confirm_blank_inColTechnique(i, colIndex, confirmedDotData);
		}
	}
}

pair<int,int> MaxBlockSizeChecker::get_continousSetConfirmedDotRangeInRow(int rowIndex, int colIndex, ConfirmedDotData& confirmedDotData)
{
	pair<int,int> setConfirmedRange(-1, -1);
	
	for(int i = colIndex - 1; i >= 0; i -= 1)
	{
		if(!confirmedDotData.get_isSetConfirmed(rowIndex, i))
		{
			setConfirmedRange.first = i + 1;
			break;
		}
	}
	
	for(int i = colIndex + 1; i < colSize; i++)
	{
		if(!confirmedDotData.get_isSetConfirmed(rowIndex, i))
		{
			setConfirmedRange.second = i - 1;
			break;
		}
	}
	
	setConfirmedRange.first = setConfirmedRange.first == -1 ? 0 : setConfirmedRange.first;
	setConfirmedRange.second = setConfirmedRange.second == -1 ? colSize - 1 : setConfirmedRange.second;
	return setConfirmedRange;
}
		
pair<int,int> MaxBlockSizeChecker::get_continousSetConfirmedDotRangeInCol(int rowIndex, int colIndex, ConfirmedDotData& confirmedDotData)
{
	pair<int,int> setConfirmedRange(-1, -1);
	
	for(int i = rowIndex - 1; i >= 0; i -= 1)
	{
		if(!confirmedDotData.get_isSetConfirmed(i, colIndex))
		{
			setConfirmedRange.first = i + 1;
			break;
		}
	}
	
	for(int i = rowIndex + 1; i < rowSize; i++)
	{
		if(!confirmedDotData.get_isSetConfirmed(i, colIndex))
		{
			setConfirmedRange.second = i - 1;
			break;
		}
	}
	
	setConfirmedRange.first = setConfirmedRange.first == -1 ? 0 : setConfirmedRange.first;
	setConfirmedRange.second = setConfirmedRange.second == -1 ? rowSize - 1 : setConfirmedRange.second;
	return setConfirmedRange;
}

int MaxBlockSizeChecker::get_possibleRowBlockSize(int rowIndex, int colStartIndex, int colEndIndex, Board& board, BlockRangeData& blockRangeData)
{
	int numOfBlock = board.get_numOfRowHint(rowIndex);
	int currentMaxPossibleBlockSize = -1;
	 
	for(int i = 0; i < numOfBlock; i++)
	{
		pair<int,int> blockRange = blockRangeData.get_rowBlockRange(rowIndex, i);
		
		if(colStartIndex > blockRange.second)
		{
			continue;
		}
		else if(colEndIndex < blockRange.first)
		{
			break;
		}
		else if(colStartIndex >= blockRange.first && colEndIndex <= blockRange.second)
		{
			int currentBlockSize = board.get_rowHint(rowIndex, i);
			currentMaxPossibleBlockSize = currentMaxPossibleBlockSize < currentBlockSize ? currentBlockSize : currentMaxPossibleBlockSize;
		}
	}
	
	return currentMaxPossibleBlockSize;
}

int MaxBlockSizeChecker::get_possibleColBlockSize(int rowStartIndex, int rowEndIndex, int colIndex, Board& board, BlockRangeData& blockRangeData)
{
	int numOfBlock = board.get_numOfColHint(colIndex);
	int currentMaxPossibleBlockSize = -1;
	 
	for(int i = 0; i < numOfBlock; i++)
	{
		pair<int,int> blockRange = blockRangeData.get_colBlockRange(colIndex, i);
		
		if(rowStartIndex > blockRange.second)
		{
			continue;
		}
		else if(rowEndIndex < blockRange.first)
		{
			break;
		}
		else if(rowStartIndex >= blockRange.first && rowEndIndex <= blockRange.second)
		{
			int currentBlockSize = board.get_colHint(colIndex, i);
			currentMaxPossibleBlockSize = currentMaxPossibleBlockSize < currentBlockSize ? currentBlockSize : currentMaxPossibleBlockSize;
		}
	}
	
	return currentMaxPossibleBlockSize;
}

