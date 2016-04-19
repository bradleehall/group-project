/*
 * GroupProject.cpp
 *
 *  Created on: Mar 31, 2014
 *  Modified on: Mar 31, 2014
 *  Author: D. Booth
 */

#include "GroupProject.h"
#include <cmath>
#include <cstdlib>

//GroupProject Constructor

GroupProject::GroupProject(GLUT_Plotter* g){
	this->g = g;
}

GroupProject::~GroupProject()
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

	while(k=g->getKey()){
		if(k = 'i'){
			//use insert function
            //Need to use:  AddValue();
            int valinsert = 0;
            cout << "What would you like to insert? ";
            cin >> valinsert;
		}
		else if(k = 'r'){
			//use remove function
            //Need to use: RemoveValue();
            int valremove = 0;
            cout << "What would you like to remove? ";
            cin >> valremove;
		}
		else if(k = 'a'){
			//access that number
            //Need to use: FindValue(**ptr)
            //	       MoveToTop(SplayNode *ptr, SplayNode* target);
            int valaccess = 0;
            cout << "What would you like to access? ";
            cin >> valaccess;
		}
		else{
			//quit
			break;
		}
	}


	//Check for mouse click
	while(g->click()){

		Click c;
		c = g->getClick();
	}

	// Update screen - draw game
	g->display();
}

//everything from here on is WIP--let Michael know if you edit it
//most of it is directly copied.  it will need to be adapted to
//more suit the group style, format, etc.
void drawCircle(float segments, float radius, float sx, float sy)
{
    float theta = 2 * 3.1415926 / segments;
    float tan_factor = tanf(theta);
    float radial_factor = cosf(theta);
    float x = radius;
    float y = 0;
    int cache_pt = 0;
    double cache_x;
    double cache_y;
    glBegin(GL_LINES);
    for (int ii = 0; ii < segments; ii++)
    {
        if(!cache_pt)
        {
            cache_x = x+sx;
            cache_y = y+sy;
            cache_pt = 1;
        }
        else
        {
            //glVertex2f(cache_x,cache_y);
            glVertex2f(x + sx, y + sy);
            cache_x = x+sx;
            cache_y = y+sy;
        }
        float tx = -y;
        float ty = x;
        x += tx * tan_factor;
        y += ty * tan_factor;
        x *= radial_factor;
        y *= radial_factor;
    }
    glEnd();
}

void draw_line(float x1, float y1, float x2, float y2)
{
    glBegin(GL_LINES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glEnd();
}

void draw_text(char* text, float x, float y)
{
    GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;
    glRasterPos3f(x, y, 0);
    for (int i = 0; text[i] != '\0'; i++)
    {
        glutBitmapCharacter(font_style, text[i]);
    }
}

void drawNode(SplayNode<int> *t_root, float x1, float y1, int level)
{
    if (!(t_root))
    {
        return;
    }
    float segments = 25;
    float radius = 1.0;
    float left_angle = 245;
    float right_angle = 115;
    float branch_length = 12 - level*2.5;
    float angle_change = 20;

    drawCircle(segments, radius, x1, y1);

    char buff[5];
    itoa(t_root->getVal(), buff, 10);
    draw_text(buff, x1, y1);

    if(t_root->getLeft())
    {
        float angle = left_angle - level*angle_change;
        double radian = angle*3.14/180;
        float m = (double)tan((double)radian);
        float x2 = x1 + branch_length * sin((double) radian);
        float y2 = y1 + branch_length * cos((double) radian);
        drawNode(t_root->getLeft(), x2, y2, level+1);
        draw_line(x1, y1, x2, y2);
    }
    if(t_root->getRight())
    {
        float angle = right_angle + level*angle_change;
        float radian = angle*3.14/180;
        float m = (double)tan((double)radian);
        float x2 = x1 + branch_length * sin((double) radian);
        float y2 = y1 + branch_length * cos((double) radian);
        drawNode(t_root->getRight(), x2, y2, level+1);
        draw_line(x1, y1, x2, y2);
    }
}

void display()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0, 10, -30);
    glColor3f(1, 1, 1);

    drawNode(root, 0, 0, 0);

    glutSwapBuffers();
}
