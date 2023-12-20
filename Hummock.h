#ifndef HUMMOCK_H_INCLUDED
#define HUMMOCK_H_INCLUDED

#include "includes.h"

using std::vector;
using std::ofstream;
using std::endl;

class Hummock {

public:
    Hummock(double x_0, double y_0, double sigma_x, double sigma_y, double sigma_xy, double height);
    Hummock();

    double Gauss_Bell(double x, double y);

private:
    double x_0, y_0;  // координаты начала Гауссиана
    double sigma_x, sigma_y, sigma_xy;  // нужно чтоб выполнялось sxy^2 >= 2*sx*sy
    double height; // высота Гауссиана
};


#endif // HUMMOCK_H_INCLUDED
