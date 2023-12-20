#ifndef STONE_H_INCLUDED
#define STONE_H_INCLUDED

#include "includes.h"

using std::vector;
using std::ofstream;
using std::endl;

struct Sphere {
    Sphere(double Sx_0, double Sy_0, double R);
    Sphere();

    double Sx_0, Sy_0; // координаты центра сферы
    double R; // радиус сферы
};
class Stone {

public:

    Stone(int stones_number, double max_radius, int stone_x_bound, int stone_y_bound);
    Stone();

    void Stones_Random(vector<Sphere> &Sp);

private:
    int stones_number;
    double max_radius;
    int stone_x_bound, stone_y_bound; // границы области
};

#endif // STONE_H_INCLUDED
