//This file is Michael's testing code.  Use it if you'd like to contribute
//to the non GLUT_Plotter-based code.

#include "functions.h"
#include <iostream>
#include <string>
#include <sstream>


using namespace std;

int main (int argc, char **argv)
{
    string userresult = "";
    while(userresult != "exit")
    {
        userresult = userinput<int>();
        if(userresult == "display")
        {
            glutInit (&argc, argv);
            glutInitDisplayMode (GLUT_DOUBLE);
            glutInitWindowSize (1200, 800);
            glutInitWindowPosition (0, 0);
            glutCreateWindow ("Visualization");
            glutDisplayFunc (display);
            glutIdleFunc (display);
            glutReshapeFunc (redraw);
            glutKeyboardFunc (keychecker);
            glutMainLoop ();
        }
    }
    cout << "Finished all tasks." << endl;
    return 0;
}
