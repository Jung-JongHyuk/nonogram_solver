#pragma once

#include "HeuristicCheckerInterface.hpp"
using namespace std;

class IntersectionChecker : public HeuristicCheckerInterface
{
	public:
		IntersectionChecker();
		IntersectionChecker(int rowSize, int colSize);
	
		void adopt_techniqueInRow(int rowIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData);
		void adopt_techniqueInCol(int colIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData);
};

//IntersectionChecker class

IntersectionChecker::IntersectionChecker() : IntersectionChecker(0,0) {}

IntersectionChecker::IntersectionChecker(int rowSize, int colSize) : HeuristicCheckerInterface(rowSize, colSize)
{
	checkerInfo = CheckerInfo(false, false, true, true, true, false, "IntersectionChecker");
}

void IntersectionChecker::adopt_techniqueInRow(int rowIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
	int numOfBlock = board.get_numOfRowHint(rowIndex);
	
	if(numOfBlock == 0) //if there is no block, set blank and end function
	{
		for(int i = 0; i < colSize; i++)
		{
			confirm_set_inRowTechnique(rowIndex, i, confirmedDotData);
		}
	}
	
	for(int i = 0; i < colSize; i++) //for (rowIndex, i)
	{
		for(int j = 0; j < numOfBlock; j++)
		{
			int blockSize = board.get_rowHint(rowIndex, j);
			pair<int,int> blockRange = blockRangeData.get_rowBlockRange(rowIndex, j);
			int blockRangeStartIndex = blockRange.first, blockRangeEndIndex = blockRange.second;
			
			//check is (rowIndex, i) in transection of all possible block
			if(i > blockRangeEndIndex)
			{
				continue;
			}
			else if(i < blockRangeStartIndex)
			{
				break;
			}
			else if(i >= blockRangeEndIndex - blockSize + 1 && i <= blockRangeStartIndex + blockSize - 1)
			{
				confirm_set_inRowTechnique(rowIndex, i, confirmedDotData);
				break;
			}
		}
	}
	
	//set blank confirmed spot
	for(int i = 0; i < blockRangeData.get_rowBlockRange(rowIndex, 0).first; i++) //set all dot before start range of first block blank
	{
		confirm_blank_inRowTechnique(rowIndex, i, confirmedDotData);
	}
	
	for(int i = blockRangeData.get_rowBlockRange(rowIndex, numOfBlock - 1).second + 1; i < colSize; i++) //set all dot after end range of last block blank
	{
		confirm_blank_inRowTechnique(rowIndex, i, confirmedDotData);
	}
	
	for(int i = 0; i < numOfBlock - 1; i++) //set all dot between range of block blank
	{
		for(int j = blockRangeData.get_rowBlockRange(rowIndex, i).second + 1; j < blockRangeData.get_rowBlockRange(rowIndex, i + 1).first; j++)
		{
			confirm_blank_inRowTechnique(rowIndex, j, confirmedDotData);
		}
	}
}

void IntersectionChecker::adopt_techniqueInCol(int colIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
	int numOfBlock = board.get_numOfColHint(colIndex);
	
	if(numOfBlock == 0) //if there is no block, set blank and end function
	{
		for(int i = 0; i < rowSize; i++)
		{
			confirm_blank_inColTechnique(i, colIndex, confirmedDotData);
		}
	}
	
	for(int i = 0; i < colSize; i++) //for (i, colIndex)
	{
		for(int j = 0; j < numOfBlock; j++)
		{
			int blockSize = board.get_colHint(colIndex, j);
			pair<int,int> blockRange = blockRangeData.get_colBlockRange(colIndex, j);
			int blockRangeStartIndex = blockRange.first, blockRangeEndIndex = blockRange.second;
			
			//check is (i, colIndex) in transection of all possible block
			if(i > blockRangeEndIndex)
			{
				continue;
			}
			else if(i < blockRangeStartIndex)
			{
				break;
			}
			else if(i >= blockRangeEndIndex - blockSize + 1 && i <= blockRangeStartIndex + blockSize - 1)
			{
				confirm_set_inColTechnique(i, colIndex, confirmedDotData);
				break;
			}
		}
	}
	
	//set blank confirmed spot
	for(int i = 0; i < blockRangeData.get_colBlockRange(colIndex, 0).first; i++) //set all dot before start range of first block blank
	{
		confirm_blank_inColTechnique(i, colIndex, confirmedDotData);
	}
	
	for(int i = blockRangeData.get_colBlockRange(colIndex, numOfBlock - 1).second + 1; i < rowSize; i++) //set all dot after end range of last block blank
	{
		confirm_blank_inColTechnique(i, colIndex, confirmedDotData);
	}
	
	for(int i = 0; i < numOfBlock - 1; i++) //set all dot between range of block blank
	{
		for(int j = blockRangeData.get_colBlockRange(colIndex, i).second + 1; j < blockRangeData.get_colBlockRange(colIndex, i + 1).first; j++)
		{
			confirm_blank_inColTechnique(j, colIndex, confirmedDotData);
		}
	}
}

