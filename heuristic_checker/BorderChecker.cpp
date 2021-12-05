#include "BorderChecker.h"

BorderChecker::BorderChecker() : BorderChecker(0,0) {}

BorderChecker::BorderChecker(int rowSize, int colSize) : HeuristicCheckerInterface(rowSize, colSize)
{
    checkerInfo = CheckerInfo(true, false, false, true, true, false, "BorderChecker");
    isUpperBorderCheckNeeded.resize(colSize, true);
    isLowerBorderCheckNeeded.resize(colSize, true);
    isLeftBorderCheckNeeded.resize(rowSize, true);
    isRightBorderCheckNeeded.resize(rowSize, true);
}

void BorderChecker::adopt_techniqueInRow(int rowIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
    if(isLeftBorderCheckNeeded[rowIndex] && confirmedDotData.get_isSetConfirmed(rowIndex, 0))
    {
        int blockSize = board.get_rowHint(rowIndex, 0);
        isLeftBorderCheckNeeded[rowIndex] = false;
        
        for(int i = 0; i < blockSize; i++)
        {
            confirm_set_inRowTechnique(rowIndex, i, confirmedDotData);
        }
        
        if(blockSize < colSize)
        {
            confirm_blank_inRowTechnique(rowIndex, blockSize, confirmedDotData);
        }
    }
    else if(isLeftBorderCheckNeeded[rowIndex] && confirmedDotData.get_isBlankConfirmed(rowIndex, 0))
    {
        isLeftBorderCheckNeeded[rowIndex] = false;
    }
    
    if(isRightBorderCheckNeeded[rowIndex] && confirmedDotData.get_isSetConfirmed(rowIndex, colSize - 1))
    {
        int blockSize = board.get_rowHint(rowIndex, board.get_numOfRowHint(rowIndex) - 1);
        isRightBorderCheckNeeded[rowIndex] = false;
        
        for(int i = 0; i < blockSize; i++)
        {
            confirm_set_inRowTechnique(rowIndex, colSize - i - 1, confirmedDotData);
        }
        
        if(blockSize < colSize)
        {
            confirm_blank_inRowTechnique(rowIndex, colSize - blockSize - 1, confirmedDotData);
        }
    }
    else if(isRightBorderCheckNeeded[rowIndex] && confirmedDotData.get_isBlankConfirmed(rowIndex, colSize - 1))
    {
        isRightBorderCheckNeeded[rowIndex] = false;
    }
}
        
void BorderChecker::adopt_techniqueInCol(int colIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
    if(isUpperBorderCheckNeeded[colIndex] && confirmedDotData.get_isSetConfirmed(0, colIndex))
    {
        int blockSize = board.get_colHint(colIndex, 0);
        isUpperBorderCheckNeeded[colIndex] = false;
        
        for(int i = 0; i < blockSize; i++)
        {
            confirm_set_inColTechnique(i, colIndex, confirmedDotData);
        }
        
        if(blockSize < rowSize)
        {
            confirm_blank_inColTechnique(blockSize, colIndex, confirmedDotData);
        }
    }
    else if(isUpperBorderCheckNeeded[colIndex] && confirmedDotData.get_isBlankConfirmed(0, colIndex))
    {
        isUpperBorderCheckNeeded[colIndex] = false;
    }
    
    if(isLowerBorderCheckNeeded[colIndex] && confirmedDotData.get_isSetConfirmed(rowSize - 1, colIndex))
    {
        int blockSize = board.get_colHint(colIndex, board.get_numOfColHint(colIndex) - 1);
        isLowerBorderCheckNeeded[colIndex] = false;
        
        for(int i = 0; i < blockSize; i++)
        {
            confirm_set_inColTechnique(rowSize - i - 1, colIndex, confirmedDotData);
        }
        
        if(blockSize < rowSize)
        {
            confirm_blank_inColTechnique(rowSize - blockSize - 1, colIndex, confirmedDotData);
        }
    }
    else if(isLowerBorderCheckNeeded[colIndex] && confirmedDotData.get_isBlankConfirmed(rowSize - 1, colIndex))
    {
        isLowerBorderCheckNeeded[colIndex] = false;
    }
}

