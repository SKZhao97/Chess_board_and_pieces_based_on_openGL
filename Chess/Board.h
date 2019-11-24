/*
Author: Sikai Zhao
Class: ECE 6122
Last date modified: 11/18/2019
Description:
 1. Defineg the class Board
 2. Draw chess board and start to draw chess pieces(enhanced and unenhanced)
 3. Store the pieces on each square of the board
*/

#ifndef Board_h
#define Board_h

#include <stdio.h>
#include "Pieces.h"
#include <array>


/*
 Class name: Board
 Summary:
    1. Draw and initial the board
    2. Store the type of piece on each square of the board and its team and used flag
    3. Implement the movements and call drawing functions
*/
class Board{
    
    public:
        const double squareLen = 1;         // Length of each square of chess board
        static const int boardRow = 8;      // The number of rows of the board
        static const int boardCol = 8;      // The number of columns of the board
        std::array<std::array<Pieces, boardCol>, boardRow> status;  // 2D array to store the information of the pieces on each aquare of the board
    public:
        Board();                            // Constructor to initialize the board
        int randomGenerator();              // Random number generator
        void drawSquare();                  // Function to draw square
        void drawBoard();                   // Function to draw chess board
        void drawNormalPieces();            // Function to draw pieces
        void drawEnhancedPieces();          // Function to draw enhanced pieces
        void pawnMovement();                // Function to deal with pawn movement
        void knightMovement();              // Function to deal with knight movement
        bool pieceTested(std::array<std::array<int, 2>, 16> arr, int x, int y, int num);
        // Check if the piece has been tested to move
};

#endif
