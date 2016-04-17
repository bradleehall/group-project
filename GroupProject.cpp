/*
 * GroupProject.cpp
 *
 *  Created on: Mar 31, 2014
 *  Modified on: Mar 31, 2014
 *  Author: D. Booth
 */

#include "GroupProject.h"

//GroupProject Constructor

GroupProject::GroupProject(GLUT_Plotter* g){
	this->g = g;
}

GroupProject::GroupProject()
{
	//end game;
	delete g;
}


//GroupProject Main Game Loop
void GroupProject::Play(void){

	//Check for Keyboard Hit
	while(g->kbhit()){
		int k = g->getKey();	//change int to char***
		switch (k){
		     case 27: exit(1); //ESC key
		              break;
		}
	}
	
	/**How the user can choose different commands**/
	/*
	while(k=g->getkey()){
		if(k = 'i'){
			//use insert function 
				//Need to use:  AddValue();
		}
		else if(k = 'r'){
			//use remove function
				//Need to use: RemoveValue();
		}
		else if(k = 'a'){
			//access that number
				//Need to use: FindValue(**ptr)
				//	       MoveToTop(SplayNode *ptr, SplayNode* target);
		}
		else{
			//quit
			break;
		}
	}
	*/

	//Check for mouse click
	while(g->click()){

		Click c;
		c = g->getClick();
	}

	// Update screen - draw game
	g->Draw();
}
