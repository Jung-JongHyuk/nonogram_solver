#pragma once

#include "HeuristicCheckerInterface.hpp"
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

//PotentialBlockSegmentChecker class

PotentialBlockSegmentChecker::PotentialBlockSegmentChecker() : PotentialBlockSegmentChecker(0,0) {}

PotentialBlockSegmentChecker::PotentialBlockSegmentChecker(int rowSize, int colSize) : HeuristicCheckerInterface(rowSize, colSize)
{
	checkerInfo = CheckerInfo(false, true, true, false, true, true, "PotentialBlockSegmentChecker");
}

void PotentialBlockSegmentChecker::adopt_techniqueInRow(int rowIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
	int numOfBlock = board.get_numOfRowHint(rowIndex);
	
	for(int i = 0; i < numOfBlock; i++)
	{
		pair<int,int> currentBlockRange = blockRangeData.get_rowBlockRange(rowIndex, i);
		pair<int,int> potentialBlockSegmentRange = find_rowPotentialBlockSegment(rowIndex, currentBlockRange.first, currentBlockRange.second, confirmedDotData);
		int currentBlockSize = board.get_rowHint(rowIndex, i);
		int firstValidPotentialBlockSegmentIndex = -1, lastValidPotentialBlockSegmentIndex = -1;
		vector<pair<int,int>> potentialBlockSegmentArray;
		
		while(potentialBlockSegmentRange.first != -1)
		{	
			if(potentialBlockSegmentRange.second - potentialBlockSegmentRange.first + 1 >= currentBlockSize)
			{
				firstValidPotentialBlockSegmentIndex = (firstValidPotentialBlockSegmentIndex == -1) ? 0 : firstValidPotentialBlockSegmentIndex;
				
				if(firstValidPotentialBlockSegmentIndex != -1)
				{
					potentialBlockSegmentArray.push_back(potentialBlockSegmentRange);
				}
			}
			
			potentialBlockSegmentRange = find_rowPotentialBlockSegment(rowIndex, potentialBlockSegmentRange.second + 1, currentBlockRange.second, confirmedDotData);
		}
		
		lastValidPotentialBlockSegmentIndex = potentialBlockSegmentArray.size() - 1;
		bool isBlockRangeChanged = false;
		
		if(potentialBlockSegmentArray.size() == 0)
		{
			return;
		}
		
		int changedBlockRangeStart = potentialBlockSegmentArray[firstValidPotentialBlockSegmentIndex].first;
		int changedBlockRangeEnd = potentialBlockSegmentArray[lastValidPotentialBlockSegmentIndex].second;
		
		if(currentBlockRange.first < changedBlockRangeStart)
		{
			currentBlockRange.first = changedBlockRangeStart;
			isBlockRangeChanged = true;
		}
		
		if(currentBlockRange.second > changedBlockRangeEnd)
		{
			currentBlockRange.second = changedBlockRangeEnd;
			isBlockRangeChanged = true;
		}
		
		if(isBlockRangeChanged)
		{
			change_rowBlockRange(rowIndex, i, currentBlockRange, blockRangeData);
		}
		
		for(int j = firstValidPotentialBlockSegmentIndex + 1; j < lastValidPotentialBlockSegmentIndex; j++)
		{
			if(potentialBlockSegmentArray[j].second - potentialBlockSegmentArray[j].first + 1 < currentBlockSize)
			{
				for(int k = potentialBlockSegmentArray[j].first; k <= potentialBlockSegmentArray[j].second; k++)
				{
					if(check_isInSingleBlockRangeInRow(rowIndex, k, i, board, blockRangeData))
					{
						confirm_blank_inRowTechnique(rowIndex, k, confirmedDotData);
					}
				}
			}
		}
	}
}

void PotentialBlockSegmentChecker::adopt_techniqueInCol(int colIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
	int numOfBlock = board.get_numOfColHint(colIndex);
	
	for(int i = 0; i < numOfBlock; i++)
	{
		pair<int,int> currentBlockRange = blockRangeData.get_colBlockRange(colIndex, i);
		pair<int,int> potentialBlockSegmentRange = find_colPotentialBlockSegment(colIndex, currentBlockRange.first, currentBlockRange.second, confirmedDotData);
		int currentBlockSize = board.get_colHint(colIndex, i);
		int firstValidPotentialBlockSegmentIndex = -1, lastValidPotentialBlockSegmentIndex = -1;
		vector<pair<int,int>> potentialBlockSegmentArray;
		
		while(potentialBlockSegmentRange.first != -1)
		{
			if(potentialBlockSegmentRange.second - potentialBlockSegmentRange.first + 1 >= currentBlockSize)
			{
				firstValidPotentialBlockSegmentIndex = (firstValidPotentialBlockSegmentIndex == -1) ? 0 : firstValidPotentialBlockSegmentIndex;
				
				if(firstValidPotentialBlockSegmentIndex != -1)
				{
					potentialBlockSegmentArray.push_back(potentialBlockSegmentRange);
				}
			}
			
			potentialBlockSegmentRange = find_colPotentialBlockSegment(colIndex, potentialBlockSegmentRange.second + 1, currentBlockRange.second, confirmedDotData);
		}
		
		lastValidPotentialBlockSegmentIndex = potentialBlockSegmentArray.size() - 1;
		bool isBlockRangeChanged = false;
		
		if(potentialBlockSegmentArray.size() == 0)
		{
			return;
		}
		
		int changedBlockRangeStart = potentialBlockSegmentArray[firstValidPotentialBlockSegmentIndex].first;
		int changedBlockRangeEnd = potentialBlockSegmentArray[lastValidPotentialBlockSegmentIndex].second;
		
		if(currentBlockRange.first < changedBlockRangeStart)
		{
			currentBlockRange.first = changedBlockRangeStart;
			isBlockRangeChanged = true;
		}
		
		if(currentBlockRange.second > changedBlockRangeEnd)
		{
			currentBlockRange.second = changedBlockRangeEnd;
			isBlockRangeChanged = true;
		}
		
		if(isBlockRangeChanged)
		{
			change_colBlockRange(colIndex, i, currentBlockRange, blockRangeData);
		}
		
		for(int j = firstValidPotentialBlockSegmentIndex + 1; j < lastValidPotentialBlockSegmentIndex; j++)
		{
			if(potentialBlockSegmentArray[j].second - potentialBlockSegmentArray[j].first + 1 < currentBlockSize)
			{
				for(int k = potentialBlockSegmentArray[j].first; k <= potentialBlockSegmentArray[j].second; k++)
				{
					if(check_isInSingleBlockRangeInCol(k, colIndex, i, board, blockRangeData))
					{
						confirm_blank_inColTechnique(k, colIndex, confirmedDotData);
					}
				}
			}
		}
	}
}

pair<int,int> PotentialBlockSegmentChecker::find_rowPotentialBlockSegment(int rowIndex, int startColIndex, int endColIndex, ConfirmedDotData& confirmedDotData)
{
	pair<int,int> segmentIndexRange;
	bool isSegmentFound = false;
	
	for(int i = startColIndex; i <= endColIndex; i++)
	{
		if(!confirmedDotData.get_isBlankConfirmed(rowIndex, i) && !isSegmentFound)
		{
			segmentIndexRange.first = i;
			isSegmentFound = true;
		}
		else if(confirmedDotData.get_isBlankConfirmed(rowIndex, i) && isSegmentFound)
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

pair<int,int> PotentialBlockSegmentChecker::find_colPotentialBlockSegment(int colIndex, int startRowIndex, int endRowIndex, ConfirmedDotData& confirmedDotData)
{	
	pair<int,int> segmentIndexRange;
	bool isSegmentFound = false;
	
	for(int i = startRowIndex; i <= endRowIndex; i++)
	{
		if(!confirmedDotData.get_isBlankConfirmed(i, colIndex) && !isSegmentFound)
		{
			segmentIndexRange.first = i;
			isSegmentFound = true;
		}
		else if(confirmedDotData.get_isBlankConfirmed(i, colIndex) && isSegmentFound)
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

bool PotentialBlockSegmentChecker::check_isInSingleBlockRangeInRow(int rowIndex, int colIndex, int blockIndex, Board& board, BlockRangeData& blockRangeData)
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

bool PotentialBlockSegmentChecker::check_isInSingleBlockRangeInCol(int rowIndex, int colIndex, int blockIndex, Board& board, BlockRangeData& blockRangeData)
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

