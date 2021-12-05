#include "BlockRangeReductionChecker.h"

BlockRangeReductionChecker::BlockRangeReductionChecker() : BlockRangeReductionChecker(0,0) {}

BlockRangeReductionChecker::BlockRangeReductionChecker(int rowSize, int colSize) : HeuristicCheckerInterface(rowSize, colSize)
{
    checkerInfo = CheckerInfo(true, true, true, false, false, true, "BlockRangeReductionChecker");
}

void BlockRangeReductionChecker::adopt_techniqueInRow(int rowIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
    int numOfBlock = board.get_numOfRowHint(rowIndex);
    
    for(int i = 0; i < numOfBlock; i++)
    {
        pair<int,int> currentBlockRange = blockRangeData.get_rowBlockRange(rowIndex, i);
        int isSetConfirmedDotFound = false;
        bool isBlockRangeChanged = false;
        
        if(i == 0 || blockRangeData.get_rowBlockRange(rowIndex, i - 1).second < currentBlockRange.first)
        {
            for(int j = currentBlockRange.first; j <= currentBlockRange.second; j++)
            {
                if(confirmedDotData.get_isSetConfirmed(rowIndex, j))
                {
                    isSetConfirmedDotFound = true;
                }
                else if(confirmedDotData.get_isBlankConfirmed(rowIndex, j) && isSetConfirmedDotFound && currentBlockRange.second > j - 1)
                {
                    currentBlockRange.second = j - 1;
                    isBlockRangeChanged = true;
                    break;
                }
            }
        }
        
        isSetConfirmedDotFound = false;
        
        if(i == numOfBlock - 1 || blockRangeData.get_rowBlockRange(rowIndex, i + 1).first > currentBlockRange.second)
        {
            for(int j = currentBlockRange.second; j >= currentBlockRange.first; j -= 1)
            {
                if(confirmedDotData.get_isSetConfirmed(rowIndex, j))
                {
                    isSetConfirmedDotFound = true;
                }
                else if(confirmedDotData.get_isBlankConfirmed(rowIndex, j) && isSetConfirmedDotFound && currentBlockRange.first < j + 1)
                {
                    currentBlockRange.first = j + 1;
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

void BlockRangeReductionChecker::adopt_techniqueInCol(int colIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
    int numOfBlock = board.get_numOfColHint(colIndex);
    
    for(int i = 0; i < numOfBlock; i++)
    {
        pair<int,int> currentBlockRange = blockRangeData.get_colBlockRange(colIndex, i);
        int isSetConfirmedDotFound = false;
        bool isBlockRangeChanged = false;
        
        if(i == 0 || blockRangeData.get_colBlockRange(colIndex, i - 1).second < currentBlockRange.first)
        {
            for(int j = currentBlockRange.first; j <= currentBlockRange.second; j++)
            {
                if(confirmedDotData.get_isSetConfirmed(j, colIndex))
                {
                    isSetConfirmedDotFound = true;
                }
                else if(confirmedDotData.get_isBlankConfirmed(j, colIndex) && isSetConfirmedDotFound && currentBlockRange.second > j - 1)
                {
                    currentBlockRange.second = j - 1;
                    isBlockRangeChanged = true;
                    break;
                }
            }
        }
        
        isSetConfirmedDotFound = false;
        
        if(i == numOfBlock - 1 || blockRangeData.get_colBlockRange(colIndex, i + 1).first > currentBlockRange.second)
        {
            for(int j = currentBlockRange.second; j >= currentBlockRange.first; j -= 1)
            {
                if(confirmedDotData.get_isSetConfirmed(j, colIndex))
                {
                    isSetConfirmedDotFound = true;
                }
                else if(confirmedDotData.get_isBlankConfirmed(j, colIndex) && isSetConfirmedDotFound && currentBlockRange.first < j + 1)
                {
                    currentBlockRange.first = j + 1;
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
