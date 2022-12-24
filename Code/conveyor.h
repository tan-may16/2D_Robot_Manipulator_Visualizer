# include <string>
# include <stdio.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
# include <stdlib.h>
# include <string.h>
# include <iostream>


const double Pi = 3.1415927;
const double G = 9.81;
const int num_blocks1 = 25;
const int num_blocks2 = 25;



class Belt
{
public:
	float posx, posy, state;

	Belt();
	~Belt();
	void Draw1(float conveyor_y, float conveyor_height);
};


class Background
{
public:
	int window_width, window_height;
	float conveyor_x, conveyor_y, conveyor_width, conveyor_height;

	Background();
	~Background();

	void Set_Values();
	void Draw_Conveyor_Support();
	void Draw_Conveyor_Roller();
	void Draw_Conveyor();
	void Draw();
	void Bin();

	Belt blt1[num_blocks1];
	Belt blt2[num_blocks2];
};