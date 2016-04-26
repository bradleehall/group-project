#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <stdlib.h>
//#include <conio.h> //IMPORTANT:  USE THIS LINE FOR WINDOWS!!!
//#include <ncurses.h> //IMPORTANT:  USE THIS LINE FOR UNIX (MAC OSX, LINUX)
                    //ALSO: YOU MUST HAVE THE NCURSES LIBRARY INSTALLED
                    //ON MAC OSX, I RECOMMEND THE HOMEBREW PACKAGE MANAGER
#include <stdio.h>
#include <iostream>
#include "math.h"
#include "glut.h" //IMPORTANT:  PLACE GLUT.H IN MAIN PROJECT FOLDER
#include "freeglut.h" //SAME FOR THIS
#include <string>
#include <sstream>

using namespace std;

template <class Base>
struct SplayNode
{
    SplayNode *left;
    SplayNode *right;
    Base value;
};

template <class Base>
void inorder(SplayNode<Base> *target);

template <class Base>
void preorder(SplayNode<Base> *target);

template <class Base>
void postorder(SplayNode<Base> *target);

template <class Base>
SplayNode<Base>* createnode(const Base &initval);

template <class Base>
SplayNode<Base>* right_rotate(SplayNode<Base> *target);

template <class Base>
SplayNode<Base>* left_rotate(SplayNode<Base> *target);

template <class Base>
SplayNode<Base>* access(const Base &accessval, SplayNode<Base> *target);

template <class Base>
SplayNode<Base>* insert(const Base &valinsert);

template <class Base>
SplayNode<Base>* insert(const Base &valinsert, SplayNode<Base> *target);

template <class Base>

SplayNode<Base>* remove(const Base &valremove, SplayNode<Base> *target);

void reverse(char *target, int length);

char* itoa(int num, char *target, int radix);

template <class Base>
string userinput();

void circle_graphic(float segments, float radius, float sx, float sy);

void text_graphic(char* text, float x, float y);

template <class Base>
void node_graphic(SplayNode<Base> *target, float x1, float y1, int level);

void display();

void redraw(int width, int height);

void keychecker(unsigned char, int, int);

#endif // FUNCTIONS_H_INCLUDED
