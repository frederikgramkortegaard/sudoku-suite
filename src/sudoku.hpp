#pragma once
#include "solve.hpp"
#include "board.hpp"
#include <iostream>
#include <fstream>
#include <time.h>
#include <ctime>
#include <cassert>
#include <filesystem> // C++17
#include <map>
#include "utils.hpp"

class Sudoku;
enum FormatType
{
    SDK,
    SDM,
    SDX,
    SCL,
    SS,
    UndefinedFormat
};

std::map<FormatType, std::string> FormatTypeStrings = {
    {SDK, "SDK"},
    {SDM, "SDM"},
    {SDX, "SDX"},
    {SCL, "SCL"},
    {SS, "SS"},
    {UndefinedFormat, "Undefined"}};

struct SCLRating
{
    int R;  // Number of solving rounds
    int B;  // Breath (not used in this version)
    int S;  // Rating score
    int I;  // Initial singles
    int FH; // Number of times the Full House technique is used.
    int D1; // Number of times the Last Digit technique is used.
    int M1; // Number of times the Mixed Single technique is used.
    int B1; // Number of times the Hidden Single in Box technique is used.
    int R1; // Number of times the Hidden Single in Row technique is used.
    int C1; // Number of times the Hidden Single in Column technique is used.
    int US; // Number of times the Unlocked Single technique is used.
    int N1; // Number of times the Naked Single technique is used.
    int LP; // Number of times the Locked Pair technique is used.
    int LT; // Number of times the Locked Triple technique is used.
    int L1; // Number of times the Locked Candidates 1 technique is used.
    int L2; // Number of times the Locked Candidates 2 technique is used.
    int N2; // Number of times the Naked Pair technique is used.
    int N3; // Number of times the Naked Triple technique is used.
    int N4; // Number of times the Naked Quad technique is used.
    int H2; // Number of times the Hidden Pair technique is used.
    int H3; // Number of times the Hidden Triple technique is used.
    int H4; // Number of times the Hidden Quad technique is used.
    int X2; // Number of times the X-Wing technique is used.
    int X3; // Number of times the Swordfish technique is used.
    int X4; // Number of times the Jellyfish technique is used.
    int Y2; // Number of times the XY-Wing technique is used.
    int Y3; // Number of times the XYZ-Wing technique is used.
    int AP; // Number of times the Aligned Pair technique is used.
    int RP; // Number of times the Remote Pair technique is used.
    int YC; // Number of times the XY-Chain technique is used.
    int F2; // Number of times the Finned X-Wing technique is used.
    int F3; // Number of times the Finned Swordfish technique is used.
    int F4; // Number of times the Finned Jellyfish technique is used.
    int S2; // Number of times the Sashimi X-Wing technique is used.
    int S3; // Number of times the Sashimi Swordfish technique is used.
    int S4; // Number of times the Sashimi Jellyfish technique is used.
    int CT; // Number of times the Color Trap technique is used.
    int CW; // Number of times the Color Wrap technique is used.
    int MC; // Number of times the Color Wing (MC) technique is used.
    int G1; // Number of times the BUG+1 technique is used.
    int MT; // Number of times the Medusa Trap technique is used.
    int MW; // Number of times the Medusa Wrap technique is used.
    int MB; // Number of times the Medusa Bridge technique is used.
    int MX; // Number of times the Medusa Complex technique is used.
    int U1; // Number of times the Unique Rectangle 1 technique is used.
    int U2; // Number of times the Unique Rectangle 2 technique is used.
    int U3; // Number of times the Unique Rectangle 3 technique is used.
    int U4; // Number of times the Unique Rectangle 4 technique is used.
    int ER; // Number of times the Empty Rectangle technique is used.
    int AL; // Number of times the Almost Locked Set technique is used.
    int NT; // Number of times the Nishio technique is used.
    int TC; // Number of times the Table Contradiction technique is used.
    int TV; // Number of times the Table Verity/Veracity technique is used.
    int BF; // Number of times Brute Force is used.
    int SR; // Surrender. When present, puzzle is unsolvable.
};

struct SCLFile
{

    std::string sudocue_rating_file_version;
    std::string path_of_rated_file;
    std::vector<SCLRating> ratings; // Each line in the SCL file is a rating
};

struct SDMPuzzleCollection
{
    std::string filename;
    std::vector<Sudoku *> puzzles;
    SCLFile scl_file; // If an SCL file exists rating this collection, we might as well be able to load it here
};

class Sudoku
{
public:
    Board *board;
    int mistakes;

    /*
        Here we store the diff of previous game states such as:
            1,1,7
        Which would indicate that setting
            board->cells[1][1] = 7
        Would revert the game state to its previous state
    */
    std::vector<std::tuple<int, int, int>> history;

    std::string filename;

    time_t start_time;
    time_t end_time;
    FormatType format;

    //@TODO : All of this should be inside a boost variant or something similar to act as a union of structs
    std::string author;
    std::string description;
    std::string comment;
    std::string date_published;
    std::string source;

    Sudoku()
    {
        board = new Board();
        mistakes = 0;
        start_time = time(0);
        end_time = time(0);
        format = UndefinedFormat;
    }

    Sudoku(FormatType format)
    {
        board = new Board();
        mistakes = 0;
        start_time = time(0);
        end_time = time(0);
        format = format;
    }

    ~Sudoku()
    {
        delete board;
    }
};

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
    //@TODO : We don't validate that the file is a valid SDK file, we should do that here
    for (std::string line; std::getline(file, line);)
    {

        if (line.at(0) == '#')
        {
            switch (line.at(1))
            {
            case 'A': // Author
                sudoku->author = line.substr(2);
                break;
            case 'D': // Description
                sudoku->description = line.substr(2);
                break;
            case 'C': // Comment
                sudoku->comment = line.substr(2);
                break;
            case 'P': // Date published
                sudoku->date_published = line.substr(2);
                break;
            case 'S': // Source
                sudoku->source = line.substr(2);
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

    err("Unsupported file format: '%s'\n", path.extension().c_str());

    return nullptr;
}
