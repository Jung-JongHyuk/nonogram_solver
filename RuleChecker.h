#pragma once

#include <vector>
#include "data_structure/Board.h"
#include "data_structure/ConfirmedDotData.h"
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
