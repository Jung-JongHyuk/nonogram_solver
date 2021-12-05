#include "ConfirmCompleteChecker.h"

ConfirmCompleteChecker::ConfirmCompleteChecker() : ConfirmCompleteChecker(0,0) {}

ConfirmCompleteChecker::ConfirmCompleteChecker(int rowSize, int colSize) : HeuristicCheckerInterface(rowSize, colSize)
{
    checkerInfo = CheckerInfo(true, true, false, true, true, false, "ConfirmCompleteChecker");
}

void ConfirmCompleteChecker::adopt_techniqueInRow(int rowIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
    int hintSum = board.get_rowHintSum(rowIndex);
    
    if(confirmedDotData.get_numOfSetConfirmedDotInRow(rowIndex) == hintSum)
    {
        for(int i = 0; i < colSize; i++)
        {
            if(!confirmedDotData.get_isSetConfirmed(rowIndex, i))
            {
                confirm_blank_inRowTechnique(rowIndex, i, confirmedDotData);
            }
        }
    }
    else if(confirmedDotData.get_numOfBlankConfirmedDotInRow(rowIndex) == colSize - hintSum)
    {
        for(int i = 0; i < colSize; i++)
        {
            if(!confirmedDotData.get_isBlankConfirmed(rowIndex, i))
            {
                confirm_set_inRowTechnique(rowIndex, i, confirmedDotData);
            }
        }
    }
}

void ConfirmCompleteChecker::adopt_techniqueInCol(int colIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
    int hintSum = board.get_colHintSum(colIndex);
    
    if(confirmedDotData.get_numOfSetConfirmedDotInCol(colIndex) == hintSum)
    {
        for(int i = 0; i < rowSize; i++)
        {
            if(!confirmedDotData.get_isSetConfirmed(i, colIndex))
            {
                confirm_blank_inColTechnique(i, colIndex, confirmedDotData);
            }
        }
    }
    else if(confirmedDotData.get_numOfBlankConfirmedDotInCol(colIndex) == rowSize - hintSum)
    {
        for(int i = 0; i < rowSize; i++)
        {
            if(!confirmedDotData.get_isBlankConfirmed(i, colIndex))
            {
                confirm_set_inColTechnique(i, colIndex, confirmedDotData);
            }
        }
    }
}
