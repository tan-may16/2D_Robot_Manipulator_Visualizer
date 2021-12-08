#include <stdio.h>
#include <iostream>
#include "fssimplewindow.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "yspng.h"
#include "conveyor.h"

Belt::Belt()
{
	posx = 0;
	posy = 0;
	state = 0;
}


Belt::~Belt()
{
	posx = 0;
	posy = 0;
	state = 0;
}


void Belt::Draw1(float conveyor_y, float conveyor_height)
{
	if (state == 0)
		posy = posy + conveyor_height;
	if (state == 1)
		posy = conveyor_y;
	
	glPointSize(5);
	glColor3ub(180, 0, 0);
	glBegin(GL_POINTS);
	glVertex2d(posx, posy);
	glEnd();

	if (state == 0 && posy > conveyor_y)
		state = 1;
	if (state == 1 && posy <= conveyor_y)
		state = 0;

}







Background::Background()
{
	window_width = 0;
	window_height = 0;

	conveyor_x = 0;
	conveyor_y = 0;
	conveyor_width = 0;
	conveyor_height = 0;

	for (int i = 0; i < num_blocks1; i++)
	{
		blt1[i].posx = 0;
		blt1[i].posy = 0;
		blt1[i].state = 0;
	}

	for (int i = 0; i < num_blocks2; i++)
	{
		blt2[i].posx = 0;
		blt2[i].posy = 0;
		blt2[i].state = 0;
	}
}


Background::~Background()
{
	window_width = 0;
	window_height = 0;

	conveyor_x = 0;
	conveyor_y = 0;
	conveyor_width = 0;
	conveyor_height = 0;

	for (int i = 0; i < num_blocks1; i++)
	{
		blt1[i].posx = 0;
		blt1[i].posy = 0;
		blt1[i].state = 0;
	}

	for (int i = 0; i < num_blocks2; i++)
	{
		blt2[i].posx = 0;
		blt2[i].posy = 0;
		blt2[i].state = 0;
	}
}


void Background::Set_Values()
{
	window_width = 1000;
	window_height = 700;

	conveyor_x = 300;
	conveyor_y = 600;
	conveyor_width = conveyor_x;
	conveyor_height = 30;

	for (int i = 0; i < num_blocks1; i++)
	{
		blt1[i].posx = 4 * i * conveyor_width / 100;
		blt1[i].posy = conveyor_y + 1;
		blt1[i].state = 0;
	}

	for (int i = 0; i < num_blocks2; i++)
	{
		blt2[i].posx = 2 * conveyor_width / 100 + 4 * i * conveyor_width / 100;
		blt2[i].posy = conveyor_y + conveyor_height + 1;
		blt2[i].state = 1;
	}
}


void Background::Draw_Conveyor_Support()
{
	glBegin(GL_QUADS);
	glColor3ub(0, 0, 0);
	glVertex2i(150, conveyor_y + conveyor_height);
	glVertex2i(160, conveyor_y + conveyor_height);
	glVertex2i(160, 700);
	glVertex2i(150, 700);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(0, 0, 0);
	glVertex2i(250, conveyor_y + conveyor_height);
	glVertex2i(260, conveyor_y + conveyor_height);
	glVertex2i(260, 700);
	glVertex2i(250, 700);
	glEnd();
}

void Background::Bin()
{
	glBegin(GL_QUADS);
	glColor3ub(0, 0, 0);
	glVertex2i(430, conveyor_y);
	glVertex2i(430, conveyor_y + conveyor_height);
	glVertex2i(320, conveyor_y + conveyor_height);
	glVertex2i(320, conveyor_y);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(0, 0, 0);
	glVertex2i(335, conveyor_y + conveyor_height);
	glVertex2i(345, conveyor_y + conveyor_height);
	glVertex2i(345, 700);
	glVertex2i(335, 700);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(0, 0, 0);
	glVertex2i(405, conveyor_y + conveyor_height);
	glVertex2i(415, conveyor_y + conveyor_height);
	glVertex2i(415, 700);
	glVertex2i(405, 700);
	glEnd();

}

void Background::Draw_Conveyor_Roller()
{
	double x = 300;
	double y = 615;
	double r = 9;
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < 64; ++i)
	{
		double a = (double)i * Pi / 32.0;
		double c = cos(a);
		double s = sin(a);
		glVertex2d(x + c * r, y + s * r);
	}
	glEnd();
}

void Background::Draw_Conveyor()
{
	glBegin(GL_QUADS);
	glColor3ub(0, 0, 0);
	glVertex2i(conveyor_x, conveyor_y);
	glVertex2i(conveyor_x, conveyor_y + conveyor_height);
	glVertex2i(conveyor_x - conveyor_width, conveyor_y + conveyor_height);
	glVertex2i(conveyor_x - conveyor_width, conveyor_y);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(255, 255, 255);
	glVertex2i(conveyor_x, conveyor_y + 5);
	glVertex2i(conveyor_x, conveyor_y + 10);
	glVertex2i(conveyor_x - conveyor_width, conveyor_y + 10);
	glVertex2i(conveyor_x - conveyor_width, conveyor_y + 5);
	glEnd();

	glBegin(GL_QUADS);
	glColor3ub(255, 255, 255);
	glVertex2i(conveyor_x, conveyor_y + 20);
	glVertex2i(conveyor_x, conveyor_y + 25);
	glVertex2i(conveyor_x - conveyor_width, conveyor_y + 25);
	glVertex2i(conveyor_x - conveyor_width, conveyor_y + 20);
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3ub(0, 0, 0);
	double x = 300;
	double y = 615;
	double r = 15;
	for (int i = 0; i < 64; ++i)
	{
		double a = (double)i * Pi / 32.0;
		double c = cos(a);
		double s = sin(a);
		glVertex2d(x + c * r, y + s * r);
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glColor3ub(255, 255, 255);
	double r2 = 7;
	for (int i = 0; i < 64; ++i)
	{
		double a = (double)i * Pi / 32.0;
		double c = cos(a);
		double s = sin(a);
		glVertex2d(x + c * r2, y + s * r2);
	}
	glEnd();
}

void Background::Draw()
{
	//Set_Values();
	for (int i = 0; i < num_blocks1; i++)
	{
		blt1[i].Draw1(conveyor_y, conveyor_height);
	}

	for (int i = 0; i < num_blocks2; i++)
	{
		blt2[i].Draw1(conveyor_y, conveyor_height);
	}

	Draw_Conveyor_Support();
	Draw_Conveyor();
	Draw_Conveyor_Roller();
	Bin();
}



//int main()
//{
//	Background bkrg;
//	Belt blt1[num_blocks1];
//	Belt blt2[num_blocks2];
//	bkrg.Set_Values();
//
//	FsOpenWindow(32, 32, bkrg.window_width, bkrg.window_height, 1);
//	bkrg.Set_Values();
//
//	/*for (;;)
//	{
//		FsPollDevice();
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		auto key = FsInkey();
//		if (FSKEY_ESC == key)
//		{
//			break;
//		}
//		
//		bkrg.Draw();
//		
//		FsSwapBuffers();
//		glFlush();
//		FsSleep(100);
//	}*/
//
//	return 0;
//}
