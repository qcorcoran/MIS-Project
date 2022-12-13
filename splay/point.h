//Quinn Corcoran
//splay

#include <sstream>

#ifndef point_H
#define point_H

using namespace std;

class point{
    private:
        int x;
        int y;
    public:
        point(int xi, int yi) {x = xi; y = yi;};
        int getX() {return x;};
        int getY() {return y;};
        string toString() {stringstream ssx; ssx<<x; string strx = ""; ssx>>strx; stringstream ssy; ssy<<y; string stry = ""; ssy>>stry; return "("+strx+", "+stry+")";}
};

#endif /* point_H */