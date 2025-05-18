// rotating_cube.cpp
//

// Copyright <2025> <JAMES C. WILLIAMS>

// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
// associated documentation files(the “Software”), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the
// following conditions :

// The above copyright notice and this permission notice shall be included in all copies or substantial
// portions of the Software.

// THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT
// LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

// 

#include <iostream>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <cmath>
#include <Windows.h>
#include <D:\Downloads\glew-2.1.0\include\GL\glew.h>                // correct for directory
#include <D:\Downloads\glfw-3.4.bin.WIN64\include\GLFW\glfw3.h>     // correct for directory
#include <gl\GL.h>
#include <C:\Users\plati\source\repos\GRAPHICS\GRAPHICS\GRAPHICS.h> // correct for directory

using namespace std;




using namespace std;

int flag = 0;


static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        flag = 1;;
}




int main()
{
    std::cout << "display_check\n\n\n\n";
    double rx = 0., ry = 0., rz = 0.;
    double pi = 3.14159265359;
    double ohm = 0.;
    double x = 0., y = 0., z = 0.;
    
display_setup:
    glfwInit();
    if (!glfwInit())
    {
        std::cout << "GLFW INITIALIZATION FAILURE\n\n";
        glfwTerminate();
        return 0;
    }

    

    GLFWwindow* window = glfwCreateWindow(800, 800, "Rotating Cube", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    if (flag==1)
    {
        goto term;
    }
    goto cont;
term:
    glfwDestroyWindow(window);
    glfwTerminate();
    PostMessage(GetConsoleWindow(), WM_CLOSE, 0, 0);
    return 0;
cont:
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, -100.0f, 100.0f);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // points
    
    PointList P(8), Q(8);

    Point A(-10., -10., -10.);
    P.load(0, A);
    A.load(0, 10.);
    P.load(1, A);
    A.load(1, 10.);
    P.load(2, A);
    A.load(0, -10.);
    P.load(3, A);
    A.load(0, -10.);
    A.load(1, -10.);
    A.load(2, 10.);
    P.load(4, A);
    A.load(0, 10.);
    P.load(5, A);
    A.load(1, 10.);
    P.load(6, A);
    A.load(0, -10.);
    P.load(7, A);
  
    //colors

    Color C1(1., 0., 0., 1.), C2(0., 1., 0., 1.), C3(0., 0., 1., 1.);



    

     
display:
    for (int i = 0; i < 628; i++)
    {
        glBegin(GL_LINE_LOOP);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3d(-50.0, 50.0, 0.0);
        glVertex3d(50.0, 50.0, 0.0);
        glVertex3d(50.0, -50.0, 0.0);
        glVertex3d(-50.0, -50.0, 0.0);
        glEnd();
        
            
        // Transform factors

        rx = .002 * pi * i;
        ry = .004 * pi * i;
        rz = .008 * pi * i;

        RotateX RX(rx);
        RotateY RY(ry);
        RotateZ RZ(rz);

        Transform C;
        C = C * RX;
        C = C * RY;
        C = C * RZ;

        for (int j = 0; j < 8; j++)
        {
            Q.load(j, C(P.access(j)));
        }
        
        glBegin(GL_LINE_LOOP);

        glColor3f(C1.access(0), C1.access(1), C1.access(2));

        glVertex3d(Q.access(0, 0), Q.access(0, 1), Q.access(0, 2));
        glVertex3d(Q.access(1, 0), Q.access(1, 1), Q.access(1, 2));
        glVertex3d(Q.access(2, 0), Q.access(2, 1), Q.access(2, 2));
        glVertex3d(Q.access(3, 0), Q.access(3, 1), Q.access(3, 2));
        glEnd();
        
        glBegin(GL_LINE_LOOP);

        glColor3f(C2.access(0), C2.access(1), C2.access(2));

        glVertex3d(Q.access(4, 0), Q.access(4, 1), Q.access(4, 2));
        glVertex3d(Q.access(5, 0), Q.access(5, 1), Q.access(5, 2));
        glVertex3d(Q.access(6, 0), Q.access(6, 1), Q.access(6, 2));
        glVertex3d(Q.access(7, 0), Q.access(7, 1), Q.access(7, 2));
        glEnd();

        glBegin(GL_LINES);

        glColor3f(C3.access(0), C3.access(1), C3.access(2));

        glVertex3d(Q.access(0, 0), Q.access(0, 1), Q.access(0, 2));
        glVertex3d(Q.access(4, 0), Q.access(4, 1), Q.access(4, 2));
        glVertex3d(Q.access(1, 0), Q.access(1, 1), Q.access(1, 2));
        glVertex3d(Q.access(5, 0), Q.access(5, 1), Q.access(5, 2));
        glVertex3d(Q.access(2, 0), Q.access(2, 1), Q.access(2, 2));
        glVertex3d(Q.access(6, 0), Q.access(6, 1), Q.access(6, 2));
        glVertex3d(Q.access(3, 0), Q.access(3, 1), Q.access(3, 2));
        glVertex3d(Q.access(7, 0), Q.access(7, 1), Q.access(7, 2));

        glEnd();
        

        glFlush();
        glfwSwapBuffers(window);
        Sleep(33);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    goto display;
}
