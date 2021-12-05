#pragma once

#include <vector>
#include <string>
#include "../data_structure/Board.h"
#include "../data_structure/ConfirmedDotData.h"
#include "../data_structure/BlockRangeData.h"
#include "../data_structure/HeuristicCheckerAdoptionResult.h"
#include "../data_structure/CheckerInfo.h"
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

