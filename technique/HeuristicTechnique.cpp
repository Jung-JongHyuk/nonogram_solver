#include "HeuristicTechnique.h"

HeuristicTechnique::HeuristicTechnique() : HeuristicTechnique(0,0) {}

HeuristicTechnique::HeuristicTechnique(int rowSize, int colSize)
{
    this->rowSize = rowSize;
    this->colSize = colSize;
    make_checkerArray();
}

HeuristicTechnique::~HeuristicTechnique()
{
    for(int i = 0; i < checkerArray.size(); i++)
    {
        delete checkerArray[i];
    }
}

HeuristicTechnique& HeuristicTechnique::operator=(const HeuristicTechnique& heuristicTechnique)
{
    if(this != &heuristicTechnique)
    {
        this->rowSize = heuristicTechnique.rowSize;
        this->colSize = heuristicTechnique.colSize;
        this->capturedConfirmedDotData = heuristicTechnique.capturedConfirmedDotData;

        for(int i = 0; i < checkerArray.size(); i++)
        {
            *checkerArray[i] = *heuristicTechnique.checkerArray[i];
        }
    }

    return *this;
}

void HeuristicTechnique::adopt_heuristicTechnique(Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
    while(is_heuristicTechniqueAvailable())
    {
        int numOfUnconfirmedDotBeforeTechniqueAdoption = confirmedDotData.get_numOfUnconfirmedDot();

        for(int i = 0; i < checkerArray.size(); i++)
        {
            adopt_checker(i, board, confirmedDotData, blockRangeData);
        }

        if(numOfUnconfirmedDotBeforeTechniqueAdoption > confirmedDotData.get_numOfUnconfirmedDot())
        {
            BoardViewer(rowSize, colSize).print_confirmedDot(confirmedDotData);
        }
    }

    if(capturedConfirmedDotData.get_numOfUnconfirmedDot() != confirmedDotData.get_numOfUnconfirmedDot())
    {
        capturedConfirmedDotData = confirmedDotData;
    }
}

void HeuristicTechnique::adopt_heuristicTechnique(int rowIndex, int colStartIndex, int colEndIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
    for(int i = colStartIndex; i <= colEndIndex; i++)
    {
        update_isUpdateNeeded(rowIndex, i, confirmedDotData);
    }

    adopt_heuristicTechnique(board, confirmedDotData, blockRangeData);
}

bool HeuristicTechnique::is_heuristicTechniqueAvailable() const
{
    for(int i = 0; i < checkerArray.size(); i++)
    {
        if(checkerArray[i]->get_isUpdateNeeded())
        {
            return true;
        }
    }

    return false;
}

void HeuristicTechnique::sync_confirmedDotData(ConfirmedDotData& confirmedDotData)
{
    if(confirmedDotData.get_numOfUnconfirmedDot() == capturedConfirmedDotData.get_numOfUnconfirmedDot())
    {
        return;
    }

    for(int i = 0; i < rowSize; i++)
    {
        for(int j = 0; j < colSize; j++)
        {
            if(confirmedDotData.is_confirmed(i, j) && !capturedConfirmedDotData.is_confirmed(i, j))
            {
                update_isUpdateNeeded(i, j, confirmedDotData);
            }
        }
    }
}

void HeuristicTechnique::update_isUpdateNeeded(int checkerIndex, ConfirmedDotData& confirmedDotData, const HeuristicCheckerAdoptionResult& heuristicCheckerAdoptionResult)
{
    for(int i = 0; i < checkerArray.size(); i++)
    {
        update_isUpdateNeeded(checkerIndex, i, confirmedDotData, heuristicCheckerAdoptionResult);
    }
}

void HeuristicTechnique::adopt_checker(int checkerIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData)
{
    for(int i = 0; i < rowSize; i++)
    {
        if(checkerArray[checkerIndex]->get_isRowUpdateNeeded(i))
        {
            checkerArray[checkerIndex]->adopt_techniqueInRow(i, board, confirmedDotData, blockRangeData);
            checkerArray[checkerIndex]->set_isRowUpdateNeeded(i, false);
        }
    }

    for(int i = 0; i < colSize; i++)
    {
        if(checkerArray[checkerIndex]->get_isColUpdateNeeded(i))
        {
            checkerArray[checkerIndex]->adopt_techniqueInCol(i, board, confirmedDotData, blockRangeData);
            checkerArray[checkerIndex]->set_isColUpdateNeeded(i, false);
        }
    }

    checkerArray[checkerIndex]->set_isUpdateNeeded(false);
    update_isUpdateNeeded(checkerIndex, confirmedDotData, checkerArray[checkerIndex]->get_checkerAdoptionResult());
    checkerArray[checkerIndex]->clear_techniqueAdoptionResult();
}


void HeuristicTechnique::update_isUpdateNeeded(int currentCheckerIndex, int checkerIndexToUpdate, ConfirmedDotData& confirmedDotData, const HeuristicCheckerAdoptionResult& heuristicCheckerAdoptionResult)
{
    CheckerInfo currentCheckerInfo = checkerArray[currentCheckerIndex]->get_checkerInfo();
    CheckerInfo checkerToUpdateInfo = checkerArray[checkerIndexToUpdate]->get_checkerInfo();

    for(int i = 0; i < rowSize; i++)
    {
        for(int j = 0; j < colSize; j++)
        {
            if(heuristicCheckerAdoptionResult.get_isConfirmedByColTechnique(i, j))
            {
                if(confirmedDotData.get_isSetConfirmed(i, j) && checkerToUpdateInfo.get_isUpdateNeededWhenSetConfirmed() && confirmedDotData.get_numOfUnconfirmedDotInRow(i) != 0)
                {
                    checkerArray[checkerIndexToUpdate]->set_isRowUpdateNeeded(i, true);
                    checkerArray[checkerIndexToUpdate]->set_isUpdateNeeded(true);
                }
                else if(confirmedDotData.get_isBlankConfirmed(i, j) && checkerToUpdateInfo.get_isUpdateNeededWhenBlankConfirmed() && confirmedDotData.get_numOfUnconfirmedDotInRow(i) != 0)
                {
                    checkerArray[checkerIndexToUpdate]->set_isRowUpdateNeeded(i, true);
                    checkerArray[checkerIndexToUpdate]->set_isUpdateNeeded(true);
                }
            }
            else if(heuristicCheckerAdoptionResult.get_isConfirmedByRowTechnique(i, j) && currentCheckerInfo.get_checkerName() != checkerToUpdateInfo.get_checkerName())
            {
                if(confirmedDotData.get_isSetConfirmed(i, j) && checkerToUpdateInfo.get_isUpdateNeededWhenSetConfirmed() && confirmedDotData.get_numOfUnconfirmedDotInCol(j) != 0)
                {
                    checkerArray[checkerIndexToUpdate]->set_isColUpdateNeeded(j, true);
                    checkerArray[checkerIndexToUpdate]->set_isUpdateNeeded(true);
                }
                else if(confirmedDotData.get_isBlankConfirmed(i, j) && checkerToUpdateInfo.get_isUpdateNeededWhenBlankConfirmed() && confirmedDotData.get_numOfUnconfirmedDotInCol(j) != 0)
                {
                    checkerArray[checkerIndexToUpdate]->set_isColUpdateNeeded(j, true);
                    checkerArray[checkerIndexToUpdate]->set_isUpdateNeeded(true);
                }
            }
        }
    }

    for(int i = 0; i < rowSize; i++)
    {
        if(heuristicCheckerAdoptionResult.get_isRowBlockRangeChanged(i) && checkerToUpdateInfo.get_isUpdateNeededWhenBlockRangeChanged() && confirmedDotData.get_numOfUnconfirmedDotInRow(i) != 0)
        {
            checkerArray[checkerIndexToUpdate]->set_isRowUpdateNeeded(i, true);
            checkerArray[checkerIndexToUpdate]->set_isUpdateNeeded(true);
        }
    }

    for(int i = 0; i < colSize; i++)
    {
        if(heuristicCheckerAdoptionResult.get_isColBlockRangeChanged(i) && checkerToUpdateInfo.get_isUpdateNeededWhenBlockRangeChanged() && confirmedDotData.get_numOfUnconfirmedDotInCol(i) != 0)
        {
            checkerArray[checkerIndexToUpdate]->set_isColUpdateNeeded(i, true);
            checkerArray[checkerIndexToUpdate]->set_isUpdateNeeded(true);
        }
    }
}

void HeuristicTechnique::update_isUpdateNeeded(int rowIndex, int colIndex, ConfirmedDotData& confirmedDotData)
{
    for(int i = 0; i < checkerArray.size(); i++)
    {
        CheckerInfo currentCheckerInfo = checkerArray[i]->get_checkerInfo();

        if((currentCheckerInfo.get_isUpdateNeededWhenSetConfirmed() && confirmedDotData.get_isSetConfirmed(rowIndex, colIndex)) || (currentCheckerInfo.get_isUpdateNeededWhenBlankConfirmed() && confirmedDotData.get_isBlankConfirmed(rowIndex, colIndex)))
        {
            if(confirmedDotData.get_numOfUnconfirmedDotInRow(rowIndex) != 0)
            {
                checkerArray[i]->set_isRowUpdateNeeded(rowIndex, true);
                checkerArray[i]->set_isUpdateNeeded(true);
            }

            if(confirmedDotData.get_numOfUnconfirmedDotInCol(i) != 0)
            {
                checkerArray[i]->set_isColUpdateNeeded(colIndex, true);
                checkerArray[i]->set_isUpdateNeeded(true);
            }
        }
    }
}

void HeuristicTechnique::make_checkerArray()
{
    checkerArray.push_back(new IntersectionChecker(rowSize, colSize));
    checkerArray.push_back(new MonoBlockRangeChecker(rowSize, colSize));
    checkerArray.push_back(new MaxBlockSizeChecker(rowSize, colSize));
    checkerArray.push_back(new BlockExpandableChecker(rowSize, colSize));
    checkerArray.push_back(new ConfirmCompleteChecker(rowSize, colSize));
    checkerArray.push_back(new BlockRangeOrderChecker(rowSize, colSize));
    checkerArray.push_back(new BlockRangeIntervalChecker(rowSize, colSize));
    checkerArray.push_back(new BlockRangeValidityChecker(rowSize, colSize));
    checkerArray.push_back(new BlockSegmentIntervalChecker(rowSize, colSize));
    checkerArray.push_back(new PotentialBlockSegmentChecker(rowSize, colSize));
    checkerArray.push_back(new BlockRangeBorderChecker(rowSize, colSize));
    checkerArray.push_back(new BlockRangeReductionChecker(rowSize, colSize));
    checkerArray.push_back(new BlockSegmentMergeChecker(rowSize, colSize));
}

int HeuristicTechnique::get_numOfChecker() const
{
    return checkerArray.size();
}

