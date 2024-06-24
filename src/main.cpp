/**/

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>

#include "sudoku.hpp"

#include "argparser.hpp"
#include "printer.hpp"

int main(int argc, char **argv)
{

    ArgParser argParser(argc, argv);

    if (argParser.cmdOptionExists("-h") || argParser.cmdOptionExists("--help"))
    {
        std::cout << "Usage: suite [options] [input-file]" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "  -h, --help    Show this help message and exit" << std::endl;
        return 0;
    }

    std::string filename = argParser.getCmdOption("-f");
    if (filename.empty())
    {
        std::cerr << "No filename provided" << std::endl;
        return 1;
    }

    // Sudoku *sudoku = loadSudokuFromFile(filename);
    // printSudoku(sudoku);

    SDMPuzzleCollection puzzles = loadPuzzleCollectionFromSDMFile(filename);
    for (auto &puzzle : puzzles.puzzles)
    {
        printSudoku(puzzle);
    }
    return 0;
}