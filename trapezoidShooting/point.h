//Quinn Corcoran

#ifndef point_H
#define point_H

#include "trapezoid.h"

using namespace std;

class point{
    private:
        int x;
        int y;
        trapezoid* trap;
    public:
        point(int xi, int yi, trapezoid* t) {x = xi; y = yi; trap = t;};
        int getX() {return x;};
        int getY() {return y;};
        trapezoid* getTrap() {return trap;};
};

#endif /* point_H */