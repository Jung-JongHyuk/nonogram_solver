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

