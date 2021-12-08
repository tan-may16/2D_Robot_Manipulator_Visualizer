#include <stdio.h>
#include <iostream>
#include "fssimplewindow.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "yspng.h"
#include "object.h"
#include "start.h"
#include "ysglfontdata.h"
#include "yssimplesound.h"
#include <vector>

int Start::startInterface(int &A, int &M)
{
	int lb, mb, rb, mx, my;
	int choice = 0;
	YsRawPngDecoder bg;
	bg.Decode("background_ARM.png");
	bg.Flip();
	YsRawPngDecoder png;
	png.Decode("Title.png");
	png.Flip();

	YsSoundPlayer player;
	YsSoundPlayer::SoundData click;
	char clickS[11] = "button.wav"; 
	if (YSOK != click.LoadWav(clickS))
	{
		printf("Error -> Cannot load hitting_sound.wav!\n");
	}

	player.Start();
	FsChangeToProgramDir();

	for (;;)
	{
		auto key = FsInkey();
		FsPollDevice();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glRasterPos2d(0, 699);
		glDrawPixels(bg.wid, bg.hei, GL_RGBA, GL_UNSIGNED_BYTE, bg.rgba);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glRasterPos2d(450, 100);
		glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
		glDisable(GL_BLEND);

		// Automatic Button
		for (int i = 0; i < 10; ++i)
		{
			glBegin(GL_QUADS);
			glColor3f(0.5, 0.5, 0.5);
			glVertex2i(210 + i, 325 + i);
			glVertex2i(210 + 130 + i, 325 + i);
			glVertex2i(210 + 130 + i, 325 + 40 + i);
			glVertex2i(210 + i, 325 + 40 + i);
		}
		glBegin(GL_QUADS);
		glColor3f(1.0, 0.0, 0.0);
		glVertex2i(210 + 10, 325 + 10);
		glVertex2i(210 + 130 + 10, 325 + 10);
		glVertex2i(210 + 130 + 10, 325 + 40 + 10);
		glVertex2i(210 + 10, 325 + 40 + 10);
		glEnd();

		glColor3f(0.0, 0.0, 0.0);
		glRasterPos2i(235, 360);
		YsGlDrawFontBitmap16x24("Manual");

		// Manual Button
		for (int i = 0; i < 10; ++i)
		{
			glBegin(GL_QUADS);
			glColor3f(0.5, 0.5, 0.5);
			glVertex2i(850 + i - 140, 325 + i);
			glVertex2i(850 + 130 + i - 140, 325 + i);
			glVertex2i(850 + 130 + i - 140, 325 + 40 + i);
			glVertex2i(850 + i - 140, 325 + 40 + i);
		}
		glBegin(GL_QUADS);
		glColor3f(1.0, 0.0, 0.0);
		glVertex2i(850 + 10 - 140, 325 + 10);
		glVertex2i(850 + 130 + 10 - 140, 325 + 10);
		glVertex2i(850 + 130 + 10 - 140, 325 + 40 + 10);
		glVertex2i(850 + 10 - 140, 325 + 40 + 10);
		glEnd();

		glColor3f(0.0, 0.0, 0.0);
		glRasterPos2i(885 - 140, 360);
		YsGlDrawFontBitmap16x24("Auto");

		// Choice Selection
		FsGetMouseEvent(lb, mb, rb, mx, my);
		if (FSKEY_LEFT == key)
		{
			player.PlayOneShot(click);
			choice = 1;
		}
		if (FSKEY_RIGHT == key)
		{
			player.PlayOneShot(click);
			choice = 2;
		}
		if (choice == 1)
		{
			glLineWidth(5);
			glBegin(GL_LINES);
			glColor3f(0.0, 1.0, 0.0);
			glVertex2i(210, 325);
			glVertex2i(350, 325);
			glVertex2i(350, 325);
			glVertex2i(350, 375);
			glVertex2i(350, 375);
			glVertex2i(210, 375);
			glVertex2i(210, 375);
			glVertex2i(210, 325);
			glEnd();
		}
		if (choice == 2)
		{
			glLineWidth(5);
			glBegin(GL_LINES);
			glColor3f(0.0, 1.0, 0.0);
			glVertex2i(850 - 140, 325);
			glVertex2i(990 - 140, 325);
			glVertex2i(990 - 140, 325);
			glVertex2i(990 - 140, 375);
			glVertex2i(990 - 140, 375);
			glVertex2i(850 - 140, 375);
			glVertex2i(850 - 140, 375);
			glVertex2i(850 - 140, 325);
			glEnd();
		}
		if (FSKEY_ENTER == key && choice == 1)
		{
			M = 1;
			A = 0;
			return 1;
		}
		if (FSKEY_ENTER == key && choice == 2)
		{
			M = 0;
			A = 1;
			return 1;
		}
		if (FSKEY_ESC == key)
		{
			return 0;
		}
		FsSleep(1);
		FsSwapBuffers();
	}
	return 0;
}
