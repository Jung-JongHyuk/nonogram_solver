#pragma once

#include <vector>
#include "Board.h"
using namespace std;

class ConfirmedDotData
{
	public:
		ConfirmedDotData();
		ConfirmedDotData(int rowSize, int colSize);
		
		//getter and setter
		bool get_isSetConfirmed(int rowIndex, int colIndex);
		bool get_isBlankConfirmed(int rowIndex, int colIndex);
		void set_isSetConfirmed(int rowIndex, int colIndex, bool value);
		void set_isBlankConfirmed(int rowIndex, int colIndex, bool value);
	
		//getter about number of confirmed dot
		int get_numOfUnconfirmedDotInRow(int rowIndex);
		int get_numOfUnconfirmedDotInCol(int colIndex);
		int get_numOfUnconfirmedDot() const;
		int get_numOfSetConfirmedDotInRow(int rowIndex);
		int get_numOfBlankConfirmedDotInRow(int rowIndex);
		int get_numOfSetConfirmedDotInCol(int colIndex);
		int get_numOfBlankConfirmedDotInCol(int colIndex);
		int get_numOfSetConfirmedDot() const;
		int get_numOfBlankConfirmedDot() const;
		
		bool is_confirmed(int rowIndex, int colIndex);
		bool get_isErrorDetected() const;
	
	private:
		bool check_isIndexOutOfRange(int rowIndex, int colIndex) const;
	
		int rowSize, colSize;
		vector<vector<bool>> isSetConfirmed, isBlankConfirmed;
		vector<int> numOfUnconfirmedDotInRow, numOfUnconfirmedDotInCol, numOfSetConfirmedDotInRow, numOfBlankConfirmedDotInRow, numOfSetConfirmedDotInCol, numOfBlankConfirmedDotInCol;
		int numOfUnconfirmedDot, numOfSetConfirmedDot, numOfBlankConfirmedDot;
		bool isErrorDetected;
};

class ConfirmedDotDataIndexOutOfRange {};


