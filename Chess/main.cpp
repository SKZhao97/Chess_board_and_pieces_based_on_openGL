/*
Author: Sikai Zhao
Class: ECE 6122
Last date modified: 11/21/2019
Description: Define parameters and precoss keyboard commands such as 'U', 'K' and setup windows and render scene. The functions to draw chess board and pieces are called in the render Sence function.
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>                    // To do math calculation
#include "Board.h"                  // Include header file

#ifdef __APPLE__                    // To use glut on macOS
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else                               // To use glut on Pace-ice
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#define ESC 27                      // Define ESC to quit

float x = 4, y = -5, z = 10;        // Camera position(4, -5, 10)
float angle = 0.0;                  // angle of rotation for the camera direction

bool light0 = true;                 //Boolean variable to control the ambient light
GLfloat light0_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat light0_specular[] = { 0, 0, 0, 0 };
GLfloat light0_diffuse[] = { 0, 0, 0, 0 };          //Ambient, sqecular and postion info of light1

bool light1 = true;                 //Boolean variable to control the diffuse light
GLfloat light1_ambient[] = { 0, 0, 0, 0 };
GLfloat light1_diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat light1_specular[] = { 0.3, 0.3, 0.3, 1.0 };
GLfloat light1_position[] = { 5, 5, 8};             //Diffuse, sqecular and postion info of light1

float mat_specular[] = {0.5, 0.5, 0.5, 1.0};
float shininess = 50.0;                             //Material properties of the chess pieces

bool enhanced = false;   //Boolean variable to control if the enhanced pieces should be drawed

Board board;             //Initial an object of Board

/*
* Function name: changeSize
* Summary: adjust the perspective according to the change of window
* Parameters:
* 1. int w: weigth of the window
* 2. int h: height of the window
* Return: N/A
*/
void changeSize(int w, int h)
{
    float ratio = ((float)w) / ((float)h);   // window aspect ratio
    glMatrixMode(GL_PROJECTION);             // projection matrix is active
    glLoadIdentity();                        // reset the projection
    gluPerspective(45.0, ratio, 0.1, 200.0); // perspective transformation
    glMatrixMode(GL_MODELVIEW);              // return to modelview mode
    glViewport(0, 0, w, h);                  // set viewport (drawing area) to entire window
}

/*
* Function name: update
* Summary: Redisplay the view
* Parameters: N/A
* Return: N/A
*/
void update(void)
{
    glutPostRedisplay();
}

/*
* Function name: pressNormalKeys
* Summary: keyboard command processing
* Parameters:
* 1. unsigned char key: the key inputed;
* 2&3. int xx & int yy: indicate the mouse location in window relative coordinates when the key was pressed(required by glutKeyboardFunc)
* Return: N/A
*/
void pressNormalKeys(unsigned char key, int xx, int yy)
{

    switch (key)
    {
        
        case 'd':
        {
            z = z - 0.25;           // Moves the eye location down z –axis 0.25 m each time
            break;
        }
        case 'D':
        {
             z = z - 0.25;          // Moves the eye location down z –axis 0.25 m each time
            break;
        }
        case 'u':
        {
            z = z + 0.25;           // Moves the eye location down z +axis 0.25 m each time
            break;
        }
        case 'U':
        {
            z = z + 0.25;           // Moves the eye location down z +axis 0.25 m each time
            break;
        }
        case 'r':
        {
            angle = atan2((y-4),(x-4))-(10.0/180)*3.14;
            // Calculate the angle of eye position in terms of the center of the chess board
            double r = sqrt((x-4)*(x-4) + (y-4)*(y-4));
            x = r*cos(angle) + 4;
            y = r*sin(angle) + 4;       // Calcule the new x, y position of the eye position
            break;
        }
        case 'R':
        {
            angle = atan((y-4)/(x-4)) - (10.0/180)*3.14;
            // Calculate the angle of camera and the center of the chess board after rotate 10 degree
            double r = sqrt((x-4)*(x-4) + (y-4)*(y-4));
            x = r*cos(angle) + 4;
            y = r*sin(angle) + 4;       // Calcule the new x, y position of the camera position
            break;
        }
        case '0':
        {
            light0 = !light0;           // Turn on/off the light0
            break;
        }
        case '1':
        {
            light1 = !light1;           // Turn on/off the light1
            break;
        }
        case 'e':
        {
            enhanced = !enhanced;       // Show enhanced pieces or not
            break;
        }
        case 'E':
        {
            enhanced = !enhanced;       // Show enhanced pieces or not
            break;
        }
        case 'k':
        {
            board.knightMovement();     // Move a random knight to a random possible position
            break;
        }
        case 'K':
        {
            board.knightMovement();     //Move a random knight to a random possible position
            break;
        }
        case 'P':
        {
            board.pawnMovement();       // Move a random pawn to a random possible position
            break;
        }
        case 'p':
        {
            board.pawnMovement();       // Move a random pawn to a random possible position
            break;
        }
    }
}

/*
* Function name: pressSpecialKeys
* Summary: keyboard special command processing
* Parameters:
* 1. unsigned char key: the key inputed;
* 2&3. int xx & int yy: indicate the mouse location in window relative coordinates when the key was pressed
* Return: N/A
*/
void pressSpecialKey(int key, int xx, int yy)
{
    
}

/*
* Function name: releaseSpecialKeys
* Summary: stop keyboard special command processing
* Parameters:
* 1. unsigned char key: the key inputed;
* 2&3. int x & int y: indicate the mouse location in window relative coordinates when the key was pressed
* Return: N/A
*/
void releaseSpecialKey(int key, int xx, int yy)
{
    
}

/*
* Function name: renderScene
* Summary: Render the color, lighting and draw pieces and board
* Parameters: N/A
* Return: N/A
*/
void renderScene()
{
    glClearColor(0.7, 0.9, 1.0, 1.0);                   // Clear color with light blue
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear depth buffers
    glLoadIdentity();                                   // Reset transformations
    glEnable(GL_LIGHTING);                              // Enable lighting
    glEnable(GL_COLOR_MATERIAL);                        // Enable material color
    
    if(light0)
    {
        glEnable(GL_LIGHT0);                            // Enable light0
    }
    else
    {
        glDisable(GL_LIGHT0);                           // Disable light0
    }
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular); //Set light0 properties
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    

    if(light1)
    {
        glEnable(GL_LIGHT1);                            // Enable light1
    }
    else
    {
        glDisable(GL_LIGHT1);                           // Disable light1
    }
    
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);         //Set light1 properties

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);    // Set material properties
    
    glEnable(GL_DEPTH_TEST);                            // Enable depth test
    glShadeModel(GL_SMOOTH);                            // Shade model
    glEnable(GL_NORMALIZE);
    
    gluLookAt(
        x, y, z,
        4, 4, 0.0,
        0.0, 0.0, 1.0);                                 // Set the look at position

    board.drawBoard();                  // Call drawBoard() in Board class to draw the chess board
    
    if (enhanced)
    {
        board.drawEnhancedPieces();     // If enhanced is set true, draw enhanced pieces
    }
    else
    {
        board.drawNormalPieces();       // If enhanced is false, do not need to draw enhanced pieces
    }
    
    glutSwapBuffers();                  // Use swap buffer to prevent flickering
    
}

/*
* Function name: main
* Summary: Entry of the program and callback functions. Use the functions to deal with displaying, keyboard commands and other issues.
* Parameters:
1. int argc: Number of command line parameters
2. char **arg: Command line parameters
* Return: N/A
*/
int main(int argc, char **argv)
{
    glutInit(&argc, argv);          //Initialize GLUT
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);  // Turn on RGB color, depth testing and double buffering
    
    glutInitWindowSize(600, 600);        //Set window size
    glutInitWindowPosition(320, 120);    //Set window position on the screen
    glutCreateWindow("Chess");           //Set the title of the window
    glutDisplayFunc(renderScene);        //Render scene
    glutReshapeFunc(changeSize);         //Callback for window reshape
    glutIdleFunc(update);                //Update
    glutSpecialFunc(pressSpecialKey);    //Deal with special key press
    glutSpecialUpFunc(releaseSpecialKey);//Deal with special key release
    glutKeyboardFunc(pressNormalKeys);   //Deal with normal key press
    glutMainLoop();                      //Loop the glut main
}
