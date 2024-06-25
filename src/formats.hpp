/*
    https://www.sudocue.net/fileformats.php
*/

#pragma once

#include <string>
#include <vector>
#include <map>
#include "sudoku.hpp"

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
    std::string sequence_number;
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