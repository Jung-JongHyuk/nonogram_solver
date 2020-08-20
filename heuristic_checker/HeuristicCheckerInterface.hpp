#pragma once

#include <vector>
#include <string>
#include "../data_structure/Board.hpp"
#include "../data_structure/ConfirmedDotData.hpp"
#include "../data_structure/BlockRangeData.hpp"
#include "../data_structure/HeuristicCheckerAdoptionResult.hpp"
#include "../data_structure/CheckerInfo.hpp"
using namespace std;

class HeuristicCheckerInterface
{
	public:
		HeuristicCheckerInterface();
		HeuristicCheckerInterface(int rowSize, int colSize);
		virtual ~HeuristicCheckerInterface() {};
	
		virtual HeuristicCheckerInterface& operator=(const HeuristicCheckerInterface& heuristicCheckerInterface);
	
		//use heuristic method. each method is implemented in child technique class
		virtual void adopt_techniqueInRow(int rowIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData) = 0;
		virtual void adopt_techniqueInCol(int colIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData) = 0;
		
		//getter and setter
		bool get_isUpdateNeeded() const;
		bool get_isRowUpdateNeeded(int rowIndex) const;
		bool get_isColUpdateNeeded(int colIndex) const;
		void set_isUpdateNeeded(bool value);
		void set_isRowUpdateNeeded(int rowIndex, bool value);
		void set_isColUpdateNeeded(int colIndex, bool value);
		void clear_techniqueAdoptionResult();
		const HeuristicCheckerAdoptionResult& get_checkerAdoptionResult() const;
		const CheckerInfo& get_checkerInfo() const;
	
	protected:
		//confirm dot and update isUpdatedByTechnique data (isUpdatedIndex[updatedIndex])
		//confirm of dot in heuristic technique class is done by this function
		void confirm_set_inRowTechnique(int rowIndex, int colIndex, ConfirmedDotData& confirmedDotData);
		void confirm_blank_inRowTechnique(int rowIndex, int colIndex, ConfirmedDotData& confirmedDotData);
		void confirm_set_inColTechnique(int rowIndex, int colIndex, ConfirmedDotData& confirmedDotData);
		void confirm_blank_inColTechnique(int rowIndex, int colIndex, ConfirmedDotData& confirmedDotData);
		void change_rowBlockRange(int rowIndex, int blockIndex, pair<int,int> blockRange, BlockRangeData& blockRangeData);
		void change_colBlockRange(int colIndex, int blockIndex, pair<int,int> blockRange, BlockRangeData& blockRangeData);
		
		int rowSize, colSize;
		bool isUpdateNeeded;
		vector<bool> isRowUpdateNeeded, isColUpdateNeeded;
		HeuristicCheckerAdoptionResult heuristicCheckerAdoptionResult;
		CheckerInfo checkerInfo;
};

//HeuristicCheckerInterface class

HeuristicCheckerInterface::HeuristicCheckerInterface() : HeuristicCheckerInterface(0,0) {}

HeuristicCheckerInterface::HeuristicCheckerInterface(int rowSize, int colSize)
{
	this->rowSize = rowSize;
	this->colSize = colSize;
	isUpdateNeeded = true;
	isRowUpdateNeeded.resize(rowSize, true);
	isColUpdateNeeded.resize(colSize, true);
	heuristicCheckerAdoptionResult = HeuristicCheckerAdoptionResult(rowSize, colSize);
}

HeuristicCheckerInterface& HeuristicCheckerInterface::operator=(const HeuristicCheckerInterface& heuristicCheckerInterface)
{
	if(this != &heuristicCheckerInterface)
	{
		rowSize = heuristicCheckerInterface.rowSize;
		colSize = heuristicCheckerInterface.colSize;
		isRowUpdateNeeded = heuristicCheckerInterface.isRowUpdateNeeded;
		isColUpdateNeeded = heuristicCheckerInterface.isColUpdateNeeded;
		heuristicCheckerAdoptionResult = heuristicCheckerInterface.heuristicCheckerAdoptionResult;
		checkerInfo = heuristicCheckerInterface.checkerInfo;
	}
	
	return *this;
}

void HeuristicCheckerInterface::confirm_set_inRowTechnique(int rowIndex, int colIndex, ConfirmedDotData& confirmedDotData)
{
	if(!confirmedDotData.get_isSetConfirmed(rowIndex, colIndex))
	{
		confirmedDotData.set_isSetConfirmed(rowIndex, colIndex, true);
		
		if(!confirmedDotData.get_isErrorDetected())
		{
			heuristicCheckerAdoptionResult.set_isConfirmedByRowTechnique(rowIndex, colIndex, true);
		}
	}
}
		
void HeuristicCheckerInterface::confirm_blank_inRowTechnique(int rowIndex, int colIndex, ConfirmedDotData& confirmedDotData)
{	
	if(!confirmedDotData.get_isBlankConfirmed(rowIndex, colIndex))
	{
		confirmedDotData.set_isBlankConfirmed(rowIndex, colIndex, true);
		
		if(!confirmedDotData.get_isErrorDetected())
		{
			heuristicCheckerAdoptionResult.set_isConfirmedByRowTechnique(rowIndex, colIndex, true);
		}
	}
}
		
void HeuristicCheckerInterface::confirm_set_inColTechnique(int rowIndex, int colIndex, ConfirmedDotData& confirmedDotData)
{	
	if(!confirmedDotData.get_isSetConfirmed(rowIndex, colIndex))
	{
		confirmedDotData.set_isSetConfirmed(rowIndex, colIndex, true);
		
		if(!confirmedDotData.get_isErrorDetected())
		{
			heuristicCheckerAdoptionResult.set_isConfirmedByColTechnique(rowIndex, colIndex, true);
		}
	}
}
		
void HeuristicCheckerInterface::confirm_blank_inColTechnique(int rowIndex, int colIndex, ConfirmedDotData& confirmedDotData)
{
	if(!confirmedDotData.get_isBlankConfirmed(rowIndex, colIndex))
	{
		confirmedDotData.set_isBlankConfirmed(rowIndex, colIndex, true);
		
		if(!confirmedDotData.get_isErrorDetected())
		{
			heuristicCheckerAdoptionResult.set_isConfirmedByColTechnique(rowIndex, colIndex, true);
		}
	}
}

void HeuristicCheckerInterface::change_rowBlockRange(int rowIndex, int blockIndex, pair<int,int> blockRange, BlockRangeData& blockRangeData)
{	
	if(blockRangeData.get_rowBlockRange(rowIndex, blockIndex) != blockRange)
	{
		blockRangeData.set_rowBlockRange(rowIndex, blockIndex, blockRange);
		
		if(!blockRangeData.get_isErrorDetected())
		{
			heuristicCheckerAdoptionResult.set_isRowBlockRangeChanged(rowIndex, true);
		}
	}
}

void HeuristicCheckerInterface::change_colBlockRange(int colIndex, int blockIndex, pair<int,int> blockRange, BlockRangeData& blockRangeData)
{	
	if(blockRangeData.get_colBlockRange(colIndex, blockIndex) != blockRange)
	{
		blockRangeData.set_colBlockRange(colIndex, blockIndex, blockRange);
		
		if(!blockRangeData.get_isErrorDetected())
		{
			heuristicCheckerAdoptionResult.set_isColBlockRangeChanged(colIndex, true);
		}
	}
}

bool HeuristicCheckerInterface::get_isUpdateNeeded() const
{
	return isUpdateNeeded;
}

bool HeuristicCheckerInterface::get_isRowUpdateNeeded(int rowIndex) const
{
	return isRowUpdateNeeded[rowIndex];
}

bool HeuristicCheckerInterface::get_isColUpdateNeeded(int colIndex) const
{
	return isColUpdateNeeded[colIndex];
}

void HeuristicCheckerInterface::set_isUpdateNeeded(bool value)
{
	isUpdateNeeded = value;
}

void HeuristicCheckerInterface::set_isRowUpdateNeeded(int rowIndex, bool value)
{
	isRowUpdateNeeded[rowIndex] = value;
}

void HeuristicCheckerInterface::set_isColUpdateNeeded(int colIndex, bool value)
{
	isColUpdateNeeded[colIndex] = value;
}

void HeuristicCheckerInterface::clear_techniqueAdoptionResult()
{
	for(int i = 0; i < rowSize; i++)
	{
		for(int j = 0; j < colSize; j++)
		{
			heuristicCheckerAdoptionResult.set_isConfirmedByRowTechnique(i, j, false);
			heuristicCheckerAdoptionResult.set_isConfirmedByColTechnique(i, j, false);
		}
	}
	
	for(int i = 0; i < rowSize; i++)
	{
		heuristicCheckerAdoptionResult.set_isRowBlockRangeChanged(i, false);
	}
	
	for(int i = 0; i < colSize; i++)
	{
		heuristicCheckerAdoptionResult.set_isColBlockRangeChanged(i, false);
	}
}

const HeuristicCheckerAdoptionResult& HeuristicCheckerInterface::get_checkerAdoptionResult() const
{
	return heuristicCheckerAdoptionResult;
}

const CheckerInfo& HeuristicCheckerInterface::get_checkerInfo() const
{
	return checkerInfo;
}

