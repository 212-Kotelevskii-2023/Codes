#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <time.h>
//#include <random>

#define eps 0.05
#define eps_offset 0.001

// splot 'C:\Users\Андрей\Desktop\прога на ЭВМ\прога на ЭВМ 3\Кочка\Gauss Bell.txt' with lines

using namespace std;

class Hummock {

    friend class Off_road;

public:
    Hummock(double x_0, double y_0, double sigma_x, double sigma_y, double sigma_xy, double height) {  // конструктор для обращения
        this->x_0 = x_0; this->y_0 = y_0;
        this->sigma_x = sigma_x; this->sigma_y = sigma_y;
        this->sigma_xy = sigma_xy;
        this->height = height;
    }

    Hummock() = default;

    double Gauss_Bell(double x, double y){  // формула Гауссиана с началом в x_0, y_0
        double degree = -(pow(x - x_0, 2) / (2 * pow(sigma_x, 2)) + (x - x_0) * (y - y_0) / pow(sigma_xy, 2) + pow(y - y_0, 2) / (2 * pow(sigma_y, 2))) / 5; // деление для пологости
        return height * exp(degree);
    }

    /* short Border(double x, double y) { // "область" Гауссиана
        if (abs(Gauss_Bell(x, y)) < eps)
            return -1;
        else
            return 1;
    } */

    /* void output(ofstream &file) {  // вывод координат Гауссиана в файл
        for (double i = -5; i <= 5; i += 0.1) {
            for (double j = -5; j <= 5; j += 0.1) {
                file << i << " " << j << " " << Gauss_Bell(i, j) << endl;
            }
        }
    } */

private:
    double x_0, y_0;  // координаты начала Гауссиана
    double sigma_x, sigma_y, sigma_xy;  // нужно чтоб выполнялось sxy^2 >= 2*sx*sy
    double height; // высота Гауссиана
};


struct Sphere {
    Sphere(double Sx_0, double Sy_0, double R): Sx_0(Sx_0), Sy_0(Sy_0), R(R) {}
    Sphere() = default;

    double Sx_0, Sy_0; // координаты центра сферы
    double R; // радиус сферы
};

class Stone {

    friend class Off_Road;

public:
    Stone(int stones_number, double max_radius, int stone_x_bound, int stone_y_bound):
        stones_number(stones_number), max_radius(max_radius), stone_x_bound(stone_x_bound), stone_y_bound(stone_y_bound) {}

    Stone() {}; // default


    void Stones_Random(vector<Sphere> &Sp) {
        double x_0, y_0, R_0;

        while (stones_number--) {
            x_0 = (double)rand() / RAND_MAX * stone_x_bound;
            y_0 = (double)rand() / RAND_MAX * stone_y_bound;
            R_0 = (double)rand() / RAND_MAX * max_radius;

            Sp.push_back(Sphere(x_0, y_0, R_0));
        }
    }

private:
    int stones_number;
    double max_radius;
    int stone_x_bound, stone_y_bound; // границы области

};


struct Log {
    Log(double x_l, double y_l, double x_r, double y_r, double rad):
        x_l(x_l), y_l(y_l), x_r(x_r), y_r(y_r), rad(rad) {}
    Log() = default;

    double x_l, y_l;
    double x_r, y_r;
    double rad;
};

class Logs {

    friend class Off_Road;

public:
    Logs(int logs_number, double max_l_rad, int logs_x_bound, int logs_y_bound):
        logs_number(logs_number), max_l_rad(max_l_rad), logs_x_bound(logs_x_bound), logs_y_bound(logs_y_bound) {}
    Logs() {};

    void Logs_Random(vector<Log> &Lg) {
        double x_l_0, y_l_0, x_r_0, y_r_0, rad_0;

        while (logs_number--) {
            x_l_0 = (double)rand() / RAND_MAX * logs_x_bound;
            y_l_0 = (double)rand() / RAND_MAX * logs_y_bound;

            x_r_0 = (double)rand() / RAND_MAX * logs_x_bound;
            y_r_0 = (double)rand() / RAND_MAX * logs_y_bound;

            rad_0 = (double)rand() / RAND_MAX * max_l_rad;

            Lg.push_back(Log(x_l_0, y_l_0, x_r_0, y_r_0, rad_0));
        }
    }

private:
    int logs_number;
    double max_l_rad;
    int logs_x_bound, logs_y_bound;

};


class Off_road { //: public Hummock {

public:
    Off_road(int bells_number, int max_height, int x_bound, int y_bound):
        bells_number(bells_number), max_height(max_height),  x_bound(x_bound), y_bound(y_bound) {}

    Off_road() {} // default



    void Random() {  // генерация параметров
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



    double Comp_Gauss_Bell(double x, double y) { // координаты точке на бездорожье
        double H = 0;

        for (int i = 0; i < (int)Hills.size(); i++) {
            H += Hills[i].Gauss_Bell(x, y);
        }

        return H / bells_number;
    }



    double Off_Road_plus_Stones(double x, double y, vector<Sphere> &Sp) { // добавляем камни
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



    double Off_Road_S_plus_Logs(double x, double y, vector<Sphere> &Sp, vector<Log> &Lg) { // добавляем брёвна
        double H = Off_Road_plus_Stones(x, y, Sp);

        for (int i = 0; i < (int)Lg.size(); i++) { // может быть ошибка из-за преобразования типа
            double a = -(Lg[i].y_r - Lg[i].y_l) / (Lg[i].x_r - Lg[i].x_l);
            double b = -(Lg[i].y_l * Lg[i].x_r - Lg[i].y_r * Lg[i].x_l) / (Lg[i].x_r - Lg[i].x_l);

            if (Lg[i].x_l <= x && x <= Lg[i].x_r && Lg[i].y_l <= y && y <= Lg[i].y_r && abs(a * x + y + b) / sqrt(pow(a, 2) + pow(b, 2) + 1) <= Lg[i].rad)
                H += Lg[i].rad;
            else
                continue;
        }

        return H;
    }



    void output(ofstream &file, vector<Sphere> &Sp, vector<Log> &Lg) {  // вывод координат композиции Гауссианов в файл
        for (double i = -5; i <= x_bound + 5; i += 0.05) {
            for (double j = -5; j <= y_bound + 5; j += 0.05) {
                file << i << " " << j << " " << Off_Road_S_plus_Logs(i, j, Sp, Lg) << endl;
            }
        }
    }

    /* void output(ofstream &file, vector<Sphere> &Sp) {  // вывод координат композиции Гауссианов в файл
        for (int i = 0; i < (int)Sp.size(); i++)
            file << Sp[i].Sx_0 << " " << Sp[i].Sy_0 << " " << Sp[i].R << endl;
    } */

        /* for (int i = 0; i < bells_number; i++) {
            file << i << " " << Hills[i].x_0 << " " << Hills[i].y_0 << " " << Hills[i].sigma_x
            << " " << Hills[i].sigma_y << " " << Hills[i].sigma_xy << " " << Hills[i].height << endl;
        } */

private:
    int bells_number; // количество холмов/низин
    int max_height; // максимальная высота/глубина
    int x_bound, y_bound; // границы области

    vector<Hummock> Hills; // бездорожье
};

int main() {
    srand(time(NULL));
    ofstream fout("Gauss Bell.txt");

    vector<Sphere> Sp;
    Stone *St = new Stone(0, 0.05, 5, 5);
    St->Stones_Random(Sp);

    vector<Log> Lg;
    Logs *Ls = new Logs(100, 1, 5, 5);
    Ls->Logs_Random(Lg);

    Off_road *Or = new Off_road(0, 1, 5, 5);
    Or->Random();
    Or->output(fout, Sp, Lg);

    delete St;
    delete Ls;
    delete Or;

    fout.close();
    return 0;
}
