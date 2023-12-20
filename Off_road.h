#ifndef OFF_ROAD_H_INCLUDED
#define OFF_ROAD_H_INCLUDED

#include "includes.h"
#include "Hummock.h"
#include "Stone.h"
#include "Logs.h"

using std::vector;
using std::ofstream;
using std::endl;

class Off_road {
    friend class Stone;
    friend class Logs;
public:
    int x_bound, y_bound; // границы области

    Off_road(int bells_number, int max_height, int x_bound, int y_bound);
    Off_road();

    void Random();

    double Comp_Gauss_Bell(double x, double y);

    double Off_Road_plus_Stones(double x, double y, vector<Sphere> &Sp);

    double Off_Road_S_plus_Logs(double x, double y, vector<Sphere> &Sp, vector<Log> &Lg);

    void output(ofstream &file, vector<Sphere> &Sp, vector<Log> &Lg, double resolution);

private:
    int bells_number; // количество холмов/низин
    int max_height; // максимальная высота/глубина

    vector<Hummock> Hills; // бездорожье
};

#endif // OFF_ROAD_H_INCLUDED
