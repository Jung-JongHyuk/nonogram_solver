#include "BlockRangeIntervalChecker.h"

BlockRangeIntervalChecker::BlockRangeIntervalChecker() : BlockRangeIntervalChecker(0,0) {}

BlockRangeIntervalChecker::BlockRangeIntervalChecker(int rowSize, int colSize) : HeuristicCheckerInterface(rowSize, colSize)
{
    checkerInfo = CheckerInfo(true, true, true, false, false, true, "BlockRangeIntervalChecker");
}

void BlockRangeIntervalChecker::adopt_techniqueInRow(int rowIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
    int numOfBlock = board.get_numOfRowHint(rowIndex);
    
    for(int i = 0; i < numOfBlock; i++)
    {
        pair<int,int> currentBlockRange = blockRangeData.get_rowBlockRange(rowIndex, i);
        bool isBlockRangeChanged = false;
        
        while(currentBlockRange.first > 0 && confirmedDotData.get_isSetConfirmed(rowIndex, currentBlockRange.first - 1))
        {
            currentBlockRange.first++;
            isBlockRangeChanged = true;
        }
        
        while(confirmedDotData.get_isBlankConfirmed(rowIndex, currentBlockRange.first))
        {
            currentBlockRange.first++;
            isBlockRangeChanged = true;
        }
        
        while(currentBlockRange.second < colSize - 1 && confirmedDotData.get_isSetConfirmed(rowIndex, currentBlockRange.second + 1))
        {
            currentBlockRange.second -= 1;
            isBlockRangeChanged = true;
        }
        
        while(confirmedDotData.get_isBlankConfirmed(rowIndex, currentBlockRange.second))
        {
            currentBlockRange.second -= 1;
            isBlockRangeChanged = true;
        }
        
        if(isBlockRangeChanged)
        {
            change_rowBlockRange(rowIndex, i, currentBlockRange, blockRangeData);
        }
    }
}

void BlockRangeIntervalChecker::adopt_techniqueInCol(int colIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
    int numOfBlock = board.get_numOfColHint(colIndex);
    
    for(int i = 0; i < numOfBlock; i++)
    {
        pair<int,int> currentBlockRange = blockRangeData.get_colBlockRange(colIndex, i);
        bool isBlockRangeChanged = false;
        
        while(currentBlockRange.first > 0 && confirmedDotData.get_isSetConfirmed(currentBlockRange.first - 1, colIndex))
        {
            currentBlockRange.first++;
            isBlockRangeChanged = true;
        }
        
        while(confirmedDotData.get_isBlankConfirmed(currentBlockRange.first, colIndex))
        {
            currentBlockRange.first++;
            isBlockRangeChanged = true;
        }
        
        while(currentBlockRange.second < rowSize - 1 && confirmedDotData.get_isSetConfirmed(currentBlockRange.second + 1, colIndex))
        {
            currentBlockRange.second -= 1;
            isBlockRangeChanged = true;
        }
        
        while(confirmedDotData.get_isBlankConfirmed(currentBlockRange.second, colIndex))
        {
            currentBlockRange.second -= 1;
            isBlockRangeChanged = true;
        }
        
        if(isBlockRangeChanged)
        {
            change_colBlockRange(colIndex, i, currentBlockRange, blockRangeData);
        }
    }
}

