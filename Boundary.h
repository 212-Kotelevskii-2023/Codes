#ifndef BOUNDARY_H_INCLUDED
#define BOUNDARY_H_INCLUDED

#include "includes.h"

using namespace std;

class Boundary {
    friend class Control;
public:

    Boundary(string configuration_file_name);
    Boundary();


    bool search_word(const string &filename, const string &word, int *number_line);

    string read_i_line(const string &filename, int i_line);

    double find_double_in_string(const string &str);

    string find_brackts_word(const string &str);

    bool read_files_information();

    bool read_field_parameters();

    bool read_hills_information();

    bool read_stones_information();

    bool read_logs_information();

    void filling_in_parameters();

    void show();

private:

    ofstream boundary_logs;

    // файлы
    string configuration_file_name;
    string field_coordinates;
    string boundary_logs_name;
    string control_logs_name;

    // параметры поля
    int x_field_bound;
    int y_field_bound;
    double field_resolution;

    // параметры холмов
    int f_number_hills;
    int f_max_hills_height;

    // параметры камней
    int f_number_stones;
    double f_max_stones_height;

    // параметры брёвен
    int f_number_logs;
    double f_max_logs_diam;
    double f_max_logs_length;

};

#endif // BOUNDARY_H_INCLUDED
