/*
Author: Sikai Zhao
Class: ECE 6122
Last date modified: 11/22/2019
Description:  1. Draw chess board and start to draw chess pieces(enhanced and unenhanced)
              2. Store the pieces on each square of the board
*/

#include <iostream>
#include <array>                           // To use std::array
#include "Board.h"

#ifdef __APPLE__                           // To use glut on macOS
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else                                      // To use glut on Pace-ice
#include <GL/gl.h>
#include <GL/glut.h>
#endif

/*
* Function name: Board
* Summary: Constructor of the board class, initiate the board and set the type and team of each square
* Parameters: N/A
* Return: N/A
*/
Board::Board()
{
    bool team = true;                        // Boolean variable to store the team information
    for(int i = 0; i < Board::boardRow; i++)
    {
        if(i > 3)
        {
            team = false;                    // Set team to true after finishing setting the first team
        }
        for(int j = 0; j < Board::boardCol; j++)
        {
            if(i == 1 || i == 6)
            {
                status[i][j].type = 1;        // Store the type information
                status[i][j].used = true;     // Set the flag of used
                status[i][j].team = team;     // Store the team information
            }
            else if(i == 0 || i == 7)         // In row 0 and row 7, draw other pieces
            {
                status[i][j].used = true;     // Set the flag of used
                status[i][j].team = team;     // Store the team information
                
                if(j == 0 || j == 7)
                {
                    status[i][j].type = 2;    // Draw rooks on column 0 and 7, store the type
                }
                else if(j == 1 || j == 6)
                {
                    status[i][j].type = 3;    // Draw knights on column 1 and 6, store the type
                }
                else if(j == 2 || j == 5)
                {
                    status[i][j].type = 4;    // Draw bishops on column 2 and 5, store the type
                }
                else if(j == 3)
                {
                    status[i][j].type = 5;    // Draw queen on column 3, store the type
                }
                else if(j == 4)
                {
                    status[i][j].type = 6;    // Draw king on column 4, store the type
                }
            }
        }
    }
}

/*
* Function name: drawSquare
* Summary: draw the squares of the chess board
* Parameters: N/A
* Return: N/A
*/
void Board::drawSquare()
{
    glBegin(GL_QUADS);                       // Draw quads
    glVertex3f(0, 0, 0);
    glVertex3f(squareLen, 0, 0);
    glVertex3f(squareLen, squareLen, 0);
    glVertex3f(0, squareLen, 0);             // Set the four points
    glEnd();                                 // End drawing
}

/*
* Function name: drawBoard
* Summary: draw the chess board, which is consist of 8x8 squares
* Parameters: N/A
* Return: N/A
*/
void Board::drawBoard()
{
    bool colorDark = true;                   // Set the flag of drawing dark color
    for(int i=0; i<Board::boardRow; i++)
    {
        if(i%2 == 0)
        {
            colorDark = true;                // The odd number of row start with drak square
        }
        else
        {
            colorDark = false;               // The even number of columns start with light square
        }
        for(int j=0; j<Board::boardCol; j++)
        {
            if(colorDark)
            {
                glColor3f(0,0,0);           // For the drak square, set color to balck(0, 0, 0)
            }
            else
            {
                glColor3f(1, 1, 1);         // For the light square, set color to white(255, 255, 255)
            }
            glPushMatrix();                 // Push current position information
            glNormal3f(0.0f, 0.0f, 1.0f);
            glTranslatef(squareLen * i, squareLen * j, 0);    // Translate to the position to draw the current square
            drawSquare();                   // Call function to draw square
            glPopMatrix();                  // Pop the position information
            colorDark = !colorDark;         // Change the color for the next column
        }
    }
}

/*
* Function name: drawNormalPieces
* Summary: draw not enhanced pieces at the correct positions
* Parameters: N/A
* Return: N/A
*/
void Board::drawNormalPieces()
{
    for(int i=0; i < boardRow; i++)
    {
        for(int j=0; j < boardCol; j++)
        {
            if(status[i][j].used)                      // If the square is marked as used,then draw piece
            {
                glPushMatrix();                        // Push the position information
                glNormal3f(0.0f, 0.0f, 1.0f);          // Set normal
                glTranslatef(j*squareLen + squareLen/2, i*squareLen + squareLen/2, 0);  //Translate to the corrent position
                glScalef(0.75, 0.75, 1);               // Scale every piece to (0.75, 0.75, 1)
                status[i][j].drawNormal();             // Draw normal pieces
                glPopMatrix();                         // Pop the position information
            }
        }
    }
}

/*
* Function name: drawEnhancedPieces
* Summary: draw enhanced pieces at the correct positions
* Parameters: N/A
* Return: N/A
*/
void Board::drawEnhancedPieces()
{
    for(int i=0; i < boardRow; i++)
    {
        for(int j=0; j < boardCol; j++)
        {
            if(status[i][j].used)                       // If the square is marked as used,then draw piece
            {
                glPushMatrix();                         // Push the position information
                glNormal3f(0.0f, 0.0f, 1.0f);           // Set normal
                glTranslatef(j*squareLen + squareLen/2, i*squareLen + squareLen/2, 0);  //Translate to the correct position
                glScalef(0.75, 0.75, 1);                // Scale to (0.75, 0.75, 1)
                status[i][j].drawEnhanced();            // Draw enhanced pieces
                glPopMatrix();                          // Pop the position information
            }
        }
    }
}

/*
* Function name: randomGenerator
* Summary: generate a random number in the range of [0, 7] to choose the random piece or direction for movement
* Parameters: N/A
* Return: int res: the generated random number
*/
int Board::randomGenerator()
{
    int min = 0;            // Lower bound
    int max = 8;            // Upper bound
    int k =rand();          // Generate random number
    double res = k % (max - min) + min;     //Get the random number
    return res;             // Return the generated random number
}

/*
* Function name: pieceTested
* Summary: check if a piece has been tested if it can move
* Parameters:
 * std::array<std::array<int, 2>, 16> arr: store the positions of the pieces that have been tested
 * int x: the x-axis of the current piece
 * int y: the y-axis of the current piece
 * int num: the number of the pieces tested
* Return: bool result: bool variable showing if the current piece has been tested
*/
bool Board::pieceTested(std::array<std::array<int, 2>, 16> arr, int x, int y, int num)
{
    bool result = false;
    for (int i = 0; i < num; i++)             // Loop the pawnPosition array
    {
        if (arr[i][0] == x && arr[i][1] == y) // If the position is already in the array, meaning it has been tested
            result = true;                    // Set the tested flag to true
    }
    return result;
}

/*
* Function name: pawnMovement
* Summary: Randomly select a pawn and move it randomly forwards or backwards, if its movement is not allowed, pick another one
* Parameters: N/A
* Return: N/A
*/
void Board::pawnMovement()
{
    std::array<std::array<int, 2>, 16> pawnPosition; // 2D array to store positions of pawns
    int pawnNum=0;                  // Amount of pawns tested
    bool movedCompleted = false;    // Flag to denote if the movement is completed
    while(movedCompleted == false)  // Loop till completed
    {
        if (pawnNum >= 16)          // If all the pawns are tested
        {
            break;                  // Break the while loop
        }
        int x = randomGenerator();  // Generate a random column number
        int y = randomGenerator();  // Generate a random row number
        bool tested = pieceTested(pawnPosition, x, y, pawnNum); // Flag if random position has been tested
        if(!tested)                 // If the position has not been tested, test it
        {
            if (status[y][x].type == 1 && status[y][x].used == true)    // If the position is used and its type is pawn
            {
                pawnPosition[pawnNum][0] = x;
                pawnPosition[pawnNum][1] = y;         // Store the pawn's position
                
                int direction = (randomGenerator() < 4) ? -1 : 1;   // Get a random direction 1 or -1
                for(int i = 0; i < 2;i++)       // Loop the two directions
                {
                    int xMoved = x;
                    int yMoved = y+direction;   // Calculate the position after moving
                    
                    // Check if the moved position is in the board and not been used
                    
                    if(xMoved >= 0 && xMoved <= 7 && yMoved >= 0 && yMoved <= 7)
                    {
                        if(!status[yMoved][xMoved].used)
                        // Check if the moved position is in the board and not been used by our side
                        {
                            status[yMoved][xMoved].type = 1;      // Set the moved position as knight
                            status[y][x].type = 0;                // Set the old position no piece
                            status[yMoved][xMoved].used = true;   // Set the moved position used
                            status[y][x].used = false;            // Set the old position not used
                            status[yMoved][xMoved].team = status[y][x].team;//Set the team as ours
                            movedCompleted = true;                // Set the completed flag
                            break;          // Break the while loop after move
                        }
                        else
                        {
                            direction *= (-1);  // If the first direction is not feasible, try opposite one
                        }
                    }
                    else
                    {
                        direction *= (-1);  // If the first direction is out of bound, try opposite one
                    }
                }
            }
        }
    }
}

/*
* Function name: knightMovement
* Summary: Randomly select a knight and move it randomly forwards or backwards, if its movement is not allowed, pick another one
* Parameters: N/A
* Return: N/A
*/
void Board::knightMovement()
{
    std::array<std::array<int, 2>, 16> knightPosition;   // 2D array to store positions of knights
    int knightNum = 0;              // Amount of pawns tested
    bool movedCompleted = false;    // Flag to denote if the random position is chosen
    while(movedCompleted == false)  // Loop till completed
    {
        if (knightNum >= 4)         // If all the pawns are tested
        {
            break;                  // Break the while loop
        }
    
        int x = randomGenerator();  // Generate a random column number
        int y = randomGenerator();  // Generate a random row number
        bool tested = pieceTested(knightPosition, x, y, knightNum); // Flag if random position has been tested
        if(!tested) // If the position has not been tested, then test it
        {
            if (status[y][x].type == 3 && status[y][x].used == true)    // If the position is used and its type is knight
            {
                knightPosition[knightNum][0] = x;
                knightPosition[knightNum][1] = y; // Store the knight position
                
                int start = randomGenerator();    // Generate a random number to determine the direction
                for(int i = 0; i < 8;i++)         // Loop all the eight possible position
                {
                    int xMoved = -1;
                    int yMoved = -1;              // Initiate the moved position
                    int direction = start + i;    // Add i to the generated random number to get diretion
                    if (direction > 7)            // If get an number larger than 7
                    {
                        direction -= 8;           // Minus 8
                    }
                    
                    switch (direction)            // Find the direction pattern
                    {
                        case 0:
                        {
                            xMoved = x-1;         // Left 1 Front 2
                            yMoved = y+2;
                            break;
                        }
                        case 1:
                        {
                            xMoved = x-2;         // Left 2 Front 1
                            yMoved = y+1;
                            break;
                        }
                        case 2:
                        {
                            xMoved = x-2;
                            yMoved = y-1;
                            break;
                        }
                        case 3:
                        {
                            xMoved = x-1;
                            yMoved = y-2;
                            break;
                        }
                        case 4:
                        {
                            xMoved = x+1;
                            yMoved = y+2;
                            break;
                        }
                        case 5:
                        {
                            xMoved = x+2;
                            yMoved = y-1;
                            break;
                        }
                        case 6:
                        {
                            xMoved = x+2;
                            yMoved = y+1;
                            break;
                        }
                        case 7:
                        {
                            xMoved = x+1;         // Right 1 Front 2
                            yMoved = y+2;
                            break;
                        }
                    }

                    if(xMoved >= 0 && xMoved <= 7 && yMoved >= 0 && yMoved <= 7)
                    {
                        if(!(status[yMoved][xMoved].used && status[yMoved][xMoved].team == status[y][x].team))
                        //Check if the moved position is in the board and not been used by our side
                        {
                            status[yMoved][xMoved].type = 3;      // Set the moved position as knight
                            status[y][x].type = 0;                // Set the old position no piece
                            status[yMoved][xMoved].used = true;   // Set the moved position used
                            status[y][x].used = false;            // Set the old position not used
                            status[yMoved][xMoved].team = status[y][x].team;//Set the team as ours
                            movedCompleted = true;                // Set the completed flag
                            break;          // Break the while loop after move
                        }
                    }
                }
            }
        }
    }
}
