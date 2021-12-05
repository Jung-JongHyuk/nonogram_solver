#pragma once

#include <vector>
#include <algorithm>
#include <thread>
#include <mutex>
#include "../data_structure/Board.h"
#include "../data_structure/ConfirmedDotData.h"
#include "../data_structure/BlockRangeData.h"
#include "HeuristicTechnique.h"
using namespace std;

class AbsurdityTechnique
{
	public:
		AbsurdityTechnique();
		AbsurdityTechnique(int rowSize, int colSize);
	
		void adopt_absurdityTechnique(Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData, HeuristicTechnique& heuristicTechnique);
		bool adopt_absurdityTechnique(int rowIndex, int startColIndex, int endColIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData, HeuristicTechnique& heuristicTechnique);
	
	private:
		void set_techniqueAdoptionPriorityArray(ConfirmedDotData& confirmedDotData);
		bool get_numOfadjacentConfirmedDot(int rowIndex, int colIndex, ConfirmedDotData& confirmedDotData);
		bool check_isAssumptionValid(pair<int,int> assumptionIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData, HeuristicTechnique& heuristicTechnique);
		bool check_isAssumptionValid(int assumptionRowIndex, int assumptionColStartIndex, int assumptionColEndIndex, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData, HeuristicTechnique& heuristicTechnique);
	
        friend void absurdityCheckWorker(AbsurdityTechnique* delegate, pair<int,int> index, Board& board, ConfirmedDotData& confirmedDotData, BlockRangeData& blockRangeData, HeuristicTechnique& heuristicTechnique, mutex& confirmedDotDataLock);
		int rowSize, colSize;
		vector<pair<pair<int,int>,int>> techniqueAdoptionPriorityArray; // first : index pair, second :num of adjacent confirmeddot
};

