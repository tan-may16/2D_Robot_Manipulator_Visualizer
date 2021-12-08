#ifndef END_EFFEC_DOT_H_IS_INCLUDED
#define END_EFFEC_DOT_H_IS_INCLUDED
class Effect
{
public:
    double robotposx, robotposy;
    double robotgap = 80;

    void draw();
    void pick();
    void drop();
};
#endif
