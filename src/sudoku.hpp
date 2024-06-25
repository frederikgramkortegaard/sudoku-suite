/*
    Definition of the Sudoku class, which is the main class that holds the game state and metadata of a Sudoku game.
*/

#pragma once

#include "board.hpp"
#include "utils.hpp"
#include "formats.hpp"

#include <iostream>
#include <fstream>
#include <time.h>
#include <ctime>
#include <cassert>
#include <filesystem> // C++17
#include <map>

class Sudoku
{
public:
    Board *board = nullptr;

    /* Some platforms have a limit on the number of mistakes a user can make before the game is over. */
    int mistakes = 0;
    int max_mistakes = 0;

    /*
        Here we store the diff of previous game states such as:
            1,1,7
        Which would indicate that setting
            board->cells[1][1] = 7
        Would revert the game state to its previous state
    */
    std::vector<std::tuple<int, int, int>> history = {};

    /* Metadata */
    std::string filename;
    time_t start_time;
    time_t end_time;
    bool is_solved = false; // Avoid having to recompute this every time

    FormatType format;

    /* Format-dependent metadata */
    //@TODO : We'd like for this not always to be loaded, but in C++ you can't have std::string's inside of Unions, meaning that if we wanted a Union of struct's for each type of format, we'd have to use e.g. boost::variant or std::variant but it doesn't work quite as neatly.
    struct
    {
        std::string author;
        std::string description;
        std::string comment;
        std::string date_published;
        std::string source;

    } sdk_data;

    Sudoku()
    {
        Sudoku(FormatType::UndefinedFormat);
    }

    Sudoku(FormatType format)
    {
        board = new Board();
        format = format;
    }

    ~Sudoku()
    {
        delete board;
    }
};
