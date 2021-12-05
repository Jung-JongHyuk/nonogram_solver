#include "ConfirmedDotData.h"

ConfirmedDotData::ConfirmedDotData() : ConfirmedDotData(0,0) {}

ConfirmedDotData::ConfirmedDotData(int rowSize, int colSize)
{
    this->rowSize = rowSize;
    this->colSize = colSize;
    isSetConfirmed.resize(rowSize);
    isBlankConfirmed.resize(rowSize);
    numOfUnconfirmedDotInRow.resize(rowSize, colSize);
    numOfUnconfirmedDotInCol.resize(colSize, rowSize);
    numOfSetConfirmedDotInRow.resize(rowSize, 0);
    numOfBlankConfirmedDotInRow.resize(rowSize, 0);
    numOfSetConfirmedDotInCol.resize(colSize, 0);
    numOfBlankConfirmedDotInCol.resize(colSize, 0);
    numOfUnconfirmedDot = rowSize * colSize;
    numOfSetConfirmedDot = 0;
    numOfBlankConfirmedDot = 0;
    isErrorDetected = false;
    
    for(int i = 0; i < rowSize; i++)
    {
        isSetConfirmed[i].resize(colSize, false);
        isBlankConfirmed[i].resize(colSize, false);
    }
}

bool ConfirmedDotData::get_isSetConfirmed(int rowIndex, int colIndex)
{
    if(check_isIndexOutOfRange(rowIndex, colIndex))
    {
        //isErrorDetected = true;
        //return false;
        throw IndexOutOfRange();
    }
    else if(!isErrorDetected)
    {
        return isSetConfirmed[rowIndex][colIndex];
    }
    else
    {
        return true;
    }
}

bool ConfirmedDotData::get_isBlankConfirmed(int rowIndex, int colIndex)
{
    if(check_isIndexOutOfRange(rowIndex, colIndex))
    {
        //isErrorDetected = true;
        //return false;
        throw IndexOutOfRange();
    }
    else if(!isErrorDetected)
    {
        return isBlankConfirmed[rowIndex][colIndex];
    }
    else
    {
        return true;
    }
}

void ConfirmedDotData::set_isSetConfirmed(int rowIndex, int colIndex, bool value)
{
    if(check_isIndexOutOfRange(rowIndex, colIndex) || (value && isBlankConfirmed[rowIndex][colIndex]))
    {
        //isErrorDetected = true;
        throw IndexOutOfRange();
    }
    else if(value != isSetConfirmed[rowIndex][colIndex] && !isErrorDetected)
    {
        isSetConfirmed[rowIndex][colIndex] = value;
        numOfUnconfirmedDotInRow[rowIndex] += value ? -1 : 1;
        numOfUnconfirmedDotInCol[colIndex] += value ? -1 : 1;
        numOfUnconfirmedDot += value ? -1 : 1;
        numOfSetConfirmedDotInRow[rowIndex] += value ? 1 : -1;
        numOfSetConfirmedDotInCol[colIndex] += value ? 1 : -1;
        numOfSetConfirmedDot += value ? 1 : -1;
    }
}
    
void ConfirmedDotData::set_isBlankConfirmed(int rowIndex, int colIndex, bool value)
{
    if(check_isIndexOutOfRange(rowIndex, colIndex) || (value && isSetConfirmed[rowIndex][colIndex]))
    {
        //isErrorDetected = true;
        throw IndexOutOfRange();
    }
    else if(value != isBlankConfirmed[rowIndex][colIndex] && !isErrorDetected)
    {
        isBlankConfirmed[rowIndex][colIndex] = value;
        numOfUnconfirmedDotInRow[rowIndex] += value ? -1 : 1;
        numOfUnconfirmedDotInCol[colIndex] += value ? -1 : 1;
        numOfUnconfirmedDot += value ? -1 : 1;
        numOfBlankConfirmedDotInRow[rowIndex] += value ? 1 : -1;
        numOfBlankConfirmedDotInCol[colIndex] += value ? 1 : -1;
        numOfBlankConfirmedDot += value ? 1 : -1;
    }
}

bool ConfirmedDotData::is_confirmed(int rowIndex, int colIndex)
{
    if(check_isIndexOutOfRange(rowIndex, colIndex))
    {
        //isErrorDetected = true;
        //return false;
        throw IndexOutOfRange();
    }
    else if(!isErrorDetected)
    {
        return (isSetConfirmed[rowIndex][colIndex] || isBlankConfirmed[rowIndex][colIndex]);
    }
    else
    {
        return true;
    }
}

bool ConfirmedDotData::get_isErrorDetected() const
{
    return isErrorDetected;
}

int ConfirmedDotData::get_numOfUnconfirmedDotInRow(int rowIndex)
{
    if(check_isIndexOutOfRange(rowIndex, 0))
    {
        //isErrorDetected = true;
        //return 0;
        throw IndexOutOfRange();
    }
    else if(!isErrorDetected)
    {
        return numOfUnconfirmedDotInRow[rowIndex];
    }
    else
    {
        return 0;
    }
}

int ConfirmedDotData::get_numOfUnconfirmedDotInCol(int colIndex)
{
    if(check_isIndexOutOfRange(0, colIndex))
    {
        //isErrorDetected = true;
        //return 0;
        throw IndexOutOfRange();
    }
    else if(!isErrorDetected)
    {
        return numOfUnconfirmedDotInCol[colIndex];
    }
    else
    {
        return 0;
    }
}

int ConfirmedDotData::get_numOfUnconfirmedDot() const
{
    return numOfUnconfirmedDot;
}

int ConfirmedDotData::get_numOfSetConfirmedDotInRow(int rowIndex)
{
    if(check_isIndexOutOfRange(rowIndex, 0))
    {
        //isErrorDetected = true;
        //return 0;
        throw IndexOutOfRange();
    }
    else if(!isErrorDetected)
    {
        return numOfSetConfirmedDotInRow[rowIndex];
    }
    else
    {
        return colSize;
    }
}

int ConfirmedDotData::get_numOfBlankConfirmedDotInRow(int rowIndex)
{
    if(check_isIndexOutOfRange(rowIndex, 0))
    {
        //isErrorDetected = true;
        //return 0;
        throw IndexOutOfRange();
    }
    else if(!isErrorDetected)
    {
        return numOfBlankConfirmedDotInRow[rowIndex];
    }
    else
    {
        return rowSize;
    }
}

int ConfirmedDotData::get_numOfSetConfirmedDotInCol(int colIndex)
{
    if(check_isIndexOutOfRange(0, colIndex))
    {
        //isErrorDetected = true;
        //return 0;
        throw IndexOutOfRange();
    }
    else if(!isErrorDetected)
    {
        return numOfSetConfirmedDotInCol[colIndex];
    }
    else
    {
        return rowSize;
    }
}

int ConfirmedDotData::get_numOfBlankConfirmedDotInCol(int colIndex)
{
    if(check_isIndexOutOfRange(0, colIndex))
    {
        //isErrorDetected = true;
        //return 0;
        throw IndexOutOfRange();
    }
    else if(!isErrorDetected)
    {
        return numOfBlankConfirmedDotInCol[colIndex];
    }
    else
    {
        return rowSize;
    }
}

int ConfirmedDotData::get_numOfSetConfirmedDot() const
{
    return numOfSetConfirmedDot;
}

int ConfirmedDotData::get_numOfBlankConfirmedDot() const
{
    return numOfBlankConfirmedDot;
}

bool ConfirmedDotData::check_isIndexOutOfRange(int rowIndex, int colIndex) const
{
    return rowIndex < 0 || colIndex < 0 || rowIndex > rowSize - 1 || colIndex > colSize - 1;
}
