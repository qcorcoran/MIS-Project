//Quinn Corcoran
//navigatingRiver

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
        friend class river;
};

#endif /* point_H */