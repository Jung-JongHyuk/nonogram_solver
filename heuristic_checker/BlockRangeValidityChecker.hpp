#pragma once

#include "HeuristicCheckerInterface.hpp"
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

//BlockRangeValidityChecker class

BlockRangeValidityChecker::BlockRangeValidityChecker() : BlockRangeValidityChecker(0,0) {}

BlockRangeValidityChecker::BlockRangeValidityChecker(int rowSize, int colSize) : HeuristicCheckerInterface(rowSize, colSize)
{
	checkerInfo = CheckerInfo(true, false, true, false, false, true, "BlockRangeValidityChecker");
}

void BlockRangeValidityChecker::adopt_techniqueInRow(int rowIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
	int numOfBlock = board.get_numOfRowHint(rowIndex);
	
	for(int i = 0; i < numOfBlock; i++)
	{
		pair<int,int> currentBlockRange = blockRangeData.get_rowBlockRange(rowIndex, i);
		int segmentSearchStartIndex = currentBlockRange.first;
		int currentBlockSize = board.get_rowHint(rowIndex, i);
		pair<int,int> blockSegmentRange = find_rowBlockSegment(rowIndex, segmentSearchStartIndex, currentBlockRange.second, confirmedDotData);
		bool isBlockRangeChanged = false;
			
		while(blockSegmentRange.first != -1)
		{
			if(blockSegmentRange.second - blockSegmentRange.first + 1 > currentBlockSize)
			{	
				if(!is_rowBlockSegmentIncludedInRightBlockRange(rowIndex, i, numOfBlock, blockSegmentRange, blockRangeData) && currentBlockRange.first < blockSegmentRange.second + 2)
				{
					currentBlockRange.first = blockSegmentRange.second + 2;
					isBlockRangeChanged = true;
				}
				
				if(!is_rowBlockSegmentIncludedInLeftBlockRange(rowIndex, i, numOfBlock, blockSegmentRange, blockRangeData) && currentBlockRange.second > blockSegmentRange.first - 2)
				{
					currentBlockRange.second = blockSegmentRange.first - 2;
					isBlockRangeChanged = true;	
				}
			}
			
			blockSegmentRange = find_rowBlockSegment(rowIndex, blockSegmentRange.second + 1, currentBlockRange.second, confirmedDotData);
		}
		
		if(isBlockRangeChanged)
		{
			change_rowBlockRange(rowIndex, i, currentBlockRange, blockRangeData);
		}
	}
}

void BlockRangeValidityChecker::adopt_techniqueInCol(int colIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
	int numOfBlock = board.get_numOfColHint(colIndex);
	
	for(int i = 0; i < numOfBlock; i++)
	{
		pair<int,int> currentBlockRange = blockRangeData.get_colBlockRange(colIndex, i);
		int segmentSearchStartIndex = currentBlockRange.first;
		int currentBlockSize = board.get_colHint(colIndex, i);
		pair<int,int> blockSegmentRange = find_colBlockSegment(colIndex, segmentSearchStartIndex, currentBlockRange.second, confirmedDotData);
		bool isBlockRangeChanged = false;
		
		while(blockSegmentRange.first != -1)
		{
			if(blockSegmentRange.second - blockSegmentRange.first + 1 > currentBlockSize)
			{	
				if(!is_colBlockSegmentIncludedInLowerBlockRange(colIndex, i, numOfBlock, blockSegmentRange, blockRangeData) && currentBlockRange.first < blockSegmentRange.second + 2)
				{
					currentBlockRange.first = blockSegmentRange.second + 2;
					isBlockRangeChanged = true;
				}
				
				if(!is_colBlockSegmentIncludedInUpperBlockRange(colIndex, i, numOfBlock, blockSegmentRange, blockRangeData) && currentBlockRange.second > blockSegmentRange.first - 2)
				{
					currentBlockRange.second = blockSegmentRange.first - 2;
					isBlockRangeChanged = true;	
				}
			}
			
			blockSegmentRange = find_colBlockSegment(colIndex, blockSegmentRange.second + 1, currentBlockRange.second, confirmedDotData);
		}
		
		if(isBlockRangeChanged)
		{
			change_colBlockRange(colIndex, i, currentBlockRange, blockRangeData);
		}
	}
}

pair<int,int> BlockRangeValidityChecker::find_rowBlockSegment(int rowIndex, int startColIndex, int endColIndex, ConfirmedDotData& confirmedDotData)
{
	pair<int,int> segmentIndexRange;
	bool isSegmentFound = false;
	
	for(int i = startColIndex; i <= endColIndex; i++)
	{
		if(confirmedDotData.get_isSetConfirmed(rowIndex, i) && !isSegmentFound)
		{
			segmentIndexRange.first = i;
			isSegmentFound = true;
		}
		else if(!confirmedDotData.get_isSetConfirmed(rowIndex, i) && isSegmentFound)
		{
			segmentIndexRange.second = i - 1;
			return segmentIndexRange;
		}
	}
	
	if(!isSegmentFound)
	{
		return pair<int,int>(-1,-1);
	}
	else
	{
		segmentIndexRange.second = endColIndex;
		return segmentIndexRange;
	}
}

pair<int,int> BlockRangeValidityChecker::find_colBlockSegment(int colIndex, int startRowIndex, int endRowIndex, ConfirmedDotData& confirmedDotData)
{
	pair<int,int> segmentIndexRange;
	bool isSegmentFound = false;
	
	for(int i = startRowIndex; i <= endRowIndex; i++)
	{
		if(confirmedDotData.get_isSetConfirmed(i, colIndex) && !isSegmentFound)
		{
			segmentIndexRange.first = i;
			isSegmentFound = true;
		}
		else if(!confirmedDotData.get_isSetConfirmed(i, colIndex) && isSegmentFound)
		{
			segmentIndexRange.second = i - 1;
			return segmentIndexRange;
		}
	}
	
	if(!isSegmentFound)
	{
		return pair<int,int>(-1,-1);
	}
	else
	{
		segmentIndexRange.second = endRowIndex;
		return segmentIndexRange;
	}
}

bool BlockRangeValidityChecker::is_rowBlockSegmentIncludedInRightBlockRange(int rowIndex, int blockIndex, int numOfBlock, pair<int,int> blockSegmentRange, BlockRangeData& blockRangeData)
{
	for(int i = blockIndex + 1; i < numOfBlock; i++)
	{
		pair<int,int> currentBlockRange = blockRangeData.get_rowBlockRange(rowIndex, i);
		
		if(blockSegmentRange.first > currentBlockRange.second)
		{
			continue;
		}
		else if(blockSegmentRange.first < currentBlockRange.first)
		{
			return false;
		}
		else if(blockSegmentRange.first >= currentBlockRange.first && blockSegmentRange.second <= currentBlockRange.second)
		{
			return true;
		}
	}
	
	return false;
}

bool BlockRangeValidityChecker::is_rowBlockSegmentIncludedInLeftBlockRange(int rowIndex, int blockIndex, int numOfBlock, pair<int,int> blockSegmentRange, BlockRangeData& blockRangeData)
{
	for(int i = blockIndex - 1; i>= 0; i -= 1)
	{
		pair<int,int> currentBlockRange = blockRangeData.get_rowBlockRange(rowIndex, i);
		
		if(blockSegmentRange.second < currentBlockRange.first)
		{
			continue;
		}
		else if(blockSegmentRange.second > currentBlockRange.second)
		{
			return false;
		}
		else if(blockSegmentRange.first >= currentBlockRange.first && blockSegmentRange.second <= currentBlockRange.second)
		{
			return true;
		}
	}
	
	return false;
}

bool BlockRangeValidityChecker::is_colBlockSegmentIncludedInLowerBlockRange(int colIndex, int blockIndex, int numOfBlock, pair<int,int> blockSegmentRange, BlockRangeData& blockRangeData)
{
	for(int i = blockIndex + 1; i < numOfBlock; i++)
	{
		pair<int,int> currentBlockRange = blockRangeData.get_colBlockRange(colIndex, i);
		
		if(blockSegmentRange.first > currentBlockRange.second)
		{
			continue;
		}
		else if(blockSegmentRange.first < currentBlockRange.first)
		{
			return false;
		}
		else if(blockSegmentRange.first >= currentBlockRange.first && blockSegmentRange.second <= currentBlockRange.second)
		{
			return true;
		}
	}
	
	return false;
}

bool BlockRangeValidityChecker::is_colBlockSegmentIncludedInUpperBlockRange(int colIndex, int blockIndex, int numOfBlock, pair<int,int> blockSegmentRange, BlockRangeData& blockRangeData)
{
	for(int i = blockIndex - 1; i>= 0; i -= 1)
	{
		pair<int,int> currentBlockRange = blockRangeData.get_colBlockRange(colIndex, i);
		
		if(blockSegmentRange.second < currentBlockRange.first)
		{
			continue;
		}
		else if(blockSegmentRange.second > currentBlockRange.second)
		{
			return false;
		}
		else if(blockSegmentRange.first >= currentBlockRange.first && blockSegmentRange.second <= currentBlockRange.second)
		{
			return true;
		}
	}
	
	return false;
}

