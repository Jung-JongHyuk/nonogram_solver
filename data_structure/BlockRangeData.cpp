#include "BlockRangeData.h"

BlockRangeData::BlockRangeData() : BlockRangeData(0,0) {}

BlockRangeData::BlockRangeData(int rowSize, int colSize)
{
    this->rowSize = rowSize;
    this->colSize = colSize;
    isErrorDetected = false;
    rowBlockRange.resize(rowSize);
    colBlockRange.resize(colSize);
}

void BlockRangeData::set_blockRange(Board& board)
{
    int blockSize, numOfBlock;
    
    for(int i = 0; i < rowSize; i++) //in row index i
    {
        int currentStartIndex = 0;
        numOfBlock = board.get_numOfRowHint(i);
        rowBlockRange[i].resize(numOfBlock);
        
        for(int j = 0; j < numOfBlock; j++) //at each row block in row index i
        {
            rowBlockRange[i][j].first = currentStartIndex;
            currentStartIndex += board.get_rowHint(i, j) + 1;
        }
        
        int currentEndIndex = colSize - 1;
        
        for(int j = numOfBlock - 1; j >= 0; j -= 1)
        {
            rowBlockRange[i][j].second = currentEndIndex;
            currentEndIndex -= board.get_rowHint(i, j) + 1;
        }
    }
    
    for(int i = 0; i < colSize; i++) //in col index i
    {
        int currentStartIndex = 0;
        numOfBlock = board.get_numOfColHint(i);
        colBlockRange[i].resize(numOfBlock);
        
        for(int j = 0; j < numOfBlock; j++) //at each col block in col index i
        {
            colBlockRange[i][j].first = currentStartIndex;
            currentStartIndex += board.get_colHint(i, j) + 1;
        }
        
        int currentEndIndex = rowSize - 1;
        
        for(int j = numOfBlock - 1; j >= 0; j -= 1)
        {
            colBlockRange[i][j].second = currentEndIndex;
            currentEndIndex -= board.get_colHint(i, j) + 1;
        }
    }
}

pair<int,int> BlockRangeData::get_rowBlockRange(int rowIndex, int rowBlockIndex)
{
    if(check_isRowBlockIndexInvalid(rowIndex, rowBlockIndex))
    {
        //isErrorDetected = true;
        //return pair<int,int>(0,0);
        throw IndexOutOfRange();
    }
    else
    {
        return rowBlockRange[rowIndex][rowBlockIndex];
    }
}

pair<int,int> BlockRangeData::get_colBlockRange(int colIndex, int colBlockIndex)
{
    if(check_isColBlockIndexInvalid(colIndex, colBlockIndex))
    {
        //isErrorDetected = true;
        //return pair<int,int>(0,0);
        throw IndexOutOfRange();
    }
    else
    {
        return colBlockRange[colIndex][colBlockIndex];
    }
}

void BlockRangeData::set_rowBlockRange(int rowIndex, int rowBlockIndex, pair<int,int> blockRange)
{
    if(check_isIndexOutOfRange(rowIndex, 0) || check_isRowBlockRangeInvalid(blockRange.first, blockRange.second))
    {
        //isErrorDetected = true;
        throw IndexOutOfRange();
    }
    else
    {
        rowBlockRange[rowIndex][rowBlockIndex] = blockRange;
    }
}

void BlockRangeData::set_colBlockRange(int colIndex, int colBlockIndex, pair<int,int> blockRange)
{
    if(check_isIndexOutOfRange(0, colIndex) || check_isColBlockRangeInvalid(blockRange.first, blockRange.second))
    {
        //isErrorDetected = true;
        throw IndexOutOfRange();
    }
    else
    {
        colBlockRange[colIndex][colBlockIndex] = blockRange;
    }
}

bool BlockRangeData::get_isErrorDetected() const
{
    return isErrorDetected;
}

bool BlockRangeData::check_isIndexOutOfRange(int rowIndex, int colIndex) const
{
    return rowIndex < 0 || colIndex < 0 || rowIndex > rowSize - 1 || colIndex > colSize - 1;
}

bool BlockRangeData::check_isRowBlockIndexInvalid(int rowIndex, int blockIndex) const
{
    return check_isIndexOutOfRange(rowIndex, 0) || blockIndex < 0 || blockIndex >= rowBlockRange[rowIndex].size();
}

bool BlockRangeData::check_isColBlockIndexInvalid(int colIndex, int blockIndex) const
{
    return check_isIndexOutOfRange(0, colIndex) || blockIndex < 0 || blockIndex >= colBlockRange[colIndex].size();
}

bool BlockRangeData::check_isRowBlockRangeInvalid(int startIndex, int endIndex) const
{
    return startIndex > endIndex || startIndex < 0 || endIndex > colSize - 1;
}

bool BlockRangeData::check_isColBlockRangeInvalid(int startIndex, int endIndex) const
{
    return startIndex > endIndex || startIndex < 0 || endIndex > rowSize - 1;
}
