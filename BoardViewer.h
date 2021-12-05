#pragma once

#include <cstdio>
#include <string>
#include "data_structure/Board.h"
#include "data_structure/ConfirmedDotData.h"
using namespace std;

class BoardViewer
{
    public:
        BoardViewer();
        BoardViewer(int rowSize, int colSize);
    
        void print_board(Board& board);
        void print_board(int rowIndex, int colIndex, Board& board);
        void print_confirmedDot(ConfirmedDotData& confirmedDotData);
        void print_confirmedDot(int rowIndex, int colIndex, ConfirmedDotData& confirmedDotData);
    
    private:
        int rowSize, colSize;
        const string filledDotLetter = "🟩";
        const string blankDotLetter = "⬛️";
        const string unknownDotLetter = "⬜️";
};


