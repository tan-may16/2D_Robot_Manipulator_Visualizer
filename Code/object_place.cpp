#include <stdio.h>
#include <iostream>
#include "fssimplewindow.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "yspng.h"
#include "object.h"

void Object_place::DrawShelf(double x1,double y1) {

	glColor3ub(212, 175, 55);
	glBegin(GL_QUADS);
	glVertex2d(0, 160);
	glVertex2d(150, 160);
	glVertex2d(150, 170);
	glVertex2d(0, 170);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2d(140, 160);
	glVertex2d(150, 160);
	glVertex2d(150, 150);
	glVertex2d(140, 150);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2d(0, 320);
	glVertex2d(150, 320);
	glVertex2d(150, 330);
	glVertex2d(0, 330);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2d(140, 320);
	glVertex2d(150, 320);
	glVertex2d(150, 300);
	glVertex2d(140, 300);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2d(0, 470);
	glVertex2d(150, 470);
	glVertex2d(150, 480);
	glVertex2d(0, 480);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2d(140, 470);
	glVertex2d(150, 470);
	glVertex2d(150, 450);
	glVertex2d(140, 450);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2d(0, 0);
	glVertex2d(0, 480);
	glVertex2d(10, 480);
	glVertex2d(10, 0);
	glEnd();

	glLineWidth(2);
	glColor3ub(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2d(10, 165);
	glVertex2d(140, 165);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(10, 325);
	glVertex2d(140, 325);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(10, 475);
	glVertex2d(140, 475);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(5, 5);
	glVertex2d(5, 475);
	glEnd();

}

void Object_place::DrawShelf2(double x2, double y2) {
	glColor3ub(212, 175, 55);
	glBegin(GL_QUADS);
	glVertex2d(x2, y2 + 160);
	glVertex2d(x2 - 150, y2 + 160);
	glVertex2d(x2 - 150, y2 + 170);
	glVertex2d(x2, y2 + 170);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2d(x2 - 140, y2 + 160);
	glVertex2d(x2 - 150, y2 + 160);
	glVertex2d(x2 - 150, y2 + 150);
	glVertex2d(x2 - 140, y2 + 150);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2d(x2, y2 + 320);
	glVertex2d(x2 - 150, y2 + 320);
	glVertex2d(x2 - 150, y2 + 330);
	glVertex2d(x2, y2 + 330);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2d(x2 - 140, y2 + 320);
	glVertex2d(x2 - 150, y2 + 320);
	glVertex2d(x2 - 150, y2 + 310);
	glVertex2d(x2 - 140, y2 + 310);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2d(x2, y2 + 470);
	glVertex2d(x2 - 150, y2 + 470);
	glVertex2d(x2 - 150, y2 + 480);
	glVertex2d(x2, y2 + 480);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2d(x2 - 140, y2 + 470);
	glVertex2d(x2 - 150, y2 + 470);
	glVertex2d(x2 - 150, y2 + 460);
	glVertex2d(x2 - 140, y2 + 460);
	glEnd();
	glBegin(GL_QUADS);
	glVertex2d(x2, y2);
	glVertex2d(x2, y2 + 480);
	glVertex2d(x2 - 10, y2 + 480);
	glVertex2d(x2 - 10, y2);
	glEnd();
	glColor3ub(0, 0, 0);
	glBegin(GL_QUADS);
	glVertex2d(880, 700);
	glVertex2d(960, 700);
	glVertex2d(960, 630);
	glVertex2d(880, 630);
	glEnd();

	glLineWidth(2);
	glColor3ub(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2d(x2 - 10, y2 + 165);
	glVertex2d(x2 - 140, y2 + 165);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(x2 - 10, y2 + 325);
	glVertex2d(x2 - 140, y2 + 325);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(x2 - 10, y2 + 475);
	glVertex2d(x2 - 140, y2 + 475);
	glEnd();

	glBegin(GL_LINES);
	glVertex2d(x2 - 5, y2 + 5);
	glVertex2d(x2 - 5, y2 + 475);
	glEnd();
}

void Object_place::DrawShape(char shape,double &x, double &y) {
	if (shape == 1) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		YsRawPngDecoder png;
		png.Decode("spring.png");
		png.Flip();
		glRasterPos2d(x, y);
		if (x < 350) {
			x = x + 10;
		}
		glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
		glDisable(GL_BLEND);
	}
	if (shape == 2) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		YsRawPngDecoder png;
		png.Decode("box.png");
		png.Flip();
		glRasterPos2d(x, y);
		if (x <350) {
			x = x + 10;
		}
		glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
		glDisable(GL_BLEND);
	}
	if (shape == 3) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		YsRawPngDecoder png;
		png.Decode("piston.png");
		png.Flip();
		glRasterPos2d(x, y);
		if (x < 350) {
			x = x + 10;
		}
		glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
		glDisable(GL_BLEND);
		
	}
	if (shape == 4) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		YsRawPngDecoder png;
		png.Decode("gear.png");
		png.Flip();
		glRasterPos2d(x, y);
		if (x < 350) {
			x = x + 10;
		}
		glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
		glDisable(GL_BLEND);
		
	}
	if (shape == 5) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		YsRawPngDecoder png;
		png.Decode("tire.png");
		png.Flip();
		glRasterPos2d(x, y);
		if (x < 350) {
			x = x + 10;
		}
		glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
		glDisable(GL_BLEND);
		
	}
	if (shape == 6) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		YsRawPngDecoder png;
		png.Decode("ball.png");
		png.Flip();
		glRasterPos2d(x, y);
		if (x < 350) {
			x = x + 10;
		}
		glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
		glDisable(GL_BLEND);
		
	}

}

void Object_place::moveShape(int a, int b, int shape)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	YsRawPngDecoder png;
	if (shape == 1)
	{
		png.Decode("spring.png");
		png.Flip();
		int winWid, winHei;
		FsGetWindowSize(winWid, winHei);
		glRasterPos2d(a - 25.0, b + 35.0);
		glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
		glDisable(GL_BLEND);
	}
	if (shape == 2)
	{
		png.Decode("box.png");
		png.Flip();
		int winWid, winHei;
		FsGetWindowSize(winWid, winHei);
		glRasterPos2d(a - 25.0, b + 45.0);
		glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
		glDisable(GL_BLEND);
	}
	if (shape == 3)
	{
		png.Decode("piston.png");
		png.Flip();
		int winWid, winHei;
		FsGetWindowSize(winWid, winHei);
		glRasterPos2d(a - 25.0, b + 48.0);
		glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
		glDisable(GL_BLEND);
	}
	if (shape == 4)
	{
		png.Decode("gear.png");
		png.Flip();
		int winWid, winHei;
		FsGetWindowSize(winWid, winHei);
		glRasterPos2d(a - 25.0, b + 45.0);
		glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
		glDisable(GL_BLEND);
	}
	if (shape == 5)
	{
		png.Decode("tire.png");
		png.Flip();
		int winWid, winHei;
		FsGetWindowSize(winWid, winHei);
		glRasterPos2d(a - 25.0, b + 45.0);
		glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
		glDisable(GL_BLEND);
	}
	if (shape == 6)
	{
		png.Decode("ball.png");
		png.Flip();
		int winWid, winHei;
		FsGetWindowSize(winWid, winHei);
		glRasterPos2d(a - 25.0, b + 45.0);
		glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
		glDisable(GL_BLEND);
	}

}

void Object_place::dropShape(int& c, int& d, int shape)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	YsRawPngDecoder png;
	int a, b1, b2, b3, b4, b5, b6;
	a = 120;
	b3 = 450;
	b2 = 280;
	b1 = 120;
	b4 = 120;
	b5 = 280;
	b6 = 410;
	if (shape == 1 && b1 <= 160)
	{
		png.Decode("spring.png");
	}
	if (shape == 2 && b2 <= 310)
	{
		png.Decode("box.png");
	}
	if (shape == 3 && b3 <= 470)
	{
		png.Decode("piston.png");
	}
	if (shape == 4 && b4 <= 160)
	{
		png.Decode("gear.png");
	}
	if (shape == 5 && b5 <= 310)
	{
		png.Decode("tire.png");
	}
	if (shape == 6 && b6 <= 470)
	{
		png.Decode("ball.png");
	}
	png.Flip();
	glRasterPos2d(c, d);
	int temp = 0;
	if (shape == 1) {
		if (d <= 160) 
		{
			d = d + 5;
		}
	}
	if (shape == 2) {
		if (d <= 315) {
			d = d + 5;
		}
	}
	if (shape == 3) {
		if (d <= 470) {
			d = d + 5;
		}
	}
	if (shape == 4) {
		if (d <= 160) {
			d = d + 5;
		}
	}
	if (shape == 5) {
		if (d <= 315) {
			d = d + 5;
		}
	}
	if (shape == 6) {
		if (d <= 470) {
			d = d + 5;
		}
	}
	glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
	glDisable(GL_BLEND);
}

void Object_place::retrackShape(int& e, int& f, int shape)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	YsRawPngDecoder png;
	int a, a1, a2, a3, a4, a5, a6;
	a = 120;
	a3 = 90;
	a2 = 90;
	a1 = 90;
	a4 = 900;
	a5 = 900;
	a6 = 900;
	if (shape == 1 && a1 <= 90)
	{
		png.Decode("spring.png");
	}
	if (shape == 2 && a2 <= 90)
	{
		png.Decode("box.png");
	}
	if (shape == 3 && a3 <= 90)
	{
		png.Decode("piston.png");
	}
	if (shape == 4 && a4 >= 900)
	{
		png.Decode("gear.png");
	}
	if (shape == 5 && a5 >= 900)
	{
		png.Decode("tire.png");
	}
	if (shape == 6 && a6 >= 900)
	{
		png.Decode("ball.png");
	}
	png.Flip();
	int winWid, winHei;
	FsGetWindowSize(winWid, winHei);
	glRasterPos2d(e, f);
	int temp = 0;
	if (shape == 1) {
		if (e <= 90)
		{
			e = e - 10;
		}
	}
	if (shape == 2) {
		if (e <= 90) {
			e = e - 10;
		}
	}
	if (shape == 3) {
		if (e <= 90) {
			e = e - 10;
		}
	}
	if (shape == 4) {
		if (e >= 900) {
			e = e + 10;
		}
	}
	if (shape == 5) {
		if (e >= 900) {
			e = e + 10;
		}
	}
	if (shape == 6) {
		if (e >= 900) {
			e = e + 10;
		}
	}
	glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
	glDisable(GL_BLEND);
}

void Object_place::dropShape_manual(int& c, int& d, int shape)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	YsRawPngDecoder png;
	int a, b1, b2, b3, b4, b5, b6;
	a = 120;
	b3 = 450;
	b2 = 280;
	b1 = 120;
	b4 = 120;
	b5 = 280;
	b6 = 450;
	if (shape == 1)
	{
		png.Decode("spring.png");
	}
	if (shape == 2 && b2 <= 310)
	{
		png.Decode("final_box_1.png");
	}
	if (shape == 3 && b3 <= 480)
	{
		png.Decode("piston.png");
	}
	if (shape == 4 && b4 <= 160)
	{
		png.Decode("gear.png");
	}
	if (shape == 5 && b5 <= 320)
	{
		png.Decode("tire.png");
	}
	if (shape == 6 && b6 <= 480)
	{
		png.Decode("ball.png");
	}
	png.Flip();
	int winWid, winHei;
	FsGetWindowSize(winWid, winHei);
	glRasterPos2d(c, d);
	int temp = 0;

	if (c < 420 && c >= 100)
	{
		if (d < 600)
		{
			d = d + 5;
		}
	}
	if (c >= 420 && c < 900)
	{
		d = d + 5;
	}
	if (c <= 120)
	{
		if (d >= 0 && d <= 160)
		{
			d = d + 5;
		}
		if (d > 170 && d <= 320)
		{
			d = d + 5;
		}
		if (d >= 330 && d <= 480)
		{
			d = d + 5;
		}
	}
	if (c >= 880)
	{
		if (d >= 0 && d <= 160)
		{
			d = d + 5;
		}
		if (d > 170 && d <= 320)
		{
			d = d + 5;
		}
		if (d >= 330 && d <= 480)
		{
			d = d + 5;
		}
	}
	glDrawPixels(png.wid, png.hei, GL_RGBA, GL_UNSIGNED_BYTE, png.rgba);
	glDisable(GL_BLEND);
}