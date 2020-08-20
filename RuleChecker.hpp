#pragma once

#include <vector>
#include "data_structure/Board.hpp"
#include "data_structure/ConfirmedDotData.hpp"
using namespace std;

class RuleChecker
{
	public:
		RuleChecker();
		RuleChecker(int rowSize, int colSize);
	
		//rowRange validity check function
		//return value : validity and invalid col index
		pair<bool,int> check_validity(int rowIndex, int startColIndex, int endColIndex, Board& board, ConfirmedDotData& confirmedDotData) const;

		//remain space sufficient check function
		bool is_remainRowSpaceSufficient(int rowIndex, int colIndex, int rowHintIndexToApply, Board& board) const; //check row whether remain col space (rowIndex, colIndex~colSize - 1) is sufficient to fill remain row block starting from rowHintIndexToApply
		bool is_remainColSpaceSufficient(int rowIndex, int colIndex, int colHintIndexToApply, Board& board) const;
		//check col whether remain row space (rowIndex~rowSize - 1, colIndex) is sufficient to fill remain row block starting from colHintIndexToApply
	
		void set_value(int rowIndex, int startColIndex, int endColIndex, Board& board); //update memoization data using value of (rowIndex, startColIndex~endColIndex)
		
	private:
		//helper function used in check_validity
		pair<bool,int> check_row(int rowIndex, int startColIndex, int endColIndex, Board& board, ConfirmedDotData& confirmedDotData) const; //check row whether each dot value in (rowIndex, startColIndex~endcolIndex) satisfies confirmed dot value condition.
		pair<bool,int> check_column(int rowIndex, int startColIndex, int endColIndex, Board& board, ConfirmedDotData& confirmedDotData) const; //check col whether each dot value in (rowIndex, startColIndex~endColIndex) satisfies col hint condition

		bool check_column(int rowIndex, int colIndex, bool dotValue, int& colHintIndexToApply, int& appliedColBlockSize, Board& board, ConfirmedDotData& confirmedDotData) const; //helper function used in public check_column function
		int get_endRowIndexToCheckCol(int rowIndex, int colIndex, Board& board, ConfirmedDotData& confirmedDotData) const; //find col hint checkable row index starting from rowIndex in colIndex
	
		//setter and getter of memoization data
		int get_currentColHintIndexToApply(int rowIndex, int colIndex) const;
		int get_currentAppliedColBlockSize(int rowIndex, int colIndex) const;
		void set_currentColHintIndexToApply(int rowIndex, int colIndex, int value);
		void set_currentAppliedColBlockSize(int rowIndex, int colIndex, int value);

		vector<vector<int>> currentColHintIndexToApply, currentAppliedColBlockSize;
		int rowSize, colSize;
};

//RuleChecker class

RuleChecker::RuleChecker() : RuleChecker(0,0) {}

RuleChecker::RuleChecker(int rowSize, int colSize)
{
	this->rowSize = rowSize;
	this->colSize = colSize;
	currentColHintIndexToApply.resize(rowSize);
	currentAppliedColBlockSize.resize(rowSize);
	
	for(int i = 0; i < rowSize; i++)
	{
		currentColHintIndexToApply[i].resize(colSize);
		currentAppliedColBlockSize[i].resize(colSize);
	}
}

pair<bool,int> RuleChecker::check_validity(int rowIndex, int startColIndex, int endColIndex, Board& board, ConfirmedDotData& confirmedDotData) const
{
	pair<bool,int> rowCheckResult = check_row(rowIndex, startColIndex, endColIndex, board, confirmedDotData);
	
	if(!rowCheckResult.first)
	{
		return rowCheckResult;
	}
	else
	{
		pair<bool,int> colCheckResult = check_column(rowIndex, startColIndex, endColIndex, board, confirmedDotData);
		
		if(!colCheckResult.first)
		{
			return colCheckResult;
		}
		else
		{
			return pair<bool,int>(true, -1);
		}
	}
}

pair<bool,int> RuleChecker::check_row(int rowIndex, int startColIndex, int endColIndex, Board& board, ConfirmedDotData& confirmedDotData) const
{
	for(int i = startColIndex; i <= endColIndex; i++)
	{
		//if blank confirmed dot value is true 
		if(board.get_board(rowIndex, i) && confirmedDotData.get_isBlankConfirmed(rowIndex, i))
		{
			return pair<bool,int>(false, i + 1);
		}
		
		//if set confirmed dot value is false
		if(!board.get_board(rowIndex, i) && confirmedDotData.get_isSetConfirmed(rowIndex, i))
		{
			return pair<bool,int>(false, startColIndex + 1);
		}
	}
	
	return pair<bool,int>(true, -1);
}

pair<bool,int> RuleChecker::check_column(int rowIndex, int startColIndex, int endColIndex, Board& board, ConfirmedDotData& confirmedDotData) const
{
	for(int i = startColIndex; i <= endColIndex; i++)
	{
		//get col block placement info in previous row 
		int colHintIndexToApply = get_currentColHintIndexToApply(rowIndex - 1, i); 
		int appliedColBlockSize = get_currentAppliedColBlockSize(rowIndex - 1, i);
		int endRowIndex = get_endRowIndexToCheckCol(rowIndex, i, board, confirmedDotData);
		
		//check col hint validity of (rowIndex, i)
		if(!check_column(rowIndex, i, board.get_board(rowIndex, i), colHintIndexToApply, appliedColBlockSize, board, confirmedDotData))
		{
			if(board.get_board(rowIndex, i)) //if dot value is true and need to blank
			{		
				return pair<bool,int>(false, i + 1);
			}
			else
			{
				return pair<bool,int>(false, startColIndex + 1);
			}
		}
		
		//check col hint validity of (rowIndex + 1~endRowIndex, i)
		for(int j = rowIndex + 1; j <= endRowIndex; j++)
		{
			if(!check_column(j, i, confirmedDotData.get_isSetConfirmed(j, i), colHintIndexToApply, appliedColBlockSize, board, confirmedDotData))
			{
				if(board.get_board(rowIndex, i)) //if dot value is true and need to blank
				{		
					return pair<bool,int>(false, i + 1);
				}
				else
				{
					return pair<bool,int>(false, startColIndex + 1);
				}
			}
		}
	}
	
	return pair<bool,int>(true, -1);
}

bool RuleChecker::is_remainRowSpaceSufficient(int rowIndex, int colIndex, int rowHintIndexToApply, Board& board) const
{
	int remainDot = 0, numOfRowHint = board.get_numOfRowHint(rowIndex);
	
	for(int i = rowHintIndexToApply; i < numOfRowHint; i++)
	{
		remainDot += board.get_rowHint(rowIndex, i); //get remain dot to place
	}
	
	int requiredSize = remainDot + numOfRowHint - rowHintIndexToApply - 1; //get minimun size to place remain dot
	return colIndex + requiredSize <= colSize;
}

bool RuleChecker::is_remainColSpaceSufficient(int rowIndex, int colIndex, int colHintIndexToApply, Board& board) const
{
	int remainDot = 0, numOfColHint = board.get_numOfColHint(colIndex); //get remain dot to place
	
	for(int i = colHintIndexToApply; i < numOfColHint; i++)
	{
		remainDot += board.get_colHint(colIndex, i);
	}
	
	int requiredSize = remainDot + numOfColHint - colHintIndexToApply - 1; //get minimun size to place remain dot
	return rowIndex + requiredSize <= rowSize;
}

bool RuleChecker::check_column(int rowIndex, int colIndex, bool dotValue, int& colHintIndexToApply, int& appliedColBlockSize, Board& board, ConfirmedDotData& confirmedDotData) const
{	
	if(dotValue) //if current dot is set
	{
		if(appliedColBlockSize == 0) //if current dot is start of col block
		{
			if(colHintIndexToApply < board.get_numOfColHint(colIndex)) //check is col block to apply exist
			{
				appliedColBlockSize++; //if valid, update current applied col block size
				return true;
			}
			else
			{
				return false;
			}
		}
		else //if current dot is in col block
		{
			if(appliedColBlockSize + 1 <= board.get_colHint(colIndex, colHintIndexToApply)) //check col block length
			{
				appliedColBlockSize++; //if valid, update current applied col block size
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	else //if current dot is blank
	{
		if(appliedColBlockSize == 0) //if current dot is continous blank
		{
			return is_remainColSpaceSufficient(rowIndex + 1, colIndex, colHintIndexToApply, board); //check is remain col space sufficient
		}
		else //if current dot is first blank next to col block
		{
			if(appliedColBlockSize == board.get_colHint(colIndex, colHintIndexToApply)) //check ended col block length
			{
				appliedColBlockSize = 0; //if valid, update current applied col block size, block index to apply
				colHintIndexToApply++;
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}
		
int RuleChecker::get_endRowIndexToCheckCol(int rowIndex, int colIndex, Board& board, ConfirmedDotData& confirmedDotData) const
{
	for(int i = rowIndex + 1; i < rowSize; i++)
	{
		if(!confirmedDotData.is_confirmed(i, colIndex))
		{
			return i - 1;
		}
	}
	
	return rowSize - 1;
}

void RuleChecker::set_value(int rowIndex, int startColIndex, int endColIndex, Board& board)
{
	for(int i = startColIndex; i <= endColIndex; i++)
	{
		if(board.get_board(rowIndex, i)) //if current dot is set
		{
			set_currentColHintIndexToApply(rowIndex, i, get_currentColHintIndexToApply(rowIndex - 1, i));
			set_currentAppliedColBlockSize(rowIndex, i, get_currentAppliedColBlockSize(rowIndex - 1, i) + 1);
		}
		else if(get_currentAppliedColBlockSize(rowIndex - 1, i) != 0) //if current dot is continuous blank
		{
			set_currentColHintIndexToApply(rowIndex, i, get_currentColHintIndexToApply(rowIndex - 1, i) + 1);
			set_currentAppliedColBlockSize(rowIndex, i, 0);
		}
		else //if current dot is first blank next to col block
		{
			set_currentColHintIndexToApply(rowIndex, i, get_currentColHintIndexToApply(rowIndex - 1, i));
			set_currentAppliedColBlockSize(rowIndex, i, 0);
		}
	}
}

int RuleChecker::get_currentColHintIndexToApply(int rowIndex, int colIndex) const
{
	return rowIndex < 0 ? 0 : currentColHintIndexToApply[rowIndex][colIndex];
}

int RuleChecker::get_currentAppliedColBlockSize(int rowIndex, int colIndex) const
{
	return rowIndex < 0 ? 0 : currentAppliedColBlockSize[rowIndex][colIndex];
}

void RuleChecker::set_currentColHintIndexToApply(int rowIndex, int colIndex, int value)
{
	currentColHintIndexToApply[rowIndex][colIndex] = value;
}

void RuleChecker::set_currentAppliedColBlockSize(int rowIndex, int colIndex, int value)
{
	currentAppliedColBlockSize[rowIndex][colIndex] = value;
}

