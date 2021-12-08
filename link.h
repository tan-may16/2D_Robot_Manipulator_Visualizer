#pragma once
#ifndef LINK_DOT_H_IS_INCLUDED
#define LINK_DOT_H_IS_INCLUDED
#include <iostream>
#include <vector>
#include <chrono>
#include "object.h"
#include "end_effec.h"
#include "conveyor.h"
#include "yssimplesound.h"
#include "yspng.h"

struct Joint
{
	float xpos, ypos;
	float len;
	float localAngle;
	float globalAngle;
};

class ArmIK
{
public:
	float xEnd = 0.0, yEnd = 0.0;
	int soundState = 0;

public:
	ArmIK();
	void AddJoint(float len);
	void ForwardKinematics(int startJoint);
	void InverseKinematics(float xTarget, float yTarget, int steps);
	void Automatic(int &A, int &M);
	int objectPick1(int& mx, int& my, time_t t1, time_t t2, int& state, int a, int b, int& keystate); 
	int objectPick2(int& mx, int& my, time_t& t1, time_t t2, int& state, int a, int b, int& keystate);
	int objectPick3(int& mx, int& my, time_t& t1, time_t t2, int& state, int a, int b, int& keystate);
	int objectPick4(int& mx, int& my, time_t& t1, time_t t2, int& state, int a, int b, int& keystate);
	int objectPick5(int& mx, int& my, time_t& t1, time_t t2, int& state, int a, int b, int& keystate);
	int objectPick6(int& mx, int& my, time_t& t1, time_t t2, int& state, int a, int b, int& keystate);
	int objectPick7(int& mx, int& my, time_t& t1, time_t t2, int& state, int a, int b, int& keystate);
	YsSoundPlayer player;
	YsSoundPlayer::SoundData arm;
	YsSoundPlayer::SoundData pop;
	YsSoundPlayer::SoundData backg;
	YsSoundPlayer::SoundData arm2;
};

#endif