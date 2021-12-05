#pragma once

#include <vector>
#include "../RuleChecker.h"
#include "../BoardViewer.h"
#include "../data_structure/Board.h"
#include "../data_structure/ConfirmedDotData.h"
#include "../data_structure/BlockRangeData.h"
#include "../data_structure/CheckerInfo.h"
#include "../data_structure/HeuristicCheckerAdoptionResult.h"
#include "../heuristic_checker/HeuristicCheckerInterface.h"
#include "../heuristic_checker/IntersectionChecker.h"
#include "../heuristic_checker/MonoBlockRangeChecker.h"
#include "../heuristic_checker/MaxBlockSizeChecker.h"
#include "../heuristic_checker/BlockExpandableChecker.h"
#include "../heuristic_checker/ConfirmCompleteChecker.h"
#include "../heuristic_checker/BlockRangeOrderChecker.h"
#include "../heuristic_checker/BlockRangeIntervalChecker.h"
#include "../heuristic_checker/BlockRangeValidityChecker.h"
#include "../heuristic_checker/BlockSegmentIntervalChecker.h"
#include "../heuristic_checker/PotentialBlockSegmentChecker.h"
#include "../heuristic_checker/BlockRangeBorderChecker.h"
#include "../heuristic_checker/BlockRangeReductionChecker.h"
#include "../heuristic_checker/BlockSegmentMergeChecker.h"
using namespace std;

class HeuristicTechnique
{
	public:
		HeuristicTechnique();
		HeuristicTechnique(int rowSize, int colSize);
		~HeuristicTechnique();
	
		HeuristicTechnique& operator=(const HeuristicTechnique& heuristicTechnique);
	
		void adopt_heuristicTechnique(Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData);
		void adopt_heuristicTechnique(int rowIndex, int colStartIndex, int colEndIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData);
	
		void adopt_checker(int checkerIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData);
		void update_isUpdateNeeded(int rowIndex, int colIndex, ConfirmedDotData& confirmedDotData);
		int get_numOfChecker() const;
	
		bool is_heuristicTechniqueAvailable() const;
		void sync_confirmedDotData(ConfirmedDotData& confirmedDotData);
	
	private:
		void make_checkerArray();
		
		//update isUpdateNeeded member of each checker
		void update_isUpdateNeeded(int checkerIndex, ConfirmedDotData& confirmedDotData, const HeuristicCheckerAdoptionResult& heuristicCheckerAdoptionResult);
		void update_isUpdateNeeded(int currentCheckerIndex, int chekerIndexToUpdate, ConfirmedDotData& confirmedDotData, const HeuristicCheckerAdoptionResult& heuristicCheckerAdoptionResult);
	
		int rowSize, colSize;
		vector<HeuristicCheckerInterface*> checkerArray;
		ConfirmedDotData capturedConfirmedDotData;
};
