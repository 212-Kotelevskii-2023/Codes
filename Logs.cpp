#include "Logs.h"

Log::Log(double x_l, double y_l, double x_r, double y_r, double rad):
        x_l(x_l), y_l(y_l), x_r(x_r), y_r(y_r), rad(rad) {}
Log::Log() = default;

Logs::Logs(int logs_number, double max_l_rad, int logs_x_bound, int logs_y_bound, double max_log_length):
        logs_number(logs_number), max_l_rad(max_l_rad), logs_x_bound(logs_x_bound), logs_y_bound(logs_y_bound), max_log_length(max_log_length) {}
Logs::Logs() {};

void Logs::Logs_Random(vector<Log> &Lg) {
    double x_l_0, y_l_0, x_r_0, y_r_0, rad_0;

    while (logs_number--) {
        x_l_0 = (double)rand() / RAND_MAX * logs_x_bound;
        y_l_0 = (double)rand() / RAND_MAX * logs_y_bound;

        x_r_0 = (double)rand() / RAND_MAX * logs_x_bound;
        y_r_0 = (double)rand() / RAND_MAX * logs_y_bound;

        while (sqrt(pow(x_r_0 - x_l_0, 2) + pow(y_r_0 - y_l_0, 2)) > max_log_length) {
            x_r_0 = (x_r_0 + x_l_0) / 2;
            y_r_0 = (y_r_0 + y_l_0) / 2;
        }

        rad_0 = (1.0/3) * sqrt(pow(x_r_0 - x_l_0, 2) + pow(y_r_0 - y_l_0, 2));

        Lg.push_back(Log(x_l_0, y_l_0, x_r_0, y_r_0, rad_0));
    }
}
