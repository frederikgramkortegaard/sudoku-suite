#pragma once
#include <fstream>
#include <string>
#include <iostream>
#include <filesystem>
#include <sstream>
#include <vector>
#include <map>

#include "sudoku.hpp"
#include "formats.hpp"

Sudoku *loadSudokuFromSDKFile(std::string filename)
{

    debug("Loading sudoku from SDK file: '%s'\n", filename.c_str());

    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Could not open file" << std::endl;
        return nullptr;
    }

    Sudoku *sudoku = new Sudoku(FormatType::SDK);

    sudoku->filename = filename;

    int rows_inserted = 0;
    for (std::string line; std::getline(file, line);)
    {

        if (line.at(0) == '#')
        {
            switch (line.at(1))
            {
            case 'A': // Author
                sudoku->sdk_data.author = line.substr(2);
                break;
            case 'D': // Description
                sudoku->sdk_data.description = line.substr(2);
                break;
            case 'C': // Comment
                sudoku->sdk_data.comment = line.substr(2);
                break;
            case 'P': // Date published
                sudoku->sdk_data.date_published = line.substr(2);
                break;
            case 'S': // Source
                sudoku->sdk_data.source = line.substr(2);
                break;
            default:
                break;
            }
        }
        else
        {
            // Parse the line
            for (int i = 0; i < 9; i++)
            {
                if (line.at(i) == '.')
                {
                    // Insert a 0
                    sudoku->board->cells[rows_inserted][i].value = 0;
                }
                else
                {
                    // Insert the value
                    sudoku->board->cells[rows_inserted][i].value = line.at(i) - '0';

                    // NOTE : We assume that all values in SDK files are fixed, meaning that a file always represents a puzzle, and not a save-state of a game.
                    sudoku->board->cells[rows_inserted][i].isFixed = true;
                }
            }

            rows_inserted++;
        }
    }

    return sudoku;
}

Sudoku *loadSudokuFromSDXFile(std::string filename)
{
    debug("Loading sudoku from SDX file: '%s'\n", filename.c_str());

    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Could not open file" << std::endl;
        return nullptr;
    }

    Sudoku *sudoku = new Sudoku(FormatType::SDX);

    sudoku->filename = filename;

    int rows_inserted = 0;
    std::string word;
    for (std::string line; std::getline(file, line);)
    {

        int col = 0;
        while (std::getline(file, word, ' '))
        {

            // if the word is a 1 digit number, then it's a cell value
            if (word.length() == 1 && std::isdigit(word.at(0)))
            {
                sudoku->board->cells[rows_inserted][col].value = std::stoi(word);
                sudoku->board->cells[rows_inserted][col].isFixed = true;
            }

            // if the word starts with a u and is followed by a 1 digit number, then it's a user value
            else if (word.at(0) == 'u' && word.length() == 2 && std::isdigit(word.at(1)))
            {
                sudoku->board->cells[rows_inserted][col].value = std::stoi(word.substr(1));
            }

            // otherwise it's just a word of non-separated digits which are the available candidates for said cell, in practice this means it's a 0
            else
            {
                sudoku->board->cells[rows_inserted][col].value = 0;
            }

            std::cout << word << std::endl;

            col++;
        }

        rows_inserted++;
    }

    return sudoku;
}

SDMPuzzleCollection loadPuzzleCollectionFromSDMFile(std::string filename)
{
    debug("Loading puzzle collection from SDM file: '%s'\n", filename.c_str());

    std::ifstream
        file(filename);

    if (!file.is_open())
    {
        std::cerr << "Could not open file" << std::endl;
        return {};
    }

    SDMPuzzleCollection collection = {};
    collection.filename = filename;

    collection.puzzles = std::vector<Sudoku *>();

    std::string line;
    while (std::getline(file, line))
    {
        Sudoku *sudoku = new Sudoku(FormatType::SDM);

        for (int i = 0; i < 81; i++)
        {
            int value;
            value = line.at(i) - '0';
            int row = i / 9;
            int col = i % 9;
            sudoku->board->cells[row][col].value = value;
            sudoku->board->cells[row][col].isFixed = value != 0;
        }

        debug("Loaded puzzle from SDM file\n");
        collection.puzzles.push_back(sudoku);
    }

    return collection;
}

SCLFile loadSCLFromSCLFile(std::string filename)
{
    debug("Loading SCL file: '%s'\n", filename.c_str());

    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Could not open file" << std::endl;
        return {};
    }

    SCLFile scl_file = {};

    std::string line;
    std::getline(file, line);
    scl_file.sudocue_rating_file_version = line;
    std::getline(file, line);
    scl_file.path_of_rated_file = line;

    while (std::getline(file, line))
    {
        SCLRating rating = {};
        std::string key;
        std::string word;
        int value;
        std::string seq_number;
        std::istringstream iss(line);

        // Get value before first =
        std::getline(iss, seq_number, '=');

        rating.sequence_number = seq_number;

        // Get all words, delimited by ';'
        while (std::getline(iss, word, ';'))
        {

            key = word.substr(0, word.find('='));
            value = std::stoi(word.substr(word.find('=') + 1));

            if (key == "R")
            {
                rating.R = value;
            }
            else if (key == "B")
            {
                rating.B = value;
            }
            else if (key == "S")
            {
                rating.S = value;
            }

            //@TODO : Not done yet, more to implement
        }
        scl_file.ratings.push_back(rating);
    }
    return scl_file;
}

Sudoku *loadSudokuFromSSFile(std::string filename)
{
    debug("Loading sudoku from SS file: '%s'\n", filename.c_str());

    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Could not open file" << std::endl;
        return nullptr;
    }

    Sudoku *sudoku = new Sudoku(FormatType::SS);

    sudoku->filename = filename;
    int rows_inserted = 0;
    std::string line;
    while (std::getline(file, line))
    {

        if (line.at(0) == '-')
        {
            continue;
        }

        int col = 0;
        for (char c : line)
        {
            if (c == '.')
            {
                sudoku->board->cells[rows_inserted][col].value = 0;
            }
            else if (c == '|')
            {
                continue;
            }
            else
            {
                sudoku->board->cells[rows_inserted][col].value = c - '0';
                sudoku->board->cells[rows_inserted][col].isFixed = true;
            }
            col++;
        }

        rows_inserted++;
    }

    return sudoku;
}

Sudoku *
loadSudokuFromFile(std::string filename)
{

    debug("Loading sudoku from file: '%s'\n", filename.c_str());

    std::filesystem::path path = filename;

    if (!std::filesystem::exists(path))
    {
        std::cerr << "File does not exist" << std::endl;
        return nullptr;
    }

    if (path.extension() == ".sdk")
    {
        return loadSudokuFromSDKFile(filename);
    }

    if (path.extension() == ".sdx")
    {
        return loadSudokuFromSDXFile(filename);
    }

    if (path.extension() == ".ss")
    {

        return loadSudokuFromSSFile(filename);
    }

    // Might be a common mistake, let's give a hint
    if (path.extension() == ".sdm")
    {
        debug("You're trying to load an SDM file as a single puzzle, and not as a puzzle collection. See --help for more information\n");
    }

    std::cerr << "Unsupported file format: '" << path.extension() << "'" << std::endl;

    return nullptr;
}
