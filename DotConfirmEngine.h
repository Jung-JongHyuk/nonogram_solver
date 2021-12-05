#pragma once

#include <vector>
#include "data_structure/Board.h"
#include "data_structure/ConfirmedDotData.h"
#include "data_structure/BlockRangeData.h"
#include "technique/HeuristicTechnique.h"
#include "technique/AbsurdityTechnique.h"
#include "RuleChecker.h"
#include "BoardViewer.h"
using namespace std;

class DotConfirmEngine
{
	public:
		DotConfirmEngine();
		DotConfirmEngine(int rowSize, int colSize);
	
		void confirm_dot(Board& board, ConfirmedDotData& confirmedDotData, RuleChecker& ruleChecker);
		void adopt_heuristicTechnique(int rowIndex, int startColIndex, int endColIndex, Board& board, ConfirmedDotData& confirmedDotData);
		bool adopt_absurdityTechnique(int rowIndex, int startColIndex, int endColIndex, Board& board, ConfirmedDotData& confirmedDotData);
		
	private:
		int rowSize, colSize;
		BlockRangeData blockRangeData;
		HeuristicTechnique heuristicTechnique;
		AbsurdityTechnique absurdityTechnique;
};
