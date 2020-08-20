#pragma once

#include <iostream>
#include "data_structure/Board.hpp"
#include "data_structure/ConfirmedDotData.hpp"
#include "RuleChecker.hpp"
#include "DotConfirmEngine.hpp"
#include "BoardViewer.hpp"
using namespace std;

class PuzzleSolver
{
	public:
		PuzzleSolver();
		PuzzleSolver(int rowSize, int colSize);
	
		bool solve_puzzle(Board& board);
	
	private:
		void solve_puzzle(int indexCount, int rowHintIndexToApply, Board& board, bool& isSolved); //recursion function of solve_puzzle
		int set_block(int rowIndex, int colIndex, int blockSize, Board& board) const; //set blockSize row block form (rowIndex, colIndex) and return colIndex which dot value is finialy set
		void adopt_heuristicTechnique(int rowIndex, int startColIndex, int endColIndex, int& unconfirmedLowestIndexCount, int currentIndexCount, Board& board);
		bool adopt_absurdityTechnique(int rowIndex, int startColIndex, int endColIndex, Board& board);
		int find_unconfirmedLowestIndexCount(int currentIndexCount);

		//transform function between indexCount and index
		pair<int,int> get_index(int indexCount) const;
		int get_indexCount(int rowIndex, int colIndex) const;
		
		int rowSize, colSize;
		RuleChecker ruleChecker;
		ConfirmedDotData confirmedDotData;
		DotConfirmEngine dotConfirmEngine;
};

//PuzzleSolver class

PuzzleSolver::PuzzleSolver() : PuzzleSolver(0,0) {}

PuzzleSolver::PuzzleSolver(int rowSize, int colSize)
{
	this->rowSize = rowSize;
	this->colSize = colSize;
	ruleChecker = RuleChecker(rowSize, colSize);
	confirmedDotData = ConfirmedDotData(rowSize, colSize);
	dotConfirmEngine = DotConfirmEngine(rowSize, colSize);
}

bool PuzzleSolver::solve_puzzle(Board& board)
{
	bool isSolved = false;
	dotConfirmEngine.confirm_dot(board, confirmedDotData, ruleChecker);
	solve_puzzle(0, 0, board, isSolved);
	return isSolved;
}

void PuzzleSolver::solve_puzzle(int indexCount, int rowHintIndexToApply, Board& board, bool& isSolved)
{
	pair<int,int> currentIndex = get_index(indexCount);
	int rowIndex = currentIndex.first, colIndex = currentIndex.second;
	static int calculateCount = 0;
	static int unconfirmedLowestIndexCount = find_unconfirmedLowestIndexCount(-1);
	
	if(calculateCount % 10000 == 0 && calculateCount != 0)
	{
		BoardViewer(rowSize, colSize).print_board(rowIndex, colIndex, board);
		cout << calculateCount << endl;
	}
	
	if(isSolved)
	{
		return;
	}
	else if(rowIndex >= rowSize) //if function reached out of board range without error, puzzle is solved
	{
		isSolved = true;
		return;
	}
	else if(rowHintIndexToApply >= board.get_numOfRowHint(rowIndex)) //if there is no remain row block
	{
		for(int i = colIndex; i < colSize; i++)
		{
			board.set_board(rowIndex, i, false); //set remain col space blank
		}
		
		if(ruleChecker.check_validity(rowIndex, colIndex, colSize - 1, board, confirmedDotData).first) //check validity
		{
			calculateCount++;
			ruleChecker.set_value(rowIndex, colIndex, colSize - 1, board);
			adopt_heuristicTechnique(rowIndex, colIndex, colSize - 1, unconfirmedLowestIndexCount, indexCount, board);
			solve_puzzle(get_indexCount(rowIndex + 1, 0), 0, board, isSolved); //recursion to next rowLine
		}
	}
	else
	{
		int blockSize = board.get_rowHint(rowIndex, rowHintIndexToApply);
		
		if(!ruleChecker.is_remainRowSpaceSufficient(rowIndex, colIndex, rowHintIndexToApply, board))
		{
			return; //finish current function if there is no more place to set block
		}
		
		int endColIndex = set_block(rowIndex, colIndex, blockSize, board); //set row block starting from current position
		pair<bool,int> checkResult = ruleChecker.check_validity(rowIndex, colIndex, endColIndex, board, confirmedDotData);
		
		if(checkResult.first) //if current block is valid in current position
		{
			calculateCount++;
			ruleChecker.set_value(rowIndex, colIndex, endColIndex, board);
			int nextIndexCount = get_indexCount(rowIndex, endColIndex) + 1;
			
			if(get_index(nextIndexCount).first != rowIndex) //if next recursion index is next rowLine
			{
				solve_puzzle(nextIndexCount, 0, board, isSolved); //initialize hintIndexToApply
			}
			else
			{
				solve_puzzle(get_indexCount(rowIndex, endColIndex) + 1, rowHintIndexToApply + 1, board, isSolved);
			}
			
			if(isSolved)
			{
				return;
			}
		
			board.set_board(rowIndex, colIndex, false); //set current dot blank
		
			if(ruleChecker.check_validity(rowIndex, colIndex, colIndex, board, confirmedDotData).first)
			{
				if(get_index(indexCount + 1).first == rowIndex)
				{
					calculateCount++;
					ruleChecker.set_value(rowIndex, colIndex, colIndex, board);
					adopt_heuristicTechnique(rowIndex, colIndex, colIndex, unconfirmedLowestIndexCount, indexCount, board);
					solve_puzzle(indexCount + 1, rowHintIndexToApply, board, isSolved);
				}
			}
		}
		else if(checkResult.second < colSize)
		{
			for(int i = colIndex; i < checkResult.second; i++)
			{
				board.set_board(rowIndex, i, false);
			}
			
			if(ruleChecker.check_validity(rowIndex, colIndex, checkResult.second - 1, board, confirmedDotData).first)
			{
				calculateCount++;
				ruleChecker.set_value(rowIndex, colIndex, checkResult.second - 1, board);
				adopt_heuristicTechnique(rowIndex, colIndex, checkResult.second - 1, unconfirmedLowestIndexCount, indexCount, board);
				solve_puzzle(get_indexCount(rowIndex, checkResult.second), rowHintIndexToApply, board, isSolved);
			}
		}
	}
}

int PuzzleSolver::set_block(int rowIndex, int colIndex, int blockSize, Board& board) const
{
	for(int i = 0; i < blockSize; i++)
	{
		board.set_board(rowIndex, colIndex + i, true);
	}
	
	if(colIndex + blockSize < colSize) //if next of block end exist
	{
		board.set_board(rowIndex, colIndex + blockSize, false); //set dot next of block end dot value blank 
		return colIndex + blockSize;
	}
	else
	{
		return colIndex + blockSize - 1;
	}
}

void PuzzleSolver::adopt_heuristicTechnique(int rowIndex, int startColIndex, int endColIndex, int& unconfirmedLowestIndexCount, int currentIndexCount, Board& board)
{
	if(unconfirmedLowestIndexCount == currentIndexCount)
	{
		for(int i = startColIndex; i <= endColIndex; i++)
		{
			if(board.get_board(rowIndex, i))
			{
				confirmedDotData.set_isSetConfirmed(rowIndex, i, true);
			}
			else
			{
				confirmedDotData.set_isBlankConfirmed(rowIndex, i, true);
			}
		}
		
		dotConfirmEngine.adopt_heuristicTechnique(rowIndex, startColIndex, endColIndex, board, confirmedDotData);
		unconfirmedLowestIndexCount = find_unconfirmedLowestIndexCount(unconfirmedLowestIndexCount);
	}
}

bool PuzzleSolver::adopt_absurdityTechnique(int rowIndex, int startColIndex, int endColIndex, Board& board)
{
	ConfirmedDotData backUp = confirmedDotData;
	
	for(int i = startColIndex; i <= endColIndex; i++)
	{
		if(board.get_board(rowIndex, i))
		{
			confirmedDotData.set_isSetConfirmed(rowIndex, i, true);
		}
		else
		{
			confirmedDotData.set_isBlankConfirmed(rowIndex, i, true);
		}
	}
	cout << rowIndex << " " << startColIndex << " " << endColIndex << endl;
	if(dotConfirmEngine.adopt_absurdityTechnique(rowIndex, startColIndex, endColIndex, board, confirmedDotData))
	{
		return true;
	}
	else
	{
		confirmedDotData = backUp;
		return false;
	}
}

int PuzzleSolver::find_unconfirmedLowestIndexCount(int currentIndexCount)
{
	for(int i = currentIndexCount + 1; i < rowSize * colSize; i++)
	{
		pair<int,int> currentIndex = get_index(i);
		
		if(!confirmedDotData.is_confirmed(currentIndex.first, currentIndex.second))
		{
			return i;
		}
	}
	
	return rowSize * colSize;
}

pair<int,int> PuzzleSolver::get_index(int indexCount) const
{
	return pair<int,int>(indexCount / colSize, indexCount % colSize);
}

int PuzzleSolver::get_indexCount(int rowIndex, int colIndex) const
{
	return rowIndex * colSize + colIndex;
}

