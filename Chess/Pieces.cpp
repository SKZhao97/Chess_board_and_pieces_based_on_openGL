/*
Author: Sikai Zhao
Class: ECE 6122
Last date modified: 11/21/2019
Description:
 1. Store the team, type information and used status of each piece
 2. Draw the six kinds of enhanced or non-enhanced pieces
*/

#include <iostream>
#include <fstream>              // To import from file
#include <string>               // To use string
#include <sstream>              // To use string operations

#ifdef __APPLE__                // To use glut on macOS
#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>
#else                           // To use glut on Pace-ice
#include <GL/gl.h>
#include <GL/glut.h>
#endif
#include "Pieces.h"

/*
* Function name: teamColor
* Summary: set the color of the team
* Parameters: N/A
* Return: N/A
*/
void Pieces::teamColor()
{
    if(team)
    {
        glColor3ub(140, 140, 135);      // Set color as (140, 140, 135)
    }
    else
    {
        glColor3ub(150, 75, 0);         // Set color as (150, 75, 0)
    }
}

/*Function name: drawEnhancedObj
 *Summary: Function to help import .obj files to draw enhanced pieces
 *Parameters: string addrstr: the relative address of the .obj file
 *Return: N/A
 *online source: http://www.gimoo.net/t/1506/556e7bc1e744b.html
 */
void Pieces::drawEnhancedObj(std::string addrstr)
{
    int v_num=0;
    int f_num=0;
    int vn_num=0;       // The number of Geometric vertices, Faces and Vertex normals)
    
    GLfloat **vArr;     // 2D array to store vertices
    int **fvArr;        // 2D array to store faces
    int **fnArr;        // 2D array to store face normals
    GLfloat **vnArr;    // 2D array to store Vertex normals
    std::string s1,s2,s3,s4;
    GLfloat f2,f3,f4;
    std::ifstream infile0(addrstr.c_str());     //Infile object
    std::string sline;           // Save one line
    int i=0;
    while(getline(infile0, sline))
    {
        if(sline[0]=='v')       // If it's a vertice
        {
            if(sline[1]=='n')   // If it's vertex normal
                vn_num++;
            else
                v_num++;
        }
        if(sline[0]=='f')       // If it's face
        {
            f_num++;
        }
    }
    vArr=new GLfloat*[v_num];   // Get the number
    for (int i=0;i<v_num;i++)
    {
        vArr[i]=new GLfloat[3];
    }
    vnArr=new GLfloat*[vn_num]; // Get the number
    for (i=0;i<vn_num;i++)
    {
        vnArr[i]=new GLfloat[3];
    }
    fvArr=new int*[f_num];      // Get the number
    fnArr=new int*[f_num];
    for (i=0;i<f_num;i++)
    {
        fvArr[i]=new int[3];
        fnArr[i]=new int[3];
    }
    std::ifstream infile(addrstr.c_str());
    int ii=0,jj=0,kk=0;
    
    while(getline(infile,sline))        // Input
    {
        if(sline[0]=='v')
        {
            if(sline[1]=='n')//vn
            {
                std::istringstream sin(sline);      // Store
                sin>>s1>>f2>>f3>>f4;
                vnArr[ii][0]=f2;
                vnArr[ii][1]=f3;
                vnArr[ii][2]=f4;
                ii++;
            }
            else//v
            {
                std::istringstream sin(sline);      // Store
                sin>>s1>>f2>>f3>>f4;
                vArr[jj][0]=f2;
                vArr[jj][1]=f3;
                vArr[jj][2]=f4;
                jj++;
            }
        }
        if (sline[0]=='f')
        {
            std::istringstream in(sline);           // Store
            GLfloat a;
            in>>s1;
            int i,k;
            for(i=0;i<3;i++)
            {
                in>>s1;
                a=0;
                for(k=0;s1[k]!='/';k++)
                {
                    a=a*10+(s1[k]-48);
                }
                fvArr[kk][i]=a;
                
                a=0;
                for(k=k+2;s1[k];k++)
                {
                    a=a*10+(s1[k]-48);;
                }
                fnArr[kk][i]=a;
            }
        kk++;
        }
    }
    
    teamColor();                // Set color
    for (int i=0;i<f_num;i++)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // Set model
        glBegin(GL_TRIANGLES);  // Draw triangles to draw the .obj files' objects
        
        glNormal3f(vnArr[fnArr[i][0]-1][0], vnArr[fnArr[i][0]-1][1], vnArr[fnArr[i][0]-1][2]);
        glVertex3f(vArr[fvArr[i][0]-1][0], vArr[fvArr[i][0]-1][1], vArr[fvArr[i][0]-1][2]);
        
        glNormal3f(vnArr[fnArr[i][1]-1][0], vnArr[fnArr[i][1]-1][1], vnArr[fnArr[i][1]-1][2]);
        glVertex3f(vArr[fvArr[i][1]-1][0], vArr[fvArr[i][1]-1][1], vArr[fvArr[i][1]-1][2]);
        
        glNormal3f(vnArr[fnArr[i][2]-1][0], vnArr[fnArr[i][2]-1][1], vnArr[fnArr[i][2]-1][2]);
        glVertex3f(vArr[fvArr[i][2]-1][0], vArr[fvArr[i][2]-1][1], vArr[fvArr[i][2]-1][2]);
        
        glEnd();
    }
}

/*
* Function name: drawNormal
* Summary: draw the non-enhanced pieces
* Parameters: N/A
* Return: N/A
*/
void Pieces::drawNormal()
{
    switch(type)            // Determines which piece to draw
    {
        case 1:
        {
            drawPawn();     // draw pawn
            break;
        }
        case 2:
        {
            drawRook();     // draw rook
            break;
        }
        case 3:
        {
            drawKnight();   // draw knight
            break;
        }
        case 4:
        {
            drawBishop();   // draw bishop
            break;
        }
        case 5:
        {
            drawQueen();    // draw queen
            break;
        }
        case 6:
        {
            drawKing();     // draw king
            break;
        }
    }
}

/*
* Function name: drawEnhanced
* Summary: draw the enhanced pieces
* Parameters: N/A
* Return: N/A
*/
void Pieces::drawEnhanced()
{
    glEnable(GL_NORMALIZE);         // Enable GL_NORMALIZE
    switch(type)                    // Determines which piece to draw
    {
        case 1:
        {
            glTranslated(-0.1, 0.1, 0);  // Adjust slightly
            drawEnhancedPawn();     // draw enhanced pawn
            break;
        }
        case 2:
        {
            drawEnhancedRook();     // draw enhanced rook
            break;
        }
        case 3:
        {
            drawEnhancedKnight();   // draw enhanced knight
            break;
        }
        case 4:
        {
            glTranslated(-0.1, 0.1, 0);  // Adjust slightly
            drawEnhancedBishop();   // draw enhanced bishop
            break;
        }
        case 5:
        {
            glTranslated(-0.1, 0.1, 0);  // Adjust slightly
            drawEnhancedQueen();    // draw enhanced queen
            break;
        }
        case 6:
        {
            drawEnhancedKing();     // draw enhanced king
            break;
        }
    }
}

/*
* Function name: drawPawn
* Summary: draw non-enhanced pawn
* Parameters: N/A
* Return: N/A
*/
void Pieces::drawPawn()
{
    glPushMatrix();
    teamColor();
    glTranslatef(0, 0, 0.5);
    glutSolidSphere(0.5, 20, 20);       // Draw pawn
    glPopMatrix();
}

/*
* Function name: drawPawn
* Summary: draw enhanced pawn
* Parameters: N/A
* Return: N/A
*/
void Pieces::drawEnhancedPawn()
{
    glPushMatrix();
    glTranslatef(0.05,-0.05, 0.7845);
    glRotated(90, 1, 0, 0);
    glScalef(0.0015,0.0015,0.0012);
    teamColor();
    drawEnhancedObj("pawn.obj");    // Call function to draw enhanced pawn using .obj file
    glPopMatrix();
}

/*
* Function name: drawRook
* Summary: draw non-enhanced rook
* Parameters: N/A
* Return: N/A
*/
void Pieces::drawRook()
{
    glPushMatrix();
    teamColor();
    //glColor3f(150, 75, 0);
    glTranslatef(0,0,0.505);       // Draw rook
    glutSolidCube(1);
    glPopMatrix();
}

/*
* Function name: drawRook
* Summary: draw enhanced rook
* Parameters: N/A
* Return: N/A
*/
void Pieces::drawEnhancedRook()
{
    glPushMatrix();
    glTranslatef(0,0,0.89);
    glRotated(90, 1, 0, 0);
    glScalef(0.0015,0.0015,0.0012);
    teamColor();
    drawEnhancedObj("rook.obj");    // Call function to draw enhanced rook using .obj file
    glPopMatrix();
}

/*
* Function name: drawKnight
* Summary: draw non-enhanced knight
* Parameters: N/A
* Return: N/A
*/
void Pieces::drawKnight()
{
    glPushMatrix();
    teamColor();
    glTranslatef(0,0,0.3);
    glRotated(90, 1, 0, 0);
    glutSolidTeapot(.375);       // Draw knight
    glPopMatrix();
    
}

/*
* Function name: drawKnight
* Summary: draw enhanced knight
* Parameters: N/A
* Return: N/A
*/
void Pieces::drawEnhancedKnight()
{
    glPushMatrix();
    teamColor();
    glTranslatef(0,0,0.9155);
    glScalef(0.002,0.002,0.0015);
    glRotated(90, 1, 0, 0);
    glRotated(90, 0, 1, 0);
    drawEnhancedObj("knight.obj");    // Call function to draw enhanced knight using .obj file
    glPopMatrix();
}

/*
* Function name: drawBishop
* Summary: draw non-enhanced bishop
* Parameters: N/A
* Return: N/A
*/
void Pieces::drawBishop()
{

    glPushMatrix();
    teamColor();
    glutSolidCone(0.5, 1, 20, 20);       // Draw bishop
    glPopMatrix();
}

/*
* Function name: drawBishop
* Summary: draw enhanced bishop
* Parameters: N/A
* Return: N/A
*/
void Pieces::drawEnhancedBishop()
{
    glPushMatrix();
    glTranslatef(0.1,0,1.160);
    glRotated(90, 1, 0, 0);
    glScalef(0.0015,0.0015,0.0012);
    teamColor();
    drawEnhancedObj("bishop.obj");    // Call function to draw enhanced bishop using .obj file
    glPopMatrix();
}

/*
* Function name: drawQueen
* Summary: draw non-enhanced Queen
* Parameters: N/A
* Return: N/A
*/
void Pieces::drawQueen()
{

    glPushMatrix();
    teamColor();
    glTranslatef(0,0,0.532);
    glRotatef(50, 0,0.5,0.5);
    glScalef(0.6,0.6,0.6);
    glutSolidTetrahedron();           // Draw queen
    glPopMatrix();
}

/*
* Function name: drawQueen
* Summary: draw enhanced queen
* Parameters: N/A
* Return: N/A
*/
void Pieces::drawEnhancedQueen()
{
    glPushMatrix();
    glTranslatef(0.1,0,1.455);
    glRotated(90, 1, 0, 0);
    glScalef(0.0015,0.0015,0.0012);
    teamColor();
    drawEnhancedObj("queen.obj");    // Call function to draw enhanced queen using .obj file
    glPopMatrix();
}
/*
* Function name: drawking
* Summary: draw non-enhanced king
* Parameters: N/A
* Return: N/A
*/
void Pieces::drawKing()
{
    glPushMatrix();
    teamColor();
    glTranslatef(0,0,0.525);
    glRotatef(60, 0,0.5,0.5);
    glScalef(0.7,0.7,0.7);
    glutSolidOctahedron();      // Draw king
    glPopMatrix();
}

/*
* Function name: drawKing
* Summary: draw enhanced biking
* Parameters: N/A
* Return: N/A
*/
void Pieces::drawEnhancedKing()
{
    glPushMatrix();
    glTranslatef(-0.025,0,1.568);
    glRotated(90, 1, 0, 0);
    glScalef(0.0015,0.0015,0.0012);
    teamColor();
    drawEnhancedObj("king.obj");    // Call function to draw enhanced king using .obj file
    glPopMatrix();
}
