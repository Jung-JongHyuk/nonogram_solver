#include "BoardViewer.h"

BoardViewer::BoardViewer() : BoardViewer(0,0) {}

BoardViewer::BoardViewer(int rowSize, int colSize)
{
    this->rowSize = rowSize;
    this->colSize = colSize;
}

void BoardViewer::print_board(Board& board)
{
    print_board(rowSize - 1, colSize - 1, board);
}

void BoardViewer::print_board(int rowIndex, int colIndex, Board& board)
{
    system("clear");
    for(int i = 0; i < rowIndex; i++)
    {
        for(int j = 0; j < colSize; j++)
        {
            if(board.get_board(i, j))
            {
                printf("%s", filledDotLetter.c_str());
            }
            else
            {
                printf("%s", blankDotLetter.c_str());
            }
        }
        
        printf("\n");
    }
    
    for(int i = 0; i <= colIndex; i++)
    {
        if(board.get_board(rowIndex, i))
        {
            printf("%s", filledDotLetter.c_str());
        }
        else
        {
            printf("%s", blankDotLetter.c_str());
        }
    }
    
    printf("\n");
}

void BoardViewer::print_confirmedDot(ConfirmedDotData& confirmedDotData)
{
    print_confirmedDot(rowSize - 1, colSize - 1, confirmedDotData);
}

void BoardViewer::print_confirmedDot(int rowIndex, int colIndex, ConfirmedDotData& confirmedDotData)
{
    system("clear");
    for(int i = 0; i < rowIndex; i++)
    {
        for(int j = 0; j < colSize; j++)
        {
            if(confirmedDotData.get_isSetConfirmed(i, j))
            {
                printf("%s", filledDotLetter.c_str());
            }
            else if(confirmedDotData.get_isBlankConfirmed(i, j))
            {
                printf("%s", blankDotLetter.c_str());
            }
            else
            {
                printf("%s", unknownDotLetter.c_str());
            }
        }
        
        printf("\n");
    }
    
    for(int i = 0; i <= colIndex; i++)
    {
        if(confirmedDotData.get_isSetConfirmed(rowIndex, i))
        {
            printf("%s", filledDotLetter.c_str());
        }
        else if(confirmedDotData.get_isBlankConfirmed(rowIndex, i))
        {
            printf("%s", blankDotLetter.c_str());
        }
        else
        {
            printf("%s", unknownDotLetter.c_str());
        }
    }
    
    printf("\n");
}
