#include "Hummock.h"

Hummock::Hummock(double x_0, double y_0, double sigma_x, double sigma_y, double sigma_xy, double height) {  // конструктор для обращения
    this->x_0 = x_0; this->y_0 = y_0;
    this->sigma_x = sigma_x; this->sigma_y = sigma_y;
    this->sigma_xy = sigma_xy;
    this->height = height;
}
Hummock::Hummock() = default;

double Hummock::Gauss_Bell(double x, double y) {  // формула Гауссиана с началом в x_0, y_0
    double degree = -(pow(x - x_0, 2) / (2 * pow(sigma_x, 2)) + (x - x_0) * (y - y_0) / pow(sigma_xy, 2) + pow(y - y_0, 2) / (2 * pow(sigma_y, 2))) / 5; // деление для пологости
    return height * exp(degree);
}
