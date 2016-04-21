//This file is Michael's testing code.  Use it if you'd like to contribute
//to the non GLUT_Plotter-based code.

#include <stdlib.h>
//#include <conio.h> //IMPORTANT:  USE THIS LINE FOR WINDOWS!!!
#include <ncurses.h> //IMPORTANT:  USE THIS LINE FOR UNIX (MAC OSX, LINUX)
                    //ALSO: YOU MUST HAVE THE NCURSES LIBRARY INSTALLED
                    //ON MAC OSX, I RECOMMEND THE HOMEBREW PACKAGE MANAGER
#include <stdio.h>
#include <iostream>
#include "math.h"
#include "glut.h" //IMPORTANT:  PLACE GLUT.H IN MAIN PROJECT FOLDER
using namespace std;

template <class Base>
struct SplayNode {
    int data;
    struct treenode* left;
    struct treenode* right;
    struct treenode* parent;
}TREENODE;

/* A utility function to reverse a string  */
void reverse(char str[], int length)
{
    int start = 0;
    int end = length -1;
    while (start < end)
    {
        swap(*(str+start), *(str+end));
        start++;
        end--;
    }
}

// Implementation of itoa()
char* itoa(int num, char* str, int base)
{
    int i = 0;
    bool isNegative = false;

    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // In standard itoa(), negative numbers are handled only with
    // base 10. Otherwise numbers are considered unsigned.
    if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }

    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }

    // If number is negative, append '-'
    if (isNegative)
        str[i++] = '-';

    str[i] = '\0'; // Append string terminator

    // Reverse the string
    reverse(str, i);

    return str;
}

TREENODE* root = NULL;
void add_node(TREENODE** t_root, TREENODE** current) {
    if(*t_root==NULL) {
        *t_root = *current;
        return;
    }
    if((*current)->data < (*t_root)->data) {
        if((*t_root)->left==NULL) {
            (*t_root)->left = (*current);
        }
        else {
            add_node(&((*t_root)->left),current);
        }
    }
    else {
        if((*t_root)->right==NULL) {
            (*t_root)->right = *current;
        }
        else {
            add_node(&((*t_root)->right),current);
        }
    }
}

void accept_tree(){
    int n;
    cout << "\nCREATING BST: (enter 0 to finish)\n";
    while(1) {
        fflush(stdin);
        cout<<"\nEnter node value: ";
        cin>>n;
        if(n==0) {
            break;
        }
        TREENODE* current = new TREENODE;
        current->data = n;
        current->right = NULL;
        current->left = NULL;
        current->parent = NULL;
        add_node(&root,&current);
    }
}
void inorder(TREENODE* root) {
    if(root!=NULL) {
        inorder(root->left);
        cout<<root->data;
        inorder(root->right);
    }
}
void preorder(TREENODE* root) {
    if(root!=NULL) {
        cout<<root->data;
        preorder(root->left);
        preorder(root->right);
    }
}
void postorder(TREENODE* root) {
    if(root!=NULL) {
        postorder(root->left);
        postorder(root->right);
        cout<<root->data;
    }
}
void drawCircle(float segments, float radius, float sx, float sy) {
    float theta = 2 * 3.1415926 / segments;
    float tan_factor = tanf(theta);
    float radial_factor = cosf(theta);
    float x = radius;
    float y = 0;
    int cache_pt = 0;
    double cache_x;
    double cache_y;
    glBegin(GL_LINES);
    for (int ii = 0; ii < segments; ii++) {
        if(!cache_pt) {
            cache_x = x+sx;
            cache_y = y+sy;
            cache_pt = 1;
        }
        else {
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
void draw_line(float x1,float y1,float x2, float y2) {
    glBegin(GL_LINES);
    glVertex2f(x1,y1);
    glVertex2f(x2,y2);
    glEnd();
}
void draw_text(char* text,float x, float y) {
    GLvoid *font_style = GLUT_BITMAP_TIMES_ROMAN_24;
    glRasterPos3f(x, y, 0);
    for (int i = 0; text[i] != '\0'; i++){
        glutBitmapCharacter(font_style, text[i]);
    }
}
void drawNode(TREENODE* t_root,float x1,float y1,int level) {
    if (t_root==NULL) {
        return;
    }
    float segments = 25;
    float radius = 1.0;
    float left_angle = 245;
    float right_angle = 115;
    float branch_length = 12 - level*2.5;
    float angle_change = 20;
    // Draw the current circle
    drawCircle(segments,radius,x1,y1);
    char buff[5];
    itoa(t_root->data,buff,10);
    draw_text(buff,x1,y1);
    if(t_root->left) {
        // Draw the Left circle
        float angle = left_angle - level*angle_change;
        double radian = angle*3.14/180;
        float m = (double)tan((double)radian);
        float x2 = x1 + branch_length * sin((double) radian);
        float y2 = y1 + branch_length * cos((double) radian);
        drawNode(t_root->left,x2,y2,level+1);
        draw_line(x1,y1,x2,y2);
    }
    if(t_root->right) {
        // Draw the Right circle
        float angle = right_angle + level*angle_change;
        float radian = angle*3.14/180;
        float m = (double)tan((double)radian);
        float x2 = x1 + branch_length * sin((double) radian);
        float y2 = y1 + branch_length * cos((double) radian);
        drawNode(t_root->right,x2,y2,level+1);
        draw_line(x1,y1,x2,y2);
    }
}
void display(void) {
    glClearColor (0.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0,10,-30);
    glColor3f(1,1,1);
    drawNode(root,0,0,0);
    glutSwapBuffers();
}
void reshape (int w, int h) {
    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
    glMatrixMode (GL_MODELVIEW);
}
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit(0);
            break;
    }
}
int main (int argc, char **argv) {
    accept_tree();
    inorder(root);
    // OPENGL Drawing functions
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE);
    glutInitWindowSize (1200, 800);
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("A Binary search tree");
    // Register function pointers to the drawing framework
    glutDisplayFunc (display);
    glutIdleFunc (display);
    glutReshapeFunc (reshape);
    glutKeyboardFunc (keyboard);
    glutMainLoop ();
    return 0;
}
