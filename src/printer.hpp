#include <iostream>
#include "board.hpp"

void printBoard(Board *board)
{
    for (int i = 0; i < 9; i++)
    {
        if (i % 3 == 0)
        {
            std::cout << "-------------------------" << std::endl;
        }
        for (int j = 0; j < 9; j++)
        {
            if (j % 3 == 0)
            {
                std::cout << "| ";
            }
            if (board->cells[i][j].value == 0)
            {
                std::cout << ". ";
            }
            else
            {
                std::cout << board->cells[i][j].value << " ";
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "-------------------------" << std::endl;
}

void printSudoku(Sudoku *sudoku)
{

    // Print the metadata
    std::cout << "Filename: " << sudoku->filename << std::endl;
    std::cout << "Format: " << FormatTypeStrings[sudoku->format] << std::endl;

    std::cout << "Mistakes: " << sudoku->mistakes << std::endl;

    // Format dependent metadata
    if (sudoku->format == FormatType::SDK)
    {
        std::cout << "Author: " << sudoku->author << std::endl;
        std::cout << "Description: " << sudoku->description << std::endl;
        std::cout << "Comment: " << sudoku->comment << std::endl;
        std::cout << "Date Published: " << sudoku->date_published << std::endl;
        std::cout << "Source: " << sudoku->source << std::endl;
    }

    printBoard(sudoku->board);
}