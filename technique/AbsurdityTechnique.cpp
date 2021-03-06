#include "AbsurdityTechnique.h"

AbsurdityTechnique::AbsurdityTechnique() : AbsurdityTechnique(0,0) {}

AbsurdityTechnique::AbsurdityTechnique(int rowSize, int colSize)
{
    this->rowSize = rowSize;
    this->colSize = colSize;
}

void absurdityCheckWorker(AbsurdityTechnique* delegate, pair<int,int> index, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData, HeuristicTechnique& heuristicTechnique, mutex& confirmedDotDataLock)
{
    ConfirmedDotData absurdityConfirmedDotData;
    BlockRangeData absurdityBlockRangeData;
    HeuristicTechnique absurdityHeuristicTechnique;
    absurdityConfirmedDotData = confirmedDotData;
    absurdityBlockRangeData = blockRangeData;
    absurdityHeuristicTechnique = heuristicTechnique;
    absurdityConfirmedDotData.set_isSetConfirmed(index.first, index.second, true);

    if(!delegate->check_isAssumptionValid(index, board, absurdityConfirmedDotData, absurdityBlockRangeData, absurdityHeuristicTechnique))
    {
        confirmedDotDataLock.lock();
        confirmedDotData.set_isBlankConfirmed(index.first, index.second, true);
        confirmedDotDataLock.unlock();
        return;
    }

    absurdityConfirmedDotData = confirmedDotData;
    absurdityBlockRangeData = blockRangeData;
    absurdityHeuristicTechnique = heuristicTechnique;
    absurdityConfirmedDotData.set_isBlankConfirmed(index.first, index.second, true);

    if(!delegate->check_isAssumptionValid(index, board, absurdityConfirmedDotData, absurdityBlockRangeData, absurdityHeuristicTechnique))
    {
        confirmedDotDataLock.lock();
        confirmedDotData.set_isSetConfirmed(index.first, index.second, true);
        confirmedDotDataLock.unlock();
        return;
    }
}

void AbsurdityTechnique::adopt_absurdityTechnique(Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData, HeuristicTechnique& heuristicTechnique)
{
    set_techniqueAdoptionPriorityArray(confirmedDotData);
    int numOfThread = thread::hardware_concurrency();
    vector<thread> threads;
    mutex confirmedDotDataLock;
    
    for(int i = 0; i < techniqueAdoptionPriorityArray.size(); i += numOfThread)
    {
        int initial = confirmedDotData.get_numOfUnconfirmedDot();
        for(int j = 0; j < numOfThread; j++)
        {
            if(i + j >= techniqueAdoptionPriorityArray.size())
            {
                break;
            }
            threads.push_back(thread(absurdityCheckWorker, this, techniqueAdoptionPriorityArray[i+j].first, ref(board), ref(confirmedDotData), ref(blockRangeData), ref(heuristicTechnique), ref(confirmedDotDataLock)));
        }
        for(int j = 0; j < threads.size(); j++)
        {
            threads[j].join();
        }
        if(confirmedDotData.get_numOfUnconfirmedDot() != initial)
        {
            break;
        }
        threads.clear();
    }
}

bool AbsurdityTechnique::adopt_absurdityTechnique(int rowIndex, int startColIndex, int endColIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData, HeuristicTechnique& heuristicTechnique)
{
    BlockRangeData absurdityBlockRangeData = blockRangeData;
    HeuristicTechnique absurdityHeuristicTechnique = heuristicTechnique;
    
    return check_isAssumptionValid(rowIndex, startColIndex, endColIndex, board, confirmedDotData, absurdityBlockRangeData, absurdityHeuristicTechnique);
}

void AbsurdityTechnique::set_techniqueAdoptionPriorityArray(ConfirmedDotData& confirmedDotData)
{
    techniqueAdoptionPriorityArray.clear();
    
    for(int i = 0; i < rowSize; i++)
    {
        for(int j = 0; j < colSize; j++)
        {
            if(!confirmedDotData.is_confirmed(i, j))
            {
                int numOfAdjacentConfirmedDot = get_numOfadjacentConfirmedDot(i, j, confirmedDotData);
                
                if(numOfAdjacentConfirmedDot > 0)
                {
                    pair<int,int> currentIndex(i, j);
                    techniqueAdoptionPriorityArray.push_back(pair<pair<int,int>,int>(currentIndex, numOfAdjacentConfirmedDot));
                }
            }
        }
    }
    
    sort(begin(techniqueAdoptionPriorityArray), end(techniqueAdoptionPriorityArray), [&confirmedDotData](const pair<pair<int,int>,int>& leftItem, const pair<pair<int,int>,int>& rightItem)
    {
        pair<int,int> leftIndex = leftItem.first, rightIndex = rightItem.first;
        int numOfAdjacentConfirmedDotOfLeft = leftItem.second, numOfAdjacentConfirmedDotOfRight = rightItem.second;
        int numOfUnconfirmedDotInRowOfLeft = confirmedDotData.get_numOfUnconfirmedDotInRow(leftIndex.first);
        int numOfUnconfirmedDotInColOfLeft = confirmedDotData.get_numOfUnconfirmedDotInCol(leftIndex.second);
        int numOfUnconfirmedDotInRowOfRight = confirmedDotData.get_numOfUnconfirmedDotInRow(rightIndex.first);
        int numOfUnconfirmedDotInColOfRight = confirmedDotData.get_numOfUnconfirmedDotInCol(rightIndex.second);
        
        int numOfMoreUnconfirmedDotOfLeft = max(numOfUnconfirmedDotInRowOfLeft, numOfUnconfirmedDotInColOfLeft);
        int numOfLessUnconfirmedDotOfLeft = min(numOfUnconfirmedDotInRowOfLeft, numOfUnconfirmedDotInColOfLeft);
        int numOfMoreUnconfirmedDotOfRight = max(numOfUnconfirmedDotInRowOfRight, numOfUnconfirmedDotInColOfRight);
        int numOfLessUnconfirmedDotOfRight = min(numOfUnconfirmedDotInRowOfRight, numOfUnconfirmedDotInColOfRight);
        
        if(numOfAdjacentConfirmedDotOfLeft > numOfAdjacentConfirmedDotOfRight)
        {
            return true;
        }
        else if(numOfAdjacentConfirmedDotOfLeft == numOfAdjacentConfirmedDotOfRight)
        {
            if(numOfLessUnconfirmedDotOfLeft < numOfLessUnconfirmedDotOfRight)
            {
                return true;
            }
            else if(numOfLessUnconfirmedDotOfLeft == numOfLessUnconfirmedDotOfRight)
            {
                if(numOfMoreUnconfirmedDotOfLeft < numOfMoreUnconfirmedDotOfRight)
                {
                    return true;
                }
            }
        }
        
        return false;
    });
}

bool AbsurdityTechnique::check_isAssumptionValid(pair<int,int> assumptionIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData, HeuristicTechnique& heuristicTechnique)
{
    int numOfHeuristicChecker = heuristicTechnique.get_numOfChecker();
    heuristicTechnique.update_isUpdateNeeded(assumptionIndex.first, assumptionIndex.second, confirmedDotData);
    
    try
    {
        while(heuristicTechnique.is_heuristicTechniqueAvailable())
        {
            for(int i = 0; i < numOfHeuristicChecker; i++)
            {
                heuristicTechnique.adopt_checker(i, board, confirmedDotData, blockRangeData);
            }
        }
    }
    catch(IndexOutOfRange& error)
    {
        return false;
    }
    
    return true;
}

bool AbsurdityTechnique::check_isAssumptionValid(int assumptionRowIndex, int assumptionColStartIndex, int assumptionColEndIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData, HeuristicTechnique& heuristicTechnique)
{
    int numOfHeuristicChecker = heuristicTechnique.get_numOfChecker();
    
    for(int i = assumptionColStartIndex; i <= assumptionColEndIndex; i++)
    {
        heuristicTechnique.update_isUpdateNeeded(assumptionRowIndex, i, confirmedDotData);
    }
    
    while(heuristicTechnique.is_heuristicTechniqueAvailable())
    {
        for(int i = 0; i < numOfHeuristicChecker; i++)
        {
            heuristicTechnique.adopt_checker(i, board, confirmedDotData, blockRangeData);
            
            if(confirmedDotData.get_isErrorDetected() || blockRangeData.get_isErrorDetected())
            {
                return false;
            }
        }
    }
    
    return true;
}

bool AbsurdityTechnique::get_numOfadjacentConfirmedDot(int rowIndex, int colIndex, ConfirmedDotData& confirmedDotData)
{
    int numOfAdjacentConfirmedDot = 0;
    
    if(rowIndex > 0 && confirmedDotData.is_confirmed(rowIndex - 1, colIndex))
    {
        numOfAdjacentConfirmedDot++;
    }
    
    if(rowIndex < rowSize - 1 && confirmedDotData.is_confirmed(rowIndex + 1, colIndex))
    {
        numOfAdjacentConfirmedDot++;
    }
    
    if(colIndex > 0 && confirmedDotData.is_confirmed(rowIndex, colIndex - 1))
    {
        numOfAdjacentConfirmedDot++;
    }
    
    if(colIndex < colSize - 1 && confirmedDotData.is_confirmed(rowIndex, colIndex + 1))
    {
        numOfAdjacentConfirmedDot++;
    }
    
    if(rowIndex == 0 && confirmedDotData.is_confirmed(rowIndex + 1, colIndex))
    {
        numOfAdjacentConfirmedDot++;
    }
    
    if(rowIndex == rowSize - 1 && confirmedDotData.is_confirmed(rowIndex - 1, colIndex))
    {
        numOfAdjacentConfirmedDot++;
    }
    
    if(colIndex == 0 && confirmedDotData.is_confirmed(rowIndex, colIndex + 1))
    {
        numOfAdjacentConfirmedDot++;
    }
    
    if(colIndex == colSize - 1 && confirmedDotData.is_confirmed(rowIndex, colIndex - 1))
    {
        numOfAdjacentConfirmedDot++;
    }
    
    return numOfAdjacentConfirmedDot;
}

