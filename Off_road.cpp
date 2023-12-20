#include "Off_road.h"

void Off_road::Random() {  // генерация параметров
    int b_n = bells_number;
    while (b_n--) { // заполняем вектор Hills
        double x0, y0, sx, sy, sxy, ht;

        x0 = (double)rand() / RAND_MAX * x_bound;
        y0 = (double)rand() / RAND_MAX * y_bound;
        sx = (double)rand() / RAND_MAX; sy = (double)rand() / RAND_MAX;
        // sxy = (double)rand() / RAND_MAX;  // надо добавить условие положительности определителя
        while (4*sx*sy > 1) {
            sx /= 2; sy /= 2;
        }
        sxy = sqrt(4*sx*sy);

        ht = (double)rand() / RAND_MAX * max_height * pow(-1, rand());

        Hills.push_back(Hummock(x0, y0, sx, sy, sxy, ht));
    }
}

Off_road::Off_road(int bells_number, int max_height, int x_bound, int y_bound):
        bells_number(bells_number), max_height(max_height),  x_bound(x_bound), y_bound(y_bound) {}
Off_road::Off_road() {} // default

double Off_road::Comp_Gauss_Bell(double x, double y) { // координаты точке на бездорожье
    double H = 0;

    for (int i = 0; i < (int)Hills.size(); i++) {
        H += Hills[i].Gauss_Bell(x, y);
    }

    return H / bells_number;
}

double Off_road::Off_Road_plus_Stones(double x, double y, vector<Sphere> &Sp) { // добавляем камни
    double H;

    if (bells_number == 0)
        H = 0;
    else
        H = Comp_Gauss_Bell(x, y);

    for (int i = 0; i < (int)Sp.size(); i++) { // может быть ошибка из-за преобразования типа
        if (abs(x - Sp[i].Sx_0) < Sp[i].R && abs(y - Sp[i].Sy_0) < Sp[i].R)
            H += sqrt(pow(Sp[i].R, 2) - pow(Sp[i].Sx_0 - x, 2) - pow(Sp[i].Sy_0 -  y, 2));
        else
            continue;
    }

    return H;
}

double Off_road::Off_Road_S_plus_Logs(double x, double y, vector<Sphere> &Sp, vector<Log> &Lg) { // добавляем брёвна
    double H = Off_Road_plus_Stones(x, y, Sp);

    for (int i = 0; i < (int)Lg.size(); i++) { // может быть ошибка из-за преобразования типа
        double a = -(Lg[i].y_r - Lg[i].y_l) / (Lg[i].x_r - Lg[i].x_l);
        double b = -(Lg[i].y_l * Lg[i].x_r - Lg[i].y_r * Lg[i].x_l) / (Lg[i].x_r - Lg[i].x_l);
        double dist = abs(a * x + y + b) / sqrt(pow(a, 2) + pow(b, 2) + 1);

        double b_1 = Lg[i].x_r - a * Lg[i].y_r;
        double b_2 = Lg[i].x_l - a * Lg[i].y_l;
        double L_1 = - x + a * y + b_1;
        double L_2 = - x + a * y + b_2;

        if (dist <= Lg[i].rad && L_1 * L_2 <= 0)
            H += sqrt(pow(Lg[i].rad, 2) - pow(dist, 2));
        else
            continue;
    }

    return H;
}

void Off_road::output(ofstream &file, vector<Sphere> &Sp, vector<Log> &Lg, double resolution) {  // вывод координат композиции Гауссианов в файл
    for (double i = -5; i <= x_bound + 5; i += resolution) {
        for (double j = -5; j <= y_bound + 5; j += resolution) {
            file << i << " " << j << " " << Off_Road_S_plus_Logs(i, j, Sp, Lg) << endl;
        }
    }
}
