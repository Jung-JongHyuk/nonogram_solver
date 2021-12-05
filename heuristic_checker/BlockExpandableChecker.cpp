#include "BlockExpandableChecker.h"

BlockExpandableChecker::BlockExpandableChecker() : BlockExpandableChecker(0,0) {}

BlockExpandableChecker::BlockExpandableChecker(int rowSize, int colSize) : HeuristicCheckerInterface(rowSize, colSize)
{
    checkerInfo = CheckerInfo(true, true, true, true, false, false, "BlockExpandableChecker");
}

void BlockExpandableChecker::adopt_techniqueInRow(int rowIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
    for(int i = 1; i < colSize; i++)
    {
        if(confirmedDotData.get_isSetConfirmed(rowIndex, i) && !confirmedDotData.get_isSetConfirmed(rowIndex, i - 1))
        {
            int minPossibleBlockSize = get_minPossibleRowBlockSize(rowIndex, i, board, blockRangeData);
            int leftWallIndex = get_leftWallIndex(rowIndex, i, i - minPossibleBlockSize + 1, i - 1, confirmedDotData);
            
            if(leftWallIndex != -2)
            {
                for(int j = i + 1; j <= leftWallIndex + minPossibleBlockSize; j++)
                {
                    confirm_set_inRowTechnique(rowIndex, j, confirmedDotData);
                }
            }
        }
    }
    
    for(int i = 0; i < colSize - 1; i++)
    {
        if(confirmedDotData.get_isSetConfirmed(rowIndex, i) && !confirmedDotData.get_isSetConfirmed(rowIndex, i + 1))
        {
            int minPossibleBlockSize = get_minPossibleRowBlockSize(rowIndex, i, board, blockRangeData);
            int rightWallIndex = get_rightWallIndex(rowIndex, i, i + 1, i + minPossibleBlockSize - 1, confirmedDotData);
            
            if(rightWallIndex != -2)
            {
                for(int j = rightWallIndex - minPossibleBlockSize; j <= i - 1; j++)
                {
                    confirm_set_inRowTechnique(rowIndex, j, confirmedDotData);
                }
            }
        }
    }
}

void BlockExpandableChecker::adopt_techniqueInCol(int colIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
    for(int i = 1; i < rowSize; i++)
    {
        if(confirmedDotData.get_isSetConfirmed(i, colIndex) && !confirmedDotData.get_isSetConfirmed(i - 1, colIndex))
        {
            int minPossibleBlockSize = get_minPossibleColBlockSize(i, colIndex, board, blockRangeData);
            int upperWallIndex = get_upperWallIndex(i, colIndex, i - minPossibleBlockSize + 1, i - 1, confirmedDotData);
            
            if(upperWallIndex != -2)
            {
                for(int j = i + 1; j <= upperWallIndex + minPossibleBlockSize; j++)
                {
                    confirm_set_inColTechnique(j, colIndex, confirmedDotData);
                }
            }
        }
    }
    
    for(int i = 0; i < rowSize - 1; i++)
    {
        if(confirmedDotData.get_isSetConfirmed(i, colIndex) && !confirmedDotData.get_isSetConfirmed(i + 1, colIndex))
        {
            int minPossibleBlockSize = get_minPossibleColBlockSize(i, colIndex, board, blockRangeData);
            int lowerWallIndex = get_lowerWallIndex(i, colIndex, i + 1, i + minPossibleBlockSize - 1, confirmedDotData);
            
            if(lowerWallIndex != -2)
            {
                for(int j = lowerWallIndex - minPossibleBlockSize; j <= i - 1; j++)
                {
                    confirm_set_inColTechnique(j, colIndex, confirmedDotData);
                }
            }
        }
    }
}

int BlockExpandableChecker::get_leftWallIndex(int rowIndex, int colIndex, int colRangeStart, int colRangeEnd, ConfirmedDotData& confirmedDotData)
{
    int startIndex = (colRangeStart >= 0) ? colRangeStart : 0;
    int endIndex = (colRangeEnd < colSize - 1) ? colRangeEnd : colSize - 1;
    
    for(int i = endIndex; i >= startIndex; i -= 1)
    {
        if(confirmedDotData.get_isBlankConfirmed(rowIndex, i))
        {
            return i;
        }
    }
    
    return (startIndex == 0) ? -1 : -2;
}

int BlockExpandableChecker::get_rightWallIndex(int rowIndex, int colIndex, int colRangeStart, int colRangeEnd, ConfirmedDotData& confirmedDotData)
{
    int startIndex = (colRangeStart >= 0) ? colRangeStart : 0;
    int endIndex = (colRangeEnd < colSize - 1) ? colRangeEnd : colSize - 1;
    
    for(int i = startIndex; i <= endIndex; i++)
    {
        if(confirmedDotData.get_isBlankConfirmed(rowIndex, i))
        {
            return i;
        }
    }
    
    return (endIndex == colSize - 1) ? colSize : -2;
}

int BlockExpandableChecker::get_upperWallIndex(int rowIndex, int colIndex, int rowRangeStart, int rowRangeEnd, ConfirmedDotData& confirmedDotData)
{
    int startIndex = (rowRangeStart >= 0) ? rowRangeStart : 0;
    int endIndex = (rowRangeEnd < rowSize - 1) ? rowRangeEnd : rowSize - 1;
    
    for(int i = endIndex; i >= startIndex; i -= 1)
    {
        if(confirmedDotData.get_isBlankConfirmed(i, colIndex))
        {
            return i;
        }
    }
    
    return (startIndex == 0) ? -1 : -2;
}

int BlockExpandableChecker::get_lowerWallIndex(int rowIndex, int colIndex, int rowRangeStart, int rowRangeEnd, ConfirmedDotData& confirmedDotData)
{
    int startIndex = (rowRangeStart >= 0) ? rowRangeStart : 0;
    int endIndex = (rowRangeEnd < rowSize - 1) ? rowRangeEnd : rowSize - 1;
    
    for(int i = startIndex; i <= endIndex; i++)
    {
        if(confirmedDotData.get_isBlankConfirmed(i, colIndex))
        {
            return i;
        }
    }
    
    return (endIndex == rowSize - 1) ? rowSize : -2;
}

int BlockExpandableChecker::get_minPossibleRowBlockSize(int rowIndex, int colIndex, Board& board, BlockRangeData& blockRangeData)
{
    int numOfBlock = board.get_numOfRowHint(rowIndex);
    int minBlockSize = 0;
    bool isMinBlockSizeSet = false; //check is current minBlockSize null value
    
    for(int i = 0; i < numOfBlock; i++)
    {
        pair<int,int> currentBlockRange = blockRangeData.get_rowBlockRange(rowIndex, i);
        
        if(colIndex > currentBlockRange.second)
        {
            continue;
        }
        else if(colIndex < currentBlockRange.first)
        {
            break;
        }
        else if(colIndex >= currentBlockRange.first && colIndex <= currentBlockRange.second)
        {
            int currentBlockSize = board.get_rowHint(rowIndex, i);
            
            if(!isMinBlockSizeSet)
            {
                minBlockSize = currentBlockSize;
                isMinBlockSizeSet = true;
            }
            else
            {
                minBlockSize = (currentBlockSize < minBlockSize) ? currentBlockSize : minBlockSize;
            }
        }
    }
    
    return minBlockSize;
}

int BlockExpandableChecker::get_minPossibleColBlockSize(int rowIndex, int colIndex, Board& board, BlockRangeData& blockRangeData)
{
    int numOfBlock = board.get_numOfColHint(colIndex);
    int minBlockSize = 0;
    bool isMinBlockSizeSet = false; //check is current minBlockSize null value
    
    for(int i = 0; i < numOfBlock; i++)
    {
        pair<int,int> currentBlockRange = blockRangeData.get_colBlockRange(colIndex, i);
        
        if(rowIndex > currentBlockRange.second)
        {
            continue;
        }
        else if(rowIndex < currentBlockRange.first)
        {
            break;
        }
        else if(rowIndex >= currentBlockRange.first && rowIndex <= currentBlockRange.second)
        {
            int currentBlockSize = board.get_colHint(colIndex, i);
            
            if(!isMinBlockSizeSet)
            {
                minBlockSize = currentBlockSize;
                isMinBlockSizeSet = true;
            }
            else
            {
                minBlockSize = (currentBlockSize < minBlockSize) ? currentBlockSize : minBlockSize;
            }
        }
    }
    
    return minBlockSize;
}
