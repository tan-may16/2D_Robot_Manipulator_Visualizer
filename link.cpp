#include <stdio.h>
#include <iostream>
#include "fssimplewindow.h"
#include <time.h>
#include <math.h>
#include "link.h"
#include <stdlib.h>
#include <iostream>
#include "yspng.h"
#include "object.h"
#include "start.h"
#include "ysglfontdata.h"
#include "yssimplesound.h"

using namespace std;
Effect	ef;
double dt = 1.0;
vector<Joint> joints;

ArmIK::ArmIK()
{
	char armS[22] = "robotic_arm_sound.wav";

	if (YSOK != arm.LoadWav(armS))
	{
		printf("Error -> Cannot load robotic_arm_sound.wav!\n");
	}
	char armS1[23] = "robotic_arm_sound1.wav";

	if (YSOK != arm2.LoadWav(armS1))
	{
		printf("Error -> Cannot load robotic_arm_sound.wav!\n");
	}

	char popsound[18] = "hitting_sound.wav";
	char bg[21] = "background_sound.wav";

	if (YSOK != pop.LoadWav(popsound))
	{
		printf("Error -> Cannot load hitting_sound.wav!\n");
	}
	if (YSOK != backg.LoadWav(bg))
	{
		printf("Error -> Cannot load background_sound.wav!\n");
	}
}

void ArmIK::AddJoint(float len)
{
	Joint newJoint = { 0 };
	newJoint.len = len;
	joints.push_back(newJoint);
}

void ArmIK::ForwardKinematics(int startJoint)
{
	joints[startJoint].globalAngle = (startJoint > 0 ? joints[startJoint - 1].globalAngle : 0) + joints[startJoint].localAngle;

	joints[0].len = 400.0;
	joints[1].len = 300.0;
	joints[2].len = 300.0;


	for (int i = startJoint + 1; i < joints.size(); i++)
	{
		joints[i].globalAngle = joints[i - 1].globalAngle + joints[i].localAngle;
		joints[i].xpos = joints[i - 1].xpos + sin(joints[i - 1].globalAngle) * joints[i - 1].len;
		joints[i].ypos = joints[i - 1].ypos + cos(joints[i - 1].globalAngle) * joints[i - 1].len;
		//player.PlayOneShot(arm);
	}

	xEnd = joints[joints.size() - 1].xpos + sin(joints[joints.size() - 1].globalAngle) * joints[joints.size() - 1].len;
	yEnd = joints[joints.size() - 1].ypos + cos(joints[joints.size() - 1].globalAngle) * joints[joints.size() - 1].len;
}

void ArmIK::InverseKinematics(float xTarget, float yTarget, int steps)
{
	for (int i = 0; i < steps; i++)
	{
		joints[joints.size() - 1].localAngle = atan2(xTarget - joints[joints.size() - 1].xpos, yTarget - joints[joints.size() - 1].ypos) - joints[joints.size() - 2].globalAngle;
		this->ForwardKinematics(joints.size() - 2);
		for (int i = joints.size() - 2; i > 0; i--) {
			this->ForwardKinematics(i - 1);
			float currentAngle = atan2(xEnd - joints[i].xpos, yEnd - joints[i].ypos);
			float targetAngle = atan2(xTarget - joints[i].xpos, yTarget - joints[i].ypos);
			joints[i].globalAngle -= currentAngle - targetAngle;
			joints[i].localAngle = joints[i].globalAngle - joints[i - 1].globalAngle;
		}
		this->ForwardKinematics(0);
		float currentAngle = atan2(xEnd, yEnd);
		float targetAngle = atan2(xTarget, yTarget);
		joints[0].localAngle -= currentAngle - targetAngle;
	}
	this->ForwardKinematics(0);
	joints[joints.size() - 1].localAngle = atan2(xTarget - joints[joints.size() - 1].xpos, yTarget - joints[joints.size() - 1].ypos) - joints[joints.size() - 2].globalAngle;
}

void drawCircle(float x, float y, float r, float color[])
{
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(color[0], color[1], color[2]);
	for (int i = 0; i < 64; ++i)
	{
		double a = (double)i * Pi / 32.0;
		double c = cos(a);
		double s = sin(a);
		glVertex2d(x + c * r, y + s * r);
	}
	glEnd();
}

int ArmIK::objectPick1(int& mx, int& my, time_t t1, time_t t2, int& state, int a, int b, int& keystate)
{
	Object_place spring;
	if (state == 1)
	{

		if (t2 == 2.0 * dt)
		{
			mx = 230;
			my = 160;
			player.PlayOneShot(arm);
		}
		if (t2 == 3.0 * dt || t2 == 4.0 * dt)
		{
			mx = 375;
			my = 557;
			ef.pick();
			player.PlayOneShot(arm);

		}
		if (t2 == 5.0 * dt)
		{
			mx = 180;
			my = 550;
			player.PlayOneShot(arm);
		}
		if (t2 == 6.0 * dt)
		{
			mx = 230;
			my = 10;
			player.PlayOneShot(arm);
		}
		if (t2 == 7.0 * dt || t2 == dt * 8.0)
		{
			mx = 110;
			my = 90;
			ef.drop();
			player.PlayOneShot(arm);
			if (t2 == dt * 8.0 && soundState == 0)
			{
				player.PlayOneShot(pop);
				soundState = 1;
			}
		}
		if (t2 == 10.0 * dt)
		{
			mx = 500;
			my = 350;
			player.PlayOneShot(arm);
			state = 0;
			keystate = 0;
			soundState = 0;
			return 0;
		}
		if (t2 > 3.0 && t2 <= 7.0 * dt)
		{
			spring.moveShape(a, b, 1);
		}
	}
	return 0;
}

int ArmIK::objectPick2(int& mx, int& my, time_t& t1, time_t t2, int& state, int a, int b, int& keystate)
{
	Object_place box;
	if (state == 2)
	{
		if (t2 == 2.0 * dt)
		{
			mx = 230;
			my = 160;
			player.PlayOneShot(arm);
		}
		if (t2 == 3.0 * dt || t2 == 4.0 * dt)
		{
			mx = 375;
			my = 553;
			ef.pick();
			if (t2 == 3.0)
			{
				player.PlayOneShot(arm);
			}
		}
		if (t2 == 5.0 * dt)
		{
			mx = 180;
			my = 550;
			player.PlayOneShot(arm);
		}
		if (t2 == 6.0 * dt)
		{
			mx = 230;
			my = 180;
			player.PlayOneShot(arm);
		}
		if (t2 == 7.0 * dt || t2 == dt * 8.0)
		{
			mx = 110;
			my = 250;
			ef.drop();
			player.PlayOneShot(arm);
			if (t2 == dt * 8.0 && soundState == 0)
			{
				player.PlayOneShot(pop);
				soundState = 1;
			}
		}
		if (t2 == 10.0 * dt)
		{
			mx = 500;
			my = 350;
			player.PlayOneShot(arm);
			state = 0;
			keystate = 0;
			soundState = 0;
			return 0;
		}
		if (t2 > 3.0 && t2 <= 7.0 * dt)
		{
			box.moveShape(a, b, 2);
			if (t2 == dt * 2.0 && soundState == 0)
			{
				player.PlayOneShot(arm);
				soundState = 1;
			}
		}
	}
	return 0;
}

int ArmIK::objectPick3(int& mx, int& my, time_t& t1, time_t t2, int& state, int a, int b, int& keystate)
{
	Object_place piston;

	if (state == 3)
	{
		soundState = 0;
		if (t2 == 2 * dt)
		{
			mx = 230;
			my = 160;
			player.PlayOneShot(arm);
		}
		if (t2 == 3.0 * dt || t2 == 4 * dt)
		{
			mx = 375;
			my = 548;
			ef.pick();
			player.PlayOneShot(arm);

		}
		if (t2 == 5 * dt)
		{
			mx = 180;
			my = 550;
			player.PlayOneShot(arm);
		}
		if (t2 == 6 * dt)
		{
			mx = 230;
			my = 340;
			player.PlayOneShot(arm);
		}
		if (t2 == 7.0 * dt || t2 == dt * 8.0)
		{
			mx = 110;
			my = 410;
			ef.drop();
			player.PlayOneShot(arm);
			if (t2 == dt * 8.0 && soundState == 0)
			{
				player.PlayOneShot(pop);
				soundState = 1;
			}
		}
		if (t2 == 9.0 * dt)
		{
			mx = 500;
			my = 350;
			player.PlayOneShot(arm);
			state = 0;
			keystate = 0;
			soundState = 0;
			return 0;
		}
		if (t2 > 3.0 && t2 <= 7.0 * dt)
		{
			piston.moveShape(a, b, 3);
		}
	}
	return 0;
}

int ArmIK::objectPick4(int& mx, int& my, time_t& t1, time_t t2, int& state, int a, int b, int& keystate)
{
	Object_place gear;

	if (state == 4)
	{
		if (t2 == dt * 1.0)
		{
			mx = 500;
			my = 350;
			player.PlayOneShot(arm);
		}
		if (t2 == dt * 2.0)
		{
			mx = 230;
			my = 160;
			player.PlayOneShot(arm);
		}
		if (t2 == dt * 3.0 || t2 == dt * 4.0)
		{
			mx = 375;
			my = 548;
			ef.pick();
			player.PlayOneShot(arm);
		}
		if (t2 == dt * 5.0)
		{
			mx = 180;
			my = 550;
			player.PlayOneShot(arm);
		}
		if (t2 == dt * 6.0)
		{
			mx = 230;
			my = 300;
			player.PlayOneShot(arm);
		}
		if (t2 == dt * 7.0)
		{
			mx = 500;
			my = 600;
			player.PlayOneShot(arm);
		}
		if (t2 == dt * 8.0)
		{
			mx = 500;
			my = 500;
			player.PlayOneShot(arm);
		}
		if (t2 == dt * 10.0)
		{
			mx = 600;
			my = 50;
			player.PlayOneShot(arm);
		}
		if (t2 == dt * 12.0)
		{
			mx = 800;
			my = 10;
			player.PlayOneShot(arm);
		}
		if (t2 == dt * 13.0 || t2 == dt * 14.0)
		{
			mx = 930;
			my = 90;
			ef.drop();
			player.PlayOneShot(arm);
			if (t2 == dt * 14.0 && soundState == 0)
			{
				player.PlayOneShot(pop);
				soundState = 1;
			}
		}
		if (t2 == dt * 16.0 || t2 == dt * 17.0)
		{
			mx = 140;
			my = 10;
			player.PlayOneShot(arm);
		}
		if (t2 == dt * 18.0)
		{
			mx = 500;
			my = 350;
			player.PlayOneShot(arm);
			state = 0;
			keystate = 0;
			soundState = 0;
			return 0;
		}
		if (t2 > 3.0 * dt && t2 < 14.0 * dt)
		{
			gear.moveShape(a, b, 4);
		}
	}
	return 0;
}

int ArmIK::objectPick5(int& mx, int& my, time_t& t1, time_t t2, int& state, int a, int b, int& keystate)
{
	Object_place tire;

	if (state == 5)
	{
		if (t2 == 0.0)
		{
			mx = 500;
			my = 350;
			player.PlayOneShot(arm);
		}
		if (t2 == 1.0)
		{
			mx = 230;
			my = 160;
			player.PlayOneShot(arm);
		}
		if (t2 == 2.0 || t2 == 3)
		{
			mx = 375;
			my = 548;
			ef.pick();
			player.PlayOneShot(arm);
		}
		if (t2 == 4.0)
		{
			mx = 180;
			my = 550;
			player.PlayOneShot(arm);
		}
		if (t2 == 5.0)
		{
			mx = 230;
			my = 300;
			player.PlayOneShot(arm);
		}
		if (t2 == 6.0)
		{
			mx = 500;
			my = 600;
			player.PlayOneShot(arm);
		}
		if (t2 == 7.0)
		{
			mx = 500;
			my = 500;
			player.PlayOneShot(arm);
		}
		if (t2 == 8.0)
		{
			mx = 600;
			my = 50;
			player.PlayOneShot(arm);
		}
		if (t2 == 9.0 || t2 == 10.0)
		{
			mx = 930;
			my = 250;
			ef.drop();
			player.PlayOneShot(arm);
			if (t2 == dt * 10.0 && soundState == 0)
			{
				player.PlayOneShot(pop);
				soundState = 1;
			}
		}
		if (t2 == 12.0 || t2 == 13.0)
		{
			mx = 140;
			my = 10;
			player.PlayOneShot(arm);
		}
		if (t2 == 14.0)
		{
			mx = 500;
			my = 350;
			player.PlayOneShot(arm);
			state = 0;
			keystate = 0;
			soundState = 0;
		}
		if (t2 > 2.0 && t2 < 10.0)
		{
			tire.moveShape(a, b, 5);
		}
	}
	return 0;
}

int ArmIK::objectPick6(int& mx, int& my, time_t& t1, time_t t2, int& state, int a, int b, int& keystate)
{
	Object_place football;

	if (state == 6)
	{
		if (t2 == dt * 0.0)
		{
			mx = 500;
			my = 350;
			player.PlayOneShot(arm);
		}
		if (t2 == dt * 1.0)
		{
			mx = 230;
			my = 160;
			player.PlayOneShot(arm);
		}
		if (t2 == dt * 2.0 || t2 == dt * 3.0)
		{
			mx = 375;
			my = 548;
			ef.pick();
			player.PlayOneShot(arm);
		}
		if (t2 == dt * 4.0)
		{
			mx = 180;
			my = 550;
			player.PlayOneShot(arm);
		}
		if (t2 == dt * 5.0)
		{
			mx = 230;
			my = 300;
			player.PlayOneShot(arm);
		}
		if (t2 == dt * 6.0)
		{
			mx = 500;
			my = 600;
			player.PlayOneShot(arm);
		}
		if (t2 == dt * 7.0)
		{
			mx = 500;
			my = 500;
			player.PlayOneShot(arm);
		}
		if (t2 == dt * 8.0)
		{
			mx = 600;
			my = 300;
			player.PlayOneShot(arm);
		}
		if (t2 == dt * 9.0 || t2 == dt * 10.0)
		{
			mx = 930;
			my = 400;
			ef.drop();
			player.PlayOneShot(arm);
			if (t2 == dt * 8.0 && soundState == 0)
			{
				player.PlayOneShot(pop);
				soundState = 1;
			}
		}
		if (t2 == dt * 12.0 || t2 == dt * 13.0)
		{
			mx = 140;
			my = 10;
			player.PlayOneShot(arm);
		}
		if (t2 == dt * 14.0)
		{
			mx = 500;
			my = 350;
			player.PlayOneShot(arm);
			state = 0;
			keystate = 0;
			soundState = 0;
			return 0;
		}
		if (t2 > 3.0 * dt && t2 < 10.0 * dt)
		{
			football.moveShape(a, b + 10, 6);
		}
	}
	return 0;
}

int ArmIK::objectPick7(int& mx, int& my, time_t& t1, time_t t2, int& state, int a, int b, int& keystate)
{
	if (state == 7)
	{
		if (t2 == dt * 1.0 || t2 == dt * 2.0)
		{
			mx = 140;
			my = 10;
			player.PlayOneShot(arm);
		}
		if (t2 == dt * 3.0)
		{
			mx = 500;
			my = 350;
			player.PlayOneShot(arm);
		}
	}
	return 0;
}

void ArmIK::Automatic(int& A, int& M)
{
	glShadeModel(GL_SMOOTH);
	player.Start();
	FsChangeToProgramDir();


	ef.robotgap = 80;
	int shape = -1;
	Background bkrg;
	Belt blt1[num_blocks1];
	Belt blt2[num_blocks2];
	bkrg.Set_Values();
	time_t t1, t2;
	Object_place obj;
	int grab_state = 0;
	int k1, k2;
	int draw_state = 1;
	int p = 1;

	int keystate = 0;
	int links = 3;
	for (int i = 0; i < links; ++i)
	{
		AddJoint(1700.0 / links);
	}

	int a, b, state;
	a = 140;
	b = 10;
	state = 0;
	int lb, mb, rb, mx, my;
	mx = 100;
	my = 70;
	time(&t1);
	time(&t2);
	int stateswitch = 0;
	int a_p, b_p, a_s, a_b, b_s, b_b, a_g, b_g, a_f, b_f, a_t, b_t;

	player.PlayBackground(backg);
	// Background
	YsRawPngDecoder bg1;
	bg1.Decode("background.png");
	bg1.Flip();

	for (;;)
	{
		printf("%d %d \n", A, M);
		auto key = FsInkey();
		FsPollDevice();

		if (FSKEY_ESC == key)
		{
			break;
		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glRasterPos2d(0, 699);
		glDrawPixels(bg1.wid, bg1.hei, GL_RGBA, GL_UNSIGNED_BYTE, bg1.rgba);

		if (keystate == 0 && A == 1)
		{
			if (FSKEY_S == key)
			{
				state = 1;
				shape = 1;
				time(&t1);
				obj.x = 0.0;
				obj.y = 600.0;
				keystate = 1;
				a_s = 90;
				b_s = 120;
			}
			if (FSKEY_B == key)
			{
				state = 2;
				time(&t1);
				shape = 2;
				obj.x = 0.0;
				obj.y = 600.0;
				keystate = 1;
				a_b = 90;
				b_b = 280;
			}
			if (FSKEY_P == key)
			{
				state = 3;
				time(&t1);
				shape = 3;
				obj.x = 0.0;
				obj.y = 600.0;
				keystate = 1;
				a_p = 90;
				b_p = 440;
			}
			if (FSKEY_G == key)
			{
				state = 4;
				time(&t1);
				shape = 4;
				obj.x = 0.0;
				obj.y = 600.0;
				keystate = 1;
				a_g = 900;
				b_g = 120;
			}
			if (FSKEY_T == key)
			{
				state = 5;
				time(&t1);
				shape = 5;
				obj.x = 0.0;
				obj.y = 600.0;
				keystate = 1;
				a_t = 900;
				b_t = 280;
			}
			if (FSKEY_F == key)
			{
				state = 6;
				time(&t1);
				shape = 6;
				obj.x = 0.0;
				obj.y = 600.0;
				keystate = 1;
				a_f = 900;
				b_f = 445;
			}
			if (FSKEY_A == key)
			{
				state = 7;
				time(&t1);
				shape = 0;
			}
		}

		if (A == 1)
		{
			obj.DrawShelf(obj.x1, obj.y1);
			obj.DrawShelf2(obj.x2, obj.y2);
			bkrg.Draw();

			objectPick1(mx, my, t1, t2, state, a, b, keystate);
			objectPick2(mx, my, t1, t2, state, a, b, keystate);
			objectPick3(mx, my, t1, t2, state, a, b, keystate);
			objectPick4(mx, my, t1, t2, state, a, b, keystate);
			objectPick5(mx, my, t1, t2, state, a, b, keystate);
			objectPick6(mx, my, t1, t2, state, a, b, keystate);
			objectPick7(mx, my, t1, t2, state, a, b, keystate);

			time(&t2);
			t2 = difftime(t2, t1);

			a += (mx - a) / 50 + (mx - a) % 50;
			b += (my - b) / 50 + (my - b) % 50;
			ef.robotposx = a;
			ef.robotposy = b;
			InverseKinematics(a - 920.0, b - 650.0, 100);
			ForwardKinematics(0);

			if (t2 < 4.0 * dt)
			{
				obj.DrawShape(shape, obj.x, obj.y);
			}
			if (t2 == 8.0 * dt && shape == 3)
			{
				obj.dropShape(a_p, b_p, shape);
			}
			if (t2 == 9.0 * dt && shape == 3)
			{
				obj.retrackShape(a_p, b_p, shape);
			}
			if (t2 == 8.0 * dt && shape == 2)
			{
				obj.dropShape(a_b, b_b, shape);
			}
			if (t2 == 9.0 * dt && shape == 2)
			{
				obj.retrackShape(a_b, b_b, shape);
			}
			if (t2 == 8.0 * dt && shape == 1)
			{
				obj.dropShape(a_s, b_s, shape);
			}
			if (t2 == 9.0 * dt && shape == 1)
			{
				obj.retrackShape(a_s, b_s, shape);
			}
			if (t2 == 14.0 * dt && shape == 4)
			{
				obj.dropShape(a_g, b_g, shape);
			}
			if (t2 == 15.0 * dt && shape == 4)
			{
				obj.retrackShape(a_g, b_g, shape);
			}
			if (t2 == 10.0 * dt && shape == 5)
			{
				obj.dropShape(a_t, b_t, shape);
			}
			if (t2 == 11.0 * dt && shape == 5)
			{
				obj.retrackShape(a_t, b_t, shape);
			}
			if (t2 == 10.0 * dt && shape == 6)
			{
				obj.dropShape(a_f, b_f, shape);
			}
			if (t2 == 11.0 * dt && shape == 6)
			{
				obj.retrackShape(a_f, b_f, shape);
			}
		}

		if (FSKEY_M == key)
		{
			M = 1;
			A = 0;
			time(&t2);
			shape = 0;
		}
		if (FSKEY_A == key)
		{
			A = 1;
			M = 0;
			state = 7;
			time(&t1);
			shape = 0;
		}

		if (M == 1)
		{

			obj.DrawShelf(obj.x1, obj.y1);
			obj.DrawShelf2(obj.x2, obj.y2);
			bkrg.Draw();



			if (FSKEY_UP == key)
			{
				player.PlayOneShot(arm2);
				b = b - 5;
			}
			if (FSKEY_DOWN == key)
			{
				player.PlayOneShot(arm2);
				b = b + 5;
			}
			if (FSKEY_LEFT == key)
			{
				player.PlayOneShot(arm2);
				a = a - 5;
			}
			if (FSKEY_RIGHT == key)
			{
				player.PlayOneShot(arm2);
				a = a + 5;
			}
			if (FSKEY_S == key)
			{

				shape = 1;
				p = 1;

				obj.x = 0.0;
				obj.y = 600.0;

			}
			if (FSKEY_B == key)
			{

				shape = 2;
				obj.x = 0.0;
				obj.y = 600.0;
				p = 1;

			}
			if (FSKEY_P == key)
			{

				shape = 3;
				obj.x = 0.0;
				obj.y = 600.0;
				p = 1;

			}
			if (FSKEY_G == key)
			{

				shape = 4;
				obj.x = 0.0;
				obj.y = 600.0;
				p = 1;

			}
			if (FSKEY_T == key)
			{

				shape = 5;
				obj.x = 0.0;
				obj.y = 600.0;
				p = 1;

			}
			if (FSKEY_F == key)
			{

				shape = 6;
				obj.x = 0.0;
				obj.y = 600.0;
				p = 1;

			}
			if (FSKEY_SPACE == key)
			{
				if (grab_state == 0 && ef.robotgap == 80)
				{
					grab_state = 1;
				}
				if (grab_state == 1 && ef.robotgap == 50)
				{
					grab_state = 0;
					k1 = a - 25;
					k2 = b + 43;
				}
			}
			if (grab_state == 1)
			{
				ef.pick();
			}
			if (grab_state == 0)
			{
				ef.drop();
			}
			if (draw_state == 0 && grab_state == 0)
			{
				ef.drop();
				obj.dropShape_manual(k1, k2, shape);
				if (k1 < 420 && k1 >= 120)
				{
					if (k2 >= 600)
					{
						draw_state = 1;
						p = 0;
						//shape = 0;
					}
				}
				if (k1 >= 420 && k1 < 880)
				{
					if (k2 >= 700)
					{
						draw_state = 1;
						p = 0;
						//shape = 0;
					}
				}
				if (k1 <= 120 || k1 > 880)
				{
					if (k2 >= 160 && k2 <= 170)
					{
						draw_state = 1;
						p = 0;
						//shape = 0;
					}
					if (k2 > 320 && k2 <= 330)
					{
						draw_state = 1;
						p = 0;
						//shape = 0;
					}
					if (k2 >= 480)
					{
						draw_state = 1;
						p = 0;
						//shape = 0;
					}
				}

			}
			if (draw_state == 1)
			{
				if (p > 0)
				{
					obj.DrawShape(shape, obj.x, obj.y);
				}
			}
			ef.robotposx = a;
			ef.robotposy = b;
			InverseKinematics(a - 920.0, b - 650.0, 100);
			ForwardKinematics(0);

			if (grab_state == 1)
			{
				if (a < 400 && a>350)
				{
					if (b > 530 && b < 570)
					{
						draw_state = 0;
					}
				}
				if (draw_state == 0)
				{
					obj.moveShape(a, b, shape);
				}
			}
		}

		for (int i = 0; i < joints.size() - 1; i++)
		{
			if (i % 2 == 0)
			{
				glLineWidth(25);
				glColor3f(0.0, 0.0, 0.0);
				glBegin(GL_LINES);
				int point1x = joints[i].xpos + 920.0;
				int point1y = joints[i].ypos + 650.0;
				int point2x = joints[i + 1].xpos + 920.0;
				int point2y = joints[i + 1].ypos + 650.0;

				glVertex2i(point1x, point1y);
				glColor3f(0.3, 0.3, 0.3);
				glVertex2i(point2x, point2y);
				glEnd();
			}
			else
			{
				glLineWidth(15);
				glColor3f(0.3, 0.3, 0.3);
				glBegin(GL_LINES);
				int point1x = joints[i].xpos + 920.0;
				int point1y = joints[i].ypos + 650.0;
				int point2x = joints[i + 1].xpos + 920.0;
				int point2y = joints[i + 1].ypos + 650.0;

				glVertex2i(point1x, point1y);
				glColor3f(0.6, 0.6, 0.6);
				glVertex2i(point2x, point2y);
				glEnd();
			}
		}
		ef.draw();

		float color1[3] = { 0.0, 0.0, 0.5 };
		float color2[3] = { 1.0, 1.0, 1.0 };

		glLineWidth(10);
		glBegin(GL_LINES);
		glColor3f(0.6, 0.6, 0.6);
		glVertex2i(joints[joints.size() - 1].xpos + 920.0, joints[joints.size() - 1].ypos + 650.0);
		glColor3f(0.9, 0.9, 0.9);
		glVertex2i(xEnd + 920.0, yEnd + 650.0);
		glEnd();
		glLineWidth(1);

		drawCircle(joints[1].xpos + 920.0, joints[1].ypos + 650.0, 15, color1);
		drawCircle(joints[2].xpos + 920.0, joints[2].ypos + 650.0, 10, color1);
		drawCircle(xEnd + 920.0, yEnd + 650.0, 7, color1);
		drawCircle(joints[1].xpos + 920.0, joints[1].ypos + 650.0, 8, color2);
		drawCircle(joints[2].xpos + 920.0, joints[2].ypos + 650.0, 5, color2);
		drawCircle(xEnd + 920.0, yEnd + 650.0, 4, color2);

		FsSleep(30);
		FsSwapBuffers();

	}
}