#include "DotConfirmEngine.h"

DotConfirmEngine::DotConfirmEngine() {}

DotConfirmEngine::DotConfirmEngine(int rowSize, int colSize)
{
    this->rowSize = rowSize;
    this->colSize = colSize;
    blockRangeData = BlockRangeData(rowSize, colSize);
    heuristicTechnique = HeuristicTechnique(rowSize, colSize);
    absurdityTechnique = AbsurdityTechnique(rowSize, colSize);
}

void DotConfirmEngine::confirm_dot(Board& board, ConfirmedDotData& confirmedDotData, RuleChecker& ruleChecker)
{
    blockRangeData.set_blockRange(board);

    while(confirmedDotData.get_numOfUnconfirmedDot() > 0)
    {
        heuristicTechnique.sync_confirmedDotData(confirmedDotData);
        heuristicTechnique.adopt_heuristicTechnique(board, confirmedDotData, blockRangeData);

        int numOfUnconfirmedDotBeforeTechniqueAdoption = confirmedDotData.get_numOfUnconfirmedDot();
        absurdityTechnique.adopt_absurdityTechnique(board, confirmedDotData, blockRangeData, heuristicTechnique);

        if(numOfUnconfirmedDotBeforeTechniqueAdoption == confirmedDotData.get_numOfUnconfirmedDot())
        {
            break;
        }

    }

}

void DotConfirmEngine::adopt_heuristicTechnique(int rowIndex, int startColIndex, int endColIndex, Board& board, ConfirmedDotData& confirmedDotData)
{
    heuristicTechnique.adopt_heuristicTechnique(rowIndex, startColIndex, endColIndex, board, confirmedDotData, blockRangeData);
}

bool DotConfirmEngine::adopt_absurdityTechnique(int rowIndex, int startColIndex, int endColIndex, Board& board, ConfirmedDotData& confirmedDotData)
{
    return absurdityTechnique.adopt_absurdityTechnique(rowIndex, startColIndex, endColIndex, board, confirmedDotData, blockRangeData, heuristicTechnique);
}


