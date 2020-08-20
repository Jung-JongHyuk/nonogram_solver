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

//HeuristicCheckerAdoptionResult class

HeuristicCheckerAdoptionResult::HeuristicCheckerAdoptionResult() : HeuristicCheckerAdoptionResult(0,0) {}

HeuristicCheckerAdoptionResult::HeuristicCheckerAdoptionResult(int rowSize, int colSize)
{
	this->rowSize = rowSize;
	this->colSize = colSize;
	isConfirmedByRowTechnique.resize(rowSize);
	isConfirmedByColTechnique.resize(rowSize);
	isRowBlockRangeChanged.resize(rowSize, false);
	isColBlockRangeChanged.resize(colSize, false);
	
	for(int i = 0; i < rowSize; i++)
	{
		isConfirmedByRowTechnique[i].resize(colSize, false);
		isConfirmedByColTechnique[i].resize(colSize, false);
	}
}

bool HeuristicCheckerAdoptionResult::get_isConfirmedByRowTechnique(int rowIndex, int colIndex) const
{
	return isConfirmedByRowTechnique[rowIndex][colIndex];
}

bool HeuristicCheckerAdoptionResult::get_isConfirmedByColTechnique(int rowIndex, int colIndex) const
{
	return isConfirmedByColTechnique[rowIndex][colIndex];
}

void HeuristicCheckerAdoptionResult::set_isConfirmedByRowTechnique(int rowIndex, int colIndex, bool value)
{
	isConfirmedByRowTechnique[rowIndex][colIndex] = value;
}

void HeuristicCheckerAdoptionResult::set_isConfirmedByColTechnique(int rowIndex, int colIndex, bool value)
{
	isConfirmedByColTechnique[rowIndex][colIndex] = value;
}

bool HeuristicCheckerAdoptionResult::get_isRowBlockRangeChanged(int rowIndex) const
{
	return isRowBlockRangeChanged[rowIndex];
}

bool HeuristicCheckerAdoptionResult::get_isColBlockRangeChanged(int colIndex) const
{
	return isColBlockRangeChanged[colIndex];
}

void HeuristicCheckerAdoptionResult::set_isRowBlockRangeChanged(int rowIndex, bool value)
{
	isRowBlockRangeChanged[rowIndex] = value;
}

void HeuristicCheckerAdoptionResult::set_isColBlockRangeChanged(int colIndex, bool value)
{
	isColBlockRangeChanged[colIndex] = value;
}

