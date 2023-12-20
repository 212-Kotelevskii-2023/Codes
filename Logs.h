#ifndef LOGS_H_INCLUDED
#define LOGS_H_INCLUDED

#include "includes.h"

using std::vector;
using std::ofstream;
using std::endl;


struct Log {
    Log(double x_l, double y_l, double x_r, double y_r, double rad);
    Log();

    double x_l, y_l;
    double x_r, y_r;
    double rad;
};
class Logs {

public:
    Logs(int logs_number, double max_l_rad, int logs_x_bound, int logs_y_bound, double max_log_length);
    Logs();

    void Logs_Random(vector<Log> &Lg);

private:
    int logs_number;
    double max_l_rad;
    int logs_x_bound, logs_y_bound;
    double max_log_length;
};

#endif // LOGS_H_INCLUDED
