#pragma once

#include <vector>
using namespace std;

class HeuristicCheckerAdoptionResult
{
	public:
		HeuristicCheckerAdoptionResult();
		HeuristicCheckerAdoptionResult(int rowSize, int colSize);
		
		//getter and setter
		bool get_isConfirmedByRowTechnique(int rowIndex, int colIndex) const;
		bool get_isConfirmedByColTechnique(int rowIndex, int colIndex) const;
		void set_isConfirmedByRowTechnique(int rowIndex, int colIndex, bool value);
		void set_isConfirmedByColTechnique(int rowIndex, int colIndex, bool value);
		bool get_isRowBlockRangeChanged(int rowIndex) const;
		bool get_isColBlockRangeChanged(int colIndex) const;
		void set_isRowBlockRangeChanged(int rowIndex, bool value);
		void set_isColBlockRangeChanged(int colIndex, bool value);
	
	private:
		int rowSize, colSize;
		vector<vector<bool>> isConfirmedByRowTechnique, isConfirmedByColTechnique;
		vector<bool> isRowBlockRangeChanged, isColBlockRangeChanged;
};

