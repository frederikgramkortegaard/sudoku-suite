
#pragma once
#include "sudoku.hpp"
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>

struct Cell
{
    int value;
    bool isFixed;

    Cell() : value(0), isFixed(false) {}
};

class Board
{
public:
    Cell cells[9][9];
    Board()
    {
        for (int i = 0; i < 81; i++)
        {
            int row = i / 9;
            int col = i % 9;
            cells[row][col].value = 0;
            cells[row][col].isFixed = false;
        }
    }
    const bool &operator==(const Board &other)
    {
        for (int i = 0; i < 81; i++)
        {
            int row = i / 9;
            int col = i % 9;
            if (cells[row][col].value != other.cells[row][col].value)
            {
                return false;
            }
        }
        return true;
    }

    Cell &operator[](int index)
    {
        int row = index / 9;
        int col = index % 9;
        return cells[row][col];
    }

    Board &operator=(const Board &other)
    {
        for (int i = 0; i < 81; i++)
        {
            int row = i / 9;
            int col = i % 9;
            cells[row][col] = other.cells[row][col];
        }
        return *this;
    }
    ~Board() {}

    std::string toString() const
    {
        std::string board_string;
        for (int i = 0; i < 81; i++)
        {
            int row = i / 9;
            int col = i % 9;
            board_string += std::to_string(cells[row][col].value);
        }
        return board_string;
    }
};

bool isBoardValid(const Board *board)
{
    // Check rows
    for (int i = 0; i < 9; i++)
    {
        bool seen[10] = {false};
        for (int j = 0; j < 9; j++)
        {
            int value = board->cells[i][j].value;
            if (value == 0)
            {
                continue;
            }
            if (seen[value])
            {
                return false;
            }
            seen[value] = true;
        }
    }

    // Check columns
    for (int i = 0; i < 9; i++)
    {
        bool seen[10] = {false};
        for (int j = 0; j < 9; j++)
        {
            int value = board->cells[j][i].value;
            if (value == 0)
            {
                continue;
            }
            if (seen[value])
            {
                return false;
            }
            seen[value] = true;
        }
    }

    // Check squares
    for (int i = 0; i < 9; i += 3)
    {
        for (int j = 0; j < 9; j += 3)
        {
            bool seen[10] = {false};
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    int value = board->cells[i + k][j + l].value;
                    if (value == 0)
                    {
                        continue;
                    }
                    if (seen[value])
                    {
                        return false;
                    }
                    seen[value] = true;
                }
            }
        }
    }

    return true;
}
bool isBoardSolved(const Board *board)
{
    if (!isBoardValid(board))
    {
        return false;
    }

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board->cells[i][j].value == 0)
            {
                return false;
            }
        }
    }

    return true;
}