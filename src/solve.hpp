/*
    Various techniques for solving Sudoku puzzles.
*/

#include "sudoku.hpp"
#include "board.hpp"
#include <concepts>
#include <vector>
#include <functional>

// Forward declare default solver
Board *backtracking(Board *board);

void solve(Board *board, std::function<Board *(Board *)> solver = backtracking)
{
    solver(board);
}

Board *copy_and_solve(Board *board, std::function<Board *(Board *)> solver)
{
    Board *copy = new Board();
    *copy = *board;
    return solver(copy);
}

bool hasSolution(Board *board, std::function<Board *(Board *)> solver = backtracking)
{
    Board *copy = new Board();
    *copy = *board;
    return solver(copy) != nullptr;
}

/*
    Backtracking algorithm for solving Sudoku puzzles.
    Returns a solved board if a solution exists, otherwise returns nullptr.
*/
Board *backtracking(Board *board)
{
    // Find the first empty cell
    int row = -1;
    int col = -1;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board->cells[i][j].value == 0)
            {
                row = i;
                col = j;
                break;
            }
        }
        if (row != -1)
        {
            break;
        }
    }

    // If there are no empty cells, the board is solved
    if (row == -1)
    {
        return board;
    }

    // Try all possible values for the empty cell
    for (int value = 1; value <= 9; value++)
    {
        board->cells[row][col].value = value;
        if (isBoardValid(board))
        {
            Board *result = backtracking(board);
            if (result != nullptr)
            {
                return result;
            }
        }
    }

    // If no value works, backtrack
    board->cells[row][col].value = 0;
    return nullptr;
}
