#ifndef OBJECT_DOT_H_IS_INCLUDED
#define OBJECT_DOT_H_IS_INCLUDED

class Object_place {
public:
	int shape;
	double x = 0.0, y = 600.0;
	double x1 = 0.0, y1 = 0.0, x2 = 1000, y2 = 0.0;
	void DrawShelf(double x1, double y1);
	void DrawShelf2(double x2, double y2);
	void DrawShape(char shape, double& x, double& y);
	void dropShape(int& c, int& d, int shape);
	void moveShape(int a, int b, int shape);
	void retrackShape(int& e, int& f, int shape);
	void dropShape_manual(int& c, int& d, int shape);

};
#endif