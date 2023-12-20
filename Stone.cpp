#include "Stone.h"

Sphere::Sphere(double Sx_0, double Sy_0, double R): Sx_0(Sx_0), Sy_0(Sy_0), R(R) {}
Sphere::Sphere() = default;

Stone::Stone(int stones_number, double max_radius, int stone_x_bound, int stone_y_bound):
        stones_number(stones_number), max_radius(max_radius), stone_x_bound(stone_x_bound), stone_y_bound(stone_y_bound) {}
Stone::Stone() {}; // default

void Stone::Stones_Random(vector<Sphere> &Sp) {
    double x_0, y_0, R_0;

    while (stones_number--) {
        x_0 = (double)rand() / RAND_MAX * stone_x_bound;
        y_0 = (double)rand() / RAND_MAX * stone_y_bound;
        R_0 = (double)rand() / RAND_MAX * max_radius;

        Sp.push_back(Sphere(x_0, y_0, R_0));
    }
}
