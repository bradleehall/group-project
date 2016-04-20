//============================================================================
// Name        : Tetris Driver.cpp
// Author      : Dr. Booth
// Version     :
// Copyright   : Your copyright notice
// Description : Main Driver For Group Project
//============================================================================

#include <iostream>
#include "GroupProject.h"
#include "GLUT.h"
using namespace std;

void runMainLoop( int val )
{
    //Frame logic
    update();
    render();

    //Run frame one more time
    glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, val );
}

int main(int argc, char* args[] ) {
	/*GLUT_Plotter* g = new GLUT_Plotter(); //Create plotter
	app = new GroupProject(g);                 //Create Game (Tetris)
	g->RegisterIdleFunc(Player);          //Register Callback
	g->MainLoop();                        //Enter main loop*/

	//Initialize FreeGLUT
    glutInit( &argc, args );

    //Create OpenGL 2.1 context
    glutInitContextVersion( 2, 1 );

    //Create Double Buffered Window
    glutInitDisplayMode( GLUT_DOUBLE );
    glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
    glutCreateWindow( "OpenGL" );

    //Do post window/context creation initialization
    if( !initGL() )
    {
        printf( "Unable to initialize graphics library!\n" );
        return 1;
    }

    //Set keyboard handler
    //glutKeyboardFunc( handleKeys );

    //Set rendering function
    glutDisplayFunc( render );

    //Set main loop
    glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, 0 );

    //Start GLUT main loop
    glutMainLoop();


	return 0;
}


