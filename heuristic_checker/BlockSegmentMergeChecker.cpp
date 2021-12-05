#include "BlockSegmentMergeChecker.h"

BlockSegmentMergeChecker::BlockSegmentMergeChecker() : BlockSegmentMergeChecker(0,0) {}

BlockSegmentMergeChecker::BlockSegmentMergeChecker(int rowSize, int colSize) : HeuristicCheckerInterface(rowSize, colSize)
{
    checkerInfo = CheckerInfo(true, false, true, false, false, true, "BlockSegmentMergeChecker");
}

void BlockSegmentMergeChecker::adopt_techniqueInRow(int rowIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
    int numOfBlock = board.get_numOfRowHint(rowIndex);
    
    for(int i = 0; i < numOfBlock; i++)
    {
        pair<int,int> currentBlockRange = blockRangeData.get_rowBlockRange(rowIndex, i);
        int currentBlockSize = board.get_rowHint(rowIndex, i);
        bool isBlockRangeChanged = false;
        vector<pair<int,int>> blockSegmentArray;
        pair<int,int> blockSegment = find_rowBlockSegment(rowIndex, currentBlockRange.first, currentBlockRange.second, confirmedDotData);
            
        while(blockSegment.first != -1)
        {
            blockSegmentArray.push_back(blockSegment);
            blockSegment = find_rowBlockSegment(rowIndex, blockSegment.second + 1, currentBlockRange.second, confirmedDotData);
        }
        
        int lastBlockSegmentIndex = blockSegmentArray.size() - 1;
        
        if(i == 0 || blockRangeData.get_rowBlockRange(rowIndex, i - 1).second < currentBlockRange.first)
        {
            for(int j = 1; j < blockSegmentArray.size(); j++)
            {
                if(blockSegmentArray[j].second - blockSegmentArray[0].first + 1 > currentBlockSize && currentBlockRange.second > blockSegmentArray[j].first - 2)
                {
                    lastBlockSegmentIndex = j - 1;
                    currentBlockRange.second = blockSegmentArray[j].first - 2;
                    isBlockRangeChanged = true;
                    break;
                }
            }
        }
        
        if(i == numOfBlock - 1 || blockRangeData.get_rowBlockRange(rowIndex, i + 1).first > currentBlockRange.second)
        {
            for(int j = lastBlockSegmentIndex - 1; j >= 0; j -= 1)
            {
                if(blockSegmentArray[lastBlockSegmentIndex].second - blockSegmentArray[j].first + 1 > currentBlockSize && currentBlockRange.first < blockSegmentArray[j].second + 2)
                {
                    currentBlockRange.first = blockSegmentArray[j].second + 2;
                    isBlockRangeChanged = true;
                    break;
                }
            }
        }
        
        if(isBlockRangeChanged)
        {
            change_rowBlockRange(rowIndex, i, currentBlockRange, blockRangeData);
        }
    }
}

void BlockSegmentMergeChecker::adopt_techniqueInCol(int colIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
    int numOfBlock = board.get_numOfColHint(colIndex);
    
    for(int i = 0; i < numOfBlock; i++)
    {
        pair<int,int> currentBlockRange = blockRangeData.get_colBlockRange(colIndex, i);
        int currentBlockSize = board.get_colHint(colIndex, i);
        bool isBlockRangeChanged = false;
        vector<pair<int,int>> blockSegmentArray;
        pair<int,int> blockSegment = find_colBlockSegment(colIndex, currentBlockRange.first, currentBlockRange.second, confirmedDotData);
            
        while(blockSegment.first != -1)
        {
            blockSegmentArray.push_back(blockSegment);
            blockSegment = find_colBlockSegment(colIndex, blockSegment.second + 1, currentBlockRange.second, confirmedDotData);
        }
        
        int lastBlockSegmentIndex = blockSegmentArray.size() - 1;
        
        if(i == 0 || blockRangeData.get_colBlockRange(colIndex, i - 1).second < currentBlockRange.first)
        {
            for(int j = 1; j < blockSegmentArray.size(); j++)
            {
                if(blockSegmentArray[j].second - blockSegmentArray[0].first + 1 > currentBlockSize && currentBlockRange.second > blockSegmentArray[j].first - 2)
                {
                    lastBlockSegmentIndex = j - 1;
                    currentBlockRange.second = blockSegmentArray[j].first - 2;
                    isBlockRangeChanged = true;
                    break;
                }
            }
        }
        
        if(i == numOfBlock - 1 || blockRangeData.get_colBlockRange(colIndex, i + 1).first > currentBlockRange.second)
        {
            for(int j = lastBlockSegmentIndex - 1; j >= 0; j -= 1)
            {
                if(blockSegmentArray[lastBlockSegmentIndex].second - blockSegmentArray[j].first + 1 > currentBlockSize && currentBlockRange.first < blockSegmentArray[j].second + 2)
                {
                    currentBlockRange.first = blockSegmentArray[j].second + 2;
                    isBlockRangeChanged = true;
                    break;
                }
            }
        }
        
        if(isBlockRangeChanged)
        {
            change_colBlockRange(colIndex, i, currentBlockRange, blockRangeData);
        }
    }
}

pair<int,int> BlockSegmentMergeChecker::find_rowBlockSegment(int rowIndex, int startColIndex, int endColIndex, ConfirmedDotData& confirmedDotData)
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

pair<int,int> BlockSegmentMergeChecker::find_colBlockSegment(int colIndex, int startRowIndex, int endRowIndex, ConfirmedDotData& confirmedDotData)
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
