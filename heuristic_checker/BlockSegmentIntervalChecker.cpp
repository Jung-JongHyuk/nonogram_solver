#include "BlockSegmentIntervalChecker.h"

BlockSegmentIntervalChecker::BlockSegmentIntervalChecker() : BlockSegmentIntervalChecker(0,0) {}

BlockSegmentIntervalChecker::BlockSegmentIntervalChecker(int rowSize, int colSize) : HeuristicCheckerInterface(rowSize, colSize)
{
    checkerInfo = CheckerInfo(true, false, true, true, false, true, "BlockSegmentIntervalChecker");
}

void BlockSegmentIntervalChecker::adopt_techniqueInRow(int rowIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
    int numOfBlock = board.get_numOfRowHint(rowIndex);
    
    for(int i = 0; i < numOfBlock; i++)
    {
        pair<int,int> currentBlockRange = blockRangeData.get_rowBlockRange(rowIndex, i);
        int firstSetConfirmedCurrentRangeOnlyIndex = currentBlockRange.second, lastSetConfirmedCurrentRangeOnlyIndex = currentBlockRange.first;
        pair<int,int> blockSegmentSearchRange;
        blockSegmentSearchRange.first = i != 0 ? blockRangeData.get_rowBlockRange(rowIndex, i - 1).second + 1 : currentBlockRange.first;
        blockSegmentSearchRange.second = i != numOfBlock - 1 ? blockRangeData.get_rowBlockRange(rowIndex, i + 1).first - 1 : currentBlockRange.second;
        
        for(int j = blockSegmentSearchRange.first; j <= blockSegmentSearchRange.second; j++)
        {
            if(confirmedDotData.get_isSetConfirmed(rowIndex, j))
            {
                firstSetConfirmedCurrentRangeOnlyIndex = j;
                break;
            }
        }
        
        for(int j = blockSegmentSearchRange.second; j >= blockSegmentSearchRange.first; j -= 1)
        {
            if(confirmedDotData.get_isSetConfirmed(rowIndex, j))
            {
                lastSetConfirmedCurrentRangeOnlyIndex = j;
                break;
            }
        }
        
        if(lastSetConfirmedCurrentRangeOnlyIndex - firstSetConfirmedCurrentRangeOnlyIndex > 1)
        {
            for(int j = firstSetConfirmedCurrentRangeOnlyIndex + 1; j <= lastSetConfirmedCurrentRangeOnlyIndex - 1; j++)
            {
                confirm_set_inRowTechnique(rowIndex, j, confirmedDotData);
            }
        }
        
        int mergedSegmentSize = lastSetConfirmedCurrentRangeOnlyIndex - firstSetConfirmedCurrentRangeOnlyIndex + 1;
        int currentBlockSize = board.get_rowHint(rowIndex, i);
        bool isBlockRangeChanged = false;
            
        if(currentBlockRange.first < firstSetConfirmedCurrentRangeOnlyIndex - currentBlockSize + mergedSegmentSize)
        {
            currentBlockRange.first = firstSetConfirmedCurrentRangeOnlyIndex - currentBlockSize + mergedSegmentSize;
            isBlockRangeChanged = true;
        }
            
        if(currentBlockRange.second > lastSetConfirmedCurrentRangeOnlyIndex + currentBlockSize - mergedSegmentSize)
        {
            currentBlockRange.second = lastSetConfirmedCurrentRangeOnlyIndex + currentBlockSize - mergedSegmentSize;
            isBlockRangeChanged = true;
        }
            
        if(isBlockRangeChanged)
        {
            change_rowBlockRange(rowIndex, i, currentBlockRange, blockRangeData);
        }
    }
}

void BlockSegmentIntervalChecker::adopt_techniqueInCol(int colIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
    int numOfBlock = board.get_numOfColHint(colIndex);
    
    for(int i = 0; i < numOfBlock; i++)
    {
        pair<int,int> currentBlockRange = blockRangeData.get_colBlockRange(colIndex, i);
        int firstSetConfirmedCurrentRangeOnlyIndex = currentBlockRange.second, lastSetConfirmedCurrentRangeOnlyIndex = currentBlockRange.first;
        pair<int,int> blockSegmentSearchRange;
        blockSegmentSearchRange.first = i != 0 ? blockRangeData.get_colBlockRange(colIndex, i - 1).second + 1 : currentBlockRange.first;
        blockSegmentSearchRange.second = i != numOfBlock - 1 ? blockRangeData.get_colBlockRange(colIndex, i + 1).first - 1 : currentBlockRange.second;
        
        for(int j = blockSegmentSearchRange.first; j <= blockSegmentSearchRange.second; j++)
        {
            if(confirmedDotData.get_isSetConfirmed(j, colIndex))
            {
                firstSetConfirmedCurrentRangeOnlyIndex = j;
                break;
            }
        }
        
        for(int j = blockSegmentSearchRange.second; j >= blockSegmentSearchRange.first; j -= 1)
        {
            if(confirmedDotData.get_isSetConfirmed(j, colIndex))
            {
                lastSetConfirmedCurrentRangeOnlyIndex = j;
                break;
            }
        }
        
        if(lastSetConfirmedCurrentRangeOnlyIndex - firstSetConfirmedCurrentRangeOnlyIndex > 1)
        {
            for(int j = firstSetConfirmedCurrentRangeOnlyIndex + 1; j <= lastSetConfirmedCurrentRangeOnlyIndex - 1; j++)
            {
                confirm_set_inColTechnique(j, colIndex, confirmedDotData);
            }
        }
        
        int mergedSegmentSize = lastSetConfirmedCurrentRangeOnlyIndex - firstSetConfirmedCurrentRangeOnlyIndex + 1;
        int currentBlockSize = board.get_colHint(colIndex, i);
        bool isBlockRangeChanged = false;
            
        if(currentBlockRange.first < firstSetConfirmedCurrentRangeOnlyIndex - currentBlockSize + mergedSegmentSize)
        {
            currentBlockRange.first = firstSetConfirmedCurrentRangeOnlyIndex - currentBlockSize + mergedSegmentSize;
            isBlockRangeChanged = true;
        }
            
        if(currentBlockRange.second > lastSetConfirmedCurrentRangeOnlyIndex + currentBlockSize - mergedSegmentSize)
        {
            currentBlockRange.second = lastSetConfirmedCurrentRangeOnlyIndex + currentBlockSize - mergedSegmentSize;
            isBlockRangeChanged = true;
        }
            
        if(isBlockRangeChanged)
        {
            change_colBlockRange(colIndex, i, currentBlockRange, blockRangeData);
        }
    }
}
