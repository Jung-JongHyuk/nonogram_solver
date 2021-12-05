#pragma once

#include <vector>
#include "Board.h"
using namespace std;

class BlockRangeData
{
	public:
		BlockRangeData();
		BlockRangeData(int rowSize, int colSize);
	
		void set_blockRange(Board& board);
	
		//getter and setter
		pair<int,int> get_rowBlockRange(int rowIndex, int rowBlockIndex);
		pair<int,int> get_colBlockRange(int colIndex, int colBlockIndex);
		void set_rowBlockRange(int rowIndex, int rowBlockIndex, pair<int,int> blockRange);
		void set_colBlockRange(int colIndex, int colBlockIndex, pair<int,int> blockRange);
	
		bool get_isErrorDetected() const;
	
	private:
		bool check_isIndexOutOfRange(int rowIndex, int colIndex) const;
		bool check_isRowBlockIndexInvalid(int rowIndex, int blockIndex) const;
		bool check_isColBlockIndexInvalid(int colIndex, int blockIndex) const;
		bool check_isRowBlockRangeInvalid(int startIndex, int endIndex) const;
		bool check_isColBlockRangeInvalid(int startIndex, int endIndex) const;
	
		int rowSize, colSize;
		bool isErrorDetected;
		vector<vector<pair<int,int>>> rowBlockRange, colBlockRange;
};

class BlockRangeDataIndexOutOfRange {};
class BlockRangeInvalid {};

	
