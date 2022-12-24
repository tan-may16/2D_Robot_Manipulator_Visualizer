#include <string>
#include <stdio.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

#include "yssimplesound.h"
#include "fssimplewindow.h"
#include "yspng.h"
//#include "yspngenc.h"
#include "ysglfontdata.h"
#include "end_effec.h"


void Effect::pick()
{
    robotgap = robotgap - 2;
    
    if (robotgap <= 50)
        robotgap = 50;

   
}


void Effect::drop()
{
    robotgap = robotgap + 2;
    
    if (robotgap >= 80)
        robotgap = 80;
}


void Effect::draw()
{
    glLineWidth(5);
    glBegin(GL_LINE_STRIP);
    glColor3ub(0, 0, 0);
    glVertex2d(robotposx - robotgap / 2, robotposy + 35);
    glVertex2d(robotposx - robotgap / 2, robotposy);
    glVertex2d(robotposx + robotgap / 2, robotposy);
    glVertex2d(robotposx + robotgap / 2, robotposy + 35);
    glEnd();
}


/*int main()
{
    Effec ef;
    
    FsOpenWindow(16, 16, 800, 600, 1);
    
    for (;;)
    {
        FsPollDevice();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto key = FsInkey();

        if (FSKEY_ESC == key)
            break;
        
        ef.set();
        ef.pick();
        // ef.drop();

        FsSwapBuffers();
        glFlush();

        FsSleep(10);
    }

    return 0;
}*/