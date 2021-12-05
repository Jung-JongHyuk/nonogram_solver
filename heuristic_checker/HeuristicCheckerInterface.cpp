#include "HeuristicCheckerInterface.h"

HeuristicCheckerInterface::HeuristicCheckerInterface() : HeuristicCheckerInterface(0,0) {}

HeuristicCheckerInterface::HeuristicCheckerInterface(int rowSize, int colSize)
{
    this->rowSize = rowSize;
    this->colSize = colSize;
    isUpdateNeeded = true;
    isRowUpdateNeeded.resize(rowSize, true);
    isColUpdateNeeded.resize(colSize, true);
    heuristicCheckerAdoptionResult = HeuristicCheckerAdoptionResult(rowSize, colSize);
}

HeuristicCheckerInterface& HeuristicCheckerInterface::operator=(const HeuristicCheckerInterface& heuristicCheckerInterface)
{
    if(this != &heuristicCheckerInterface)
    {
        rowSize = heuristicCheckerInterface.rowSize;
        colSize = heuristicCheckerInterface.colSize;
        isRowUpdateNeeded = heuristicCheckerInterface.isRowUpdateNeeded;
        isColUpdateNeeded = heuristicCheckerInterface.isColUpdateNeeded;
        heuristicCheckerAdoptionResult = heuristicCheckerInterface.heuristicCheckerAdoptionResult;
        checkerInfo = heuristicCheckerInterface.checkerInfo;
    }
    
    return *this;
}

void HeuristicCheckerInterface::confirm_set_inRowTechnique(int rowIndex, int colIndex, ConfirmedDotData& confirmedDotData)
{
    if(!confirmedDotData.get_isSetConfirmed(rowIndex, colIndex))
    {
        confirmedDotData.set_isSetConfirmed(rowIndex, colIndex, true);
        
        if(!confirmedDotData.get_isErrorDetected())
        {
            heuristicCheckerAdoptionResult.set_isConfirmedByRowTechnique(rowIndex, colIndex, true);
        }
    }
}
        
void HeuristicCheckerInterface::confirm_blank_inRowTechnique(int rowIndex, int colIndex, ConfirmedDotData& confirmedDotData)
{
    if(!confirmedDotData.get_isBlankConfirmed(rowIndex, colIndex))
    {
        confirmedDotData.set_isBlankConfirmed(rowIndex, colIndex, true);
        
        if(!confirmedDotData.get_isErrorDetected())
        {
            heuristicCheckerAdoptionResult.set_isConfirmedByRowTechnique(rowIndex, colIndex, true);
        }
    }
}
        
void HeuristicCheckerInterface::confirm_set_inColTechnique(int rowIndex, int colIndex, ConfirmedDotData& confirmedDotData)
{
    if(!confirmedDotData.get_isSetConfirmed(rowIndex, colIndex))
    {
        confirmedDotData.set_isSetConfirmed(rowIndex, colIndex, true);
        
        if(!confirmedDotData.get_isErrorDetected())
        {
            heuristicCheckerAdoptionResult.set_isConfirmedByColTechnique(rowIndex, colIndex, true);
        }
    }
}
        
void HeuristicCheckerInterface::confirm_blank_inColTechnique(int rowIndex, int colIndex, ConfirmedDotData& confirmedDotData)
{
    if(!confirmedDotData.get_isBlankConfirmed(rowIndex, colIndex))
    {
        confirmedDotData.set_isBlankConfirmed(rowIndex, colIndex, true);
        
        if(!confirmedDotData.get_isErrorDetected())
        {
            heuristicCheckerAdoptionResult.set_isConfirmedByColTechnique(rowIndex, colIndex, true);
        }
    }
}

void HeuristicCheckerInterface::change_rowBlockRange(int rowIndex, int blockIndex, pair<int,int> blockRange, BlockRangeData& blockRangeData)
{
    if(blockRangeData.get_rowBlockRange(rowIndex, blockIndex) != blockRange)
    {
        blockRangeData.set_rowBlockRange(rowIndex, blockIndex, blockRange);
        
        if(!blockRangeData.get_isErrorDetected())
        {
            heuristicCheckerAdoptionResult.set_isRowBlockRangeChanged(rowIndex, true);
        }
    }
}

void HeuristicCheckerInterface::change_colBlockRange(int colIndex, int blockIndex, pair<int,int> blockRange, BlockRangeData& blockRangeData)
{
    if(blockRangeData.get_colBlockRange(colIndex, blockIndex) != blockRange)
    {
        blockRangeData.set_colBlockRange(colIndex, blockIndex, blockRange);
        
        if(!blockRangeData.get_isErrorDetected())
        {
            heuristicCheckerAdoptionResult.set_isColBlockRangeChanged(colIndex, true);
        }
    }
}

bool HeuristicCheckerInterface::get_isUpdateNeeded() const
{
    return isUpdateNeeded;
}

bool HeuristicCheckerInterface::get_isRowUpdateNeeded(int rowIndex) const
{
    return isRowUpdateNeeded[rowIndex];
}

bool HeuristicCheckerInterface::get_isColUpdateNeeded(int colIndex) const
{
    return isColUpdateNeeded[colIndex];
}

void HeuristicCheckerInterface::set_isUpdateNeeded(bool value)
{
    isUpdateNeeded = value;
}

void HeuristicCheckerInterface::set_isRowUpdateNeeded(int rowIndex, bool value)
{
    isRowUpdateNeeded[rowIndex] = value;
}

void HeuristicCheckerInterface::set_isColUpdateNeeded(int colIndex, bool value)
{
    isColUpdateNeeded[colIndex] = value;
}

void HeuristicCheckerInterface::clear_techniqueAdoptionResult()
{
    for(int i = 0; i < rowSize; i++)
    {
        for(int j = 0; j < colSize; j++)
        {
            heuristicCheckerAdoptionResult.set_isConfirmedByRowTechnique(i, j, false);
            heuristicCheckerAdoptionResult.set_isConfirmedByColTechnique(i, j, false);
        }
    }
    
    for(int i = 0; i < rowSize; i++)
    {
        heuristicCheckerAdoptionResult.set_isRowBlockRangeChanged(i, false);
    }
    
    for(int i = 0; i < colSize; i++)
    {
        heuristicCheckerAdoptionResult.set_isColBlockRangeChanged(i, false);
    }
}

const HeuristicCheckerAdoptionResult& HeuristicCheckerInterface::get_checkerAdoptionResult() const
{
    return heuristicCheckerAdoptionResult;
}

const CheckerInfo& HeuristicCheckerInterface::get_checkerInfo() const
{
    return checkerInfo;
}
