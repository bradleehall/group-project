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

extern SplayNode<int> *root = NULL;

template <class Base>
void inorder(SplayNode<Base> *target)
{
    if(target)
    {
        inorder(target->left);
        cout << target->value << " ";
        inorder(target->right);
    }
}

template <class Base>
void preorder(SplayNode<Base> *target)
{
    if(target)
    {
        cout << target->value << " ";
        preorder(target->left);
        preorder(target->right);
    }
}

template <class Base>
void postorder(SplayNode<Base> *target)
{
    if(target)
    {
        postorder(target->left);
        postorder(target->right);
        cout << target->value << " ";
    }
}

template <class Base>
SplayNode<Base>* createnode(const Base &initval)
{
    SplayNode<Base> *temp = new SplayNode<Base>;
    if(!temp)
    {
        cerr << "fatal: out of memory" << endl;
        exit(1);
    }
    temp->value = initval;
    temp->left = temp->right = NULL;
    return temp;
}

template <class Base>
SplayNode<Base>* right_rotate(SplayNode<Base> *target)
{
    SplayNode<Base> *temp = target->left;
    target->left = temp->right;
    temp->right = target;
    return temp;
}

template <class Base>
SplayNode<Base>* left_rotate(SplayNode<Base> *target)
{
    SplayNode<Base> *temp = target->right;
    target->right = temp->left;
    temp->left = target;
    return temp;
}

template <class Base>
SplayNode<Base>* access(const Base &accessval, SplayNode<Base> *target)
{
    if(!(target))
    {
        return NULL;
    }
    SplayNode<Base> searcher;
    searcher.left = searcher.right = NULL;
    SplayNode<Base> *leftdepth = &searcher;
    SplayNode<Base> *rightdepth = &searcher;
    while(true)
    {
        if(accessval < target->value)
        {
            if(!(target->left))
            {
                break;
            }
            if(accessval < target->left->value)
            {
                target = right_rotate(target);
                if(!(target->left))
                {
                    break;
                }
            }
            rightdepth->left = target;
            rightdepth = rightdepth->left;
            target = target->left;
            rightdepth->left = NULL;
        }
        else if(accessval > target->value)
        {
            if(!(target->right))
            {
                break;
            }
            if(accessval > target->right->value)
            {
                target = left_rotate(target);
                if(!(target->right))
                {
                    break;
                }
            }
            leftdepth->right = target;
            leftdepth = leftdepth->right;
            target = target->right;
            leftdepth->right = NULL;
        }
        else
        {
            break;
        }
    }
    leftdepth->right = target->left;
    rightdepth->left = target->right;
    target->left = searcher.right;
    target->right = searcher.left;
    return target;
}

template <class Base>
SplayNode<Base>* insert(const Base &valinsert, SplayNode<Base> *target)
{
    if(!target)
    {
        target = createnode(valinsert);
        return target;
    }
    SplayNode<Base> *temp = target;
    while(true)
    {
        if(valinsert < temp->value)
        {
            if(temp->left)
            {
                temp = temp->left;
            }
            else
            {
                temp->left = createnode(valinsert);
                access(valinsert, temp->left);
                return target;
            }
        }
        else if(valinsert > temp->value)
        {
            if(temp->right)
            {
                temp = temp->right;
            }
            else
            {
                temp->right = createnode(valinsert);
                access(valinsert, temp->right);
                return target;
            }
        }
        else
        {
            cout << "warning: insert: " << valinsert << " already in tree"
            << endl;
            return target;
        }
    }
}

template <class Base>
SplayNode<Base>* remove(const Base &valremove, SplayNode<Base> *target)
{
    SplayNode<Base> *temp;
    if(!target)
    {
        cout << "warning: remove: empty tree" << endl;
        return NULL;
    }
    target = access(valremove, target);
    if(valremove != target->value)
    {
        cout << "warning: remove: unable to find " << valremove << endl;
        return target;
    }
    else
    {
        if(!(target->left))
        {
            temp = target;
            target = target->right;
        }
        else
        {
            temp = target;
            target = access(valremove, target->left);
            target->right = temp->right;
        }
        delete temp;
        return target;
    }
}

void reverse(char *target, int length)
{
    int finish = length - 1;
    int init = 0;
    while (init < finish)
    {
        swap(*(target+init), *(target+finish));
        init++;
        finish--;
    }
}

char* itoa(int num, char *target, int radix)
{
    int ticker = 0;
    bool neg = false;

    if (!num)
    {
        target[ticker++] = '0';
        target[ticker] = '\0';
        return target;
    }
    if (num < 0 && radix == 10)
    {
        num = -num;
        neg = true;
    }
    while(num)
    {
        int temp = num % radix;
        target[ticker++] = (temp > 9)? (temp-10) + 'a' : temp + '0';
        num = num/radix;
    }
    if (neg)
    {
        target[ticker++] = '-';
    }
    target[ticker] = '\0';
    reverse(target, ticker);
    return target;
}

//replace this with insert()
/*
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
*/

//retaining this function in case I screw something up
/*
void accept_tree(){
    int n;
    cout << "\nCREATING BST: (enter 0 to finish)\n";
    while(1) {
        fflush(stdin);
        cout<<"\nEnter node value: ";
        cin>>n;
        if(!n)
        {
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
*/

template <class Base>
string userinput()
{
    cout << endl << "What would you like to do? ";
    //fflush(stdin);
    //cin.clear();
    string userstring, usercommand;
    Base userargument;
    do
    {
        getline(cin, userstring);
    }while(userstring == "");
    istringstream parser(userstring);
    parser >> usercommand;
    //cout << "Executing command " << usercommand << endl;
    if(usercommand == "exit")
    {
        cout << "Exiting..." << endl;
        return "exit";
    }
    else if(usercommand == "help")
    {
        cout << "insert x: place a node containing x into the tree" << endl
        << "remove y: remove the node containing y from the tree" << endl
        << "access z: modify the tree as if the node containing z had been"
        << "accessed, but do not do anything else" << endl
        << "display: display a graphical representation of the tree" << endl
        << "help: display this help" << endl
        << "exit: exit the program" << endl;
    }
    else if(usercommand == "insert")
    {
        if(!(parser >> userargument))
        {
            cout << "What would you like to insert? ";
            cin >> userargument;
        }
        cout << "Inserting " << userargument << "...";
        root = insert(userargument, root);
        cout << "done." << endl;
        return "insert";
    }
    else if(usercommand == "remove")
    {
        if(!(parser >> userargument))
        {
            cout << "What would you like to remove? ";
            cin >> userargument;
        }
        cout << "Removing " << userargument << "...";
        root = remove(userargument, root);
        cout << "done." << endl;
        return "remove";
    }
    else if(usercommand == "access")
    {
        if(!(parser >> userargument))
        {
            cout << "What would you like to access? ";
            cin >> userargument;
        }
        cout << "Accessing " << userargument << "...";
        root = access(userargument, root);
        cout << "done." << endl;
        return "access";
    }
    else if(usercommand == "print")
    {
        string printtype;
        if(!(parser >> printtype))
        {
            do
            {
                cout << "How would you like to print the tree? ";
                cin >> printtype;
                if(printtype != "preorder" && printtype != "inorder"
                   && printtype != "postorder")
                {
                    cout << "warning: print: invalid print type, please select"
                    << " from preorder, inorder, or postorder" << endl;
                }
            }while(printtype != "preorder" && printtype != "inorder"
                   && printtype != "postorder");
        }
        if(printtype == "preorder")
        {
            preorder(root);
        }
        else if(printtype == "inorder")
        {
            inorder(root);
        }
        else
        {
            postorder(root);
        }
    }
    else if(usercommand == "display")
    {
        cout << "Displaying tree..." << endl;
        return "display";
    }
    else
    {
        cout << "error: unknown command " << usercommand << endl
        << "Type 'help' for a list of commands." << endl;
    }
}

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

template <class Base>
void drawNode(SplayNode<Base> *t_root, float x1, float y1, int level)
{
    if (!t_root)
    {
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
    itoa(t_root->value,buff,10);
    draw_text(buff,x1,y1);
    if(t_root->left)
    {
        // Draw the Left circle
        float angle = left_angle - level*angle_change;
        double radian = angle*3.14/180;
        float m = (double)tan((double)radian);
        float x2 = x1 + branch_length * sin((double) radian);
        float y2 = y1 + branch_length * cos((double) radian);
        draw_line(x1,y1,x2,y2);
        drawNode(t_root->left,x2,y2,level+1);
    }
    if(t_root->right)
    {
        // Draw the Right circle
        float angle = right_angle + level*angle_change;
        float radian = angle*3.14/180;
        float m = (double)tan((double)radian);
        float x2 = x1 + branch_length * sin((double) radian);
        float y2 = y1 + branch_length * cos((double) radian);
        draw_line(x1,y1,x2,y2);
        drawNode(t_root->right,x2,y2,level+1);
    }
}


void display()
{
    glClearColor (0.0,0.0,0.0,1.0);
    glClear (GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0,10,-30);
    glColor3f(1,1,1);
    drawNode(root,0,0,0);
    glutSwapBuffers();
}

void reshape (int w, int h)
{
    glViewport (0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective (60, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
    glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 27:
            exit (0);
            break;
    }
}

int main (int argc, char **argv)
{
    string userresult = "";
    while(userresult != "exit")
    {
        userresult = userinput<int>();
        if(userresult == "display")
        {
            inorder(root);
            // OPENGL Drawing functions
            glutInit (&argc, argv);
            glutInitDisplayMode (GLUT_DOUBLE);
            glutInitWindowSize (1200, 800);
            glutInitWindowPosition (0, 0);
            glutCreateWindow ("Visualization");
            // Register function pointers to the drawing framework
            glutDisplayFunc (display);
            glutIdleFunc (display);
            glutReshapeFunc (reshape);
            glutKeyboardFunc (keyboard);
            glutMainLoop ();
        }
    }
    cout << "Finished all tasks." << endl;
    return 0;
}
