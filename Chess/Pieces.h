/*
Author: Sikai Zhao
Class: ECE 6122
Last date modified: 11/18/2019
Description:
 1. Define class of Pieces
 2. Store the team, type information and used status of each piece
 3. Draw the six kinds of enhanced or non-enhanced pieces
*/

#ifndef Pieces_h
#define Pieces_h
#include <stdio.h>
#include <iostream>

/*
 * Class name: Pieces
 * Summary:
    1. Draw the six kinds of enhanced or non-enhanced pieces
    2. Store the team, type information and used status of each piece
 */
class Pieces
{
    public:
        int type = 0;               // Type of piece, initially 0
        bool used = false;          // Flag of used
        bool team = false;          // Team of piece. initially false
    
    public:
        void teamColor();           // Set the color of team
        void drawNormal();          // Draw non-enhanced pieces
        void drawEnhanced();        // Draw enhanced pieces
    
        void drawPawn();
        void drawRook();
        void drawKnight();
        void drawBishop();
        void drawQueen();
        void drawKing();            // Draw the six kinds of pieces
    
        void drawEnhancedPawn();
        void drawEnhancedRook();
        void drawEnhancedKnight();
        void drawEnhancedBishop();
        void drawEnhancedQueen();
        void drawEnhancedKing();    // Draw the six kinds of enhanced pieces
    
        void drawEnhancedObj(std::string addrstr);  //Function to help import .obj files to draw enhanced pieces (source: http://www.gimoo.net/t/1506/556e7bc1e744b.html)
};

#endif
