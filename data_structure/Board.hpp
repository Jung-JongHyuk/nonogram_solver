#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class IndexOutOfRange {};
class BoardHintIndexOutOfRange {};

class Board
{
	public:
		Board();
		Board(int rowSize, int colSize);
		friend istream& operator>>(istream& inputStream, Board& board);
		
		//setter and getter
		void set_board(int rowIndex, int colIndex, bool dotValue);
		bool get_board(int rowIndex, int colIndex) const;
		int get_rowHint(int rowIndex, int rowHintIndex) const;
		int get_colHint(int colIndex, int colHintIndex) const;
		int get_rowHintSum(int rowIndex) const;
		int get_colHintSum(int colIndex) const;
		int get_numOfRowHint(int rowIndex) const;
		int get_numOfColHint(int colIndex) const;
	
		pair<int,int> get_boardSize() const;
	
	private:
		bool check_isRowIndexValid(int rowIndex) const;
		bool check_isColIndexValid(int colIndex) const;
		bool check_isRowHintIndexValid(int rowIndex, int rowHintIndex) const;
		bool check_isColHintIndexValid(int colIndex, int colHintIndex) const;
	
		int rowSize, colSize;
		vector<vector<bool>> dotArray;
		vector<vector<int>> rowHint, colHint;
		vector<int> rowHintSum, colHintSum;
};

//Board class

Board::Board() : Board(0,0) {}

Board::Board(int rowSize, int colSize)
{
	this->rowSize = rowSize;
	this->colSize = colSize;
	dotArray.resize(rowSize);
	rowHint.resize(rowSize);
	colHint.resize(colSize);
	rowHintSum.resize(rowSize);
	colHintSum.resize(colSize);
	
	for(int i = 0; i < rowSize; i++)
	{
		dotArray[i].resize(colSize, false);
	}
}

istream& operator>>(istream& inputStream, Board& board)
{
	int numberOfHint, sum = 0, overallRowHintSum = 0, overallColHintSum = 0;
	string buffer;
	
	for(int i = 0; i < board.rowSize; i++)
	{
		inputStream >> buffer;
		numberOfHint = stoi(buffer);
		inputStream >> buffer;
		board.rowHint[i].resize(numberOfHint);
		
		for(int j = 0; j < numberOfHint; j++)
		{
			inputStream >> buffer;
			board.rowHint[i][j] = stoi(buffer);
			sum += board.rowHint[i][j];
			overallRowHintSum += board.rowHint[i][j];
		}
		
		board.rowHintSum[i] = sum;
		sum = 0;
	}
	
	for(int i = 0; i < board.colSize; i++)
	{
		inputStream >> buffer;
		numberOfHint = stoi(buffer);
		inputStream >> buffer;
		board.colHint[i].resize(numberOfHint);
		
		for(int j = 0; j < numberOfHint; j++)
		{
			inputStream >> buffer;
			board.colHint[i][j] = stoi(buffer);
			sum += board.colHint[i][j];
			overallColHintSum += board.colHint[i][j];
		}
		
		board.colHintSum[i] = sum;
		sum = 0;
	}
	
	if(overallRowHintSum != overallColHintSum) //check is input Hint valid
	{
		cout << "Invalid puzzle" << endl;
		exit(1);
	}
	
	return inputStream;
}

void Board::set_board(int rowIndex, int colIndex, bool dotValue)
{
	if(check_isRowIndexValid(rowIndex) && check_isColIndexValid(colIndex))
	{
		dotArray[rowIndex][colIndex] = dotValue;
	}
	else
	{
		throw IndexOutOfRange();
	}	
}

bool Board::get_board(int rowIndex, int colIndex) const
{
	if(check_isRowIndexValid(rowIndex) && check_isColIndexValid(colIndex))
	{
		return dotArray[rowIndex][colIndex];
	}
	else
	{
		throw IndexOutOfRange();
	}
}

int Board::get_rowHint(int rowIndex, int rowHintIndex) const
{
	if(!check_isRowIndexValid(rowIndex))
	{
		throw IndexOutOfRange();
	}
	else if(!check_isRowHintIndexValid(rowIndex, rowHintIndex))
	{
		throw BoardHintIndexOutOfRange();
	}
	else
	{
		return rowHint[rowIndex][rowHintIndex];
	}
}

int Board::get_colHint(int colIndex, int colHintIndex) const
{
	if(!check_isColIndexValid(colIndex))
	{
		throw IndexOutOfRange();
	}
	else if(!check_isColHintIndexValid(colIndex, colHintIndex))
	{
		throw BoardHintIndexOutOfRange();
	}
	else
	{
		return colHint[colIndex][colHintIndex];
	}
}

int Board::get_rowHintSum(int rowIndex) const
{
	if(!check_isRowIndexValid(rowIndex))
	{
		throw IndexOutOfRange();
	}
	else
	{
		return rowHintSum[rowIndex];
	}
}

int Board::get_colHintSum(int colIndex) const
{
	if(!check_isColIndexValid(colIndex))
	{
		throw IndexOutOfRange();
	}
	else
	{
		return colHintSum[colIndex];
	}
}

int Board::get_numOfRowHint(int rowIndex) const
{
	if(!check_isRowIndexValid(rowIndex))
	{
		throw IndexOutOfRange();
	}
	else
	{
		return rowHint[rowIndex].size();
	}
}

int Board::get_numOfColHint(int colIndex) const
{
	if(!check_isColIndexValid(colIndex))
	{
		throw IndexOutOfRange();
	}
	else
	{
		return colHint[colIndex].size();
	}
}

pair<int,int> Board::get_boardSize() const
{
	return pair<int,int>(rowSize, colSize);
}

bool Board::check_isRowIndexValid(int rowIndex) const
{
	return rowIndex >= 0 && rowIndex < rowSize;
}

bool Board::check_isColIndexValid(int colIndex) const
{
	return colIndex >= 0 && colIndex < colSize; 
}

bool Board::check_isRowHintIndexValid(int rowIndex, int rowHintIndex) const
{
	return rowHintIndex >= 0 && rowHintIndex < rowHint[rowIndex].size();
}

bool Board::check_isColHintIndexValid(int colIndex, int colHintIndex) const
{
	return colHintIndex >= 0 && colHintIndex < colHint[colIndex].size();
}

