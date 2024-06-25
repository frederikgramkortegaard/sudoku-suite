/**/

#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <string>

#include "sudoku.hpp"
#include "loaders.hpp"
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
        std::cout << "  -f <filename>    Load a file" << std::endl;
        return 0;
    }

    std::string filename = argParser.getCmdOption("-f");
    if (filename.empty())
    {
        std::cerr << "No filename provided" << std::endl;
        return 1;
    }

    // SDMPuzzleCollection puzzles = loadPuzzleCollectionFromSDMFile(filename);
    // for (auto &puzzle : puzzles.puzzles)
    //{
    //     printSudoku(puzzle);
    // }

    SCLFile sclFile = loadSCLFromSCLFile(filename);
    std::cout << "Ratings version: " << sclFile.sudocue_rating_file_version << std::endl;
    std::cout << "Rated File: " << sclFile.path_of_rated_file << std::endl;
    for (auto &rating : sclFile.ratings)
    {
        std::cout << "R: " << rating.R << std::endl;
    }

    return 0;
}