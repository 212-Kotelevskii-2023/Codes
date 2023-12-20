#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <time.h>
#include <sstream>

//#include <random>

#define eps 0.05
#define eps_offset 0.001

// splot 'C:\Users\Андрей\Desktop\прога на ЭВМ\прога на ЭВМ 3\Rover (без разделения)\Gauss Bell.txt' with lines
// splot 'C:\Users\Андрей\Desktop\прога на ЭВМ\прога на ЭВМ 3\Rover (без разделения)\Rover way.txt' with lines
// splot 'C:\Users\Андрей\Desktop\прога на ЭВМ\прога на ЭВМ 3\Rover (без разделения)\Gauss Bell.txt' with lines, 'C:\Users\Андрей\Desktop\прога на ЭВМ\прога на ЭВМ 3\Rover (без разделения)\Rover way.txt' with lines

using namespace std;



class Hummock {

public:
    Hummock(double x_0, double y_0, double sigma_x, double sigma_y, double sigma_xy, double height) {  // конструктор для обращения
    this->x_0 = x_0; this->y_0 = y_0;
    this->sigma_x = sigma_x; this->sigma_y = sigma_y;
    this->sigma_xy = sigma_xy;
    this->height = height;
    }
    Hummock() = default;

    double Gauss_Bell(double x, double y) {  // формула Гауссиана с началом в x_0, y_0
        double degree = -(pow(x - x_0, 2) / (2 * pow(sigma_x, 2)) + (x - x_0) * (y - y_0) / pow(sigma_xy, 2) + pow(y - y_0, 2) / (2 * pow(sigma_y, 2))) / 5; // деление для пологости
        return height * exp(degree);
    }

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

public:

    Stone(int stones_number, double max_radius, int stone_x_bound, int stone_y_bound):
        stones_number(stones_number), max_radius(max_radius), stone_x_bound(stone_x_bound), stone_y_bound(stone_y_bound) {}
    Stone() = default; // default

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

public:
    Logs(int logs_number, double max_l_rad, int logs_x_bound, int logs_y_bound, double max_log_length):
        logs_number(logs_number), max_l_rad(max_l_rad), logs_x_bound(logs_x_bound), logs_y_bound(logs_y_bound), max_log_length(max_log_length) {}
    Logs() = default;

    void Logs_Random(vector<Log> &Lg) {
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

private:
    int logs_number;
    double max_l_rad;
    int logs_x_bound, logs_y_bound;
    double max_log_length;
};


class Off_road {
    friend class Stone;
    friend class Logs;
public:
    int x_bound, y_bound; // границы области

    Off_road(int bells_number, int max_height, int x_bound, int y_bound):
        bells_number(bells_number), max_height(max_height),  x_bound(x_bound), y_bound(y_bound) {}
    Off_road() = default; // default

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

    double Comp_Gauss_Bell(double x, double y) { // координаты точки на бездорожье
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

    void output(ofstream &file, vector<Sphere> &Sp, vector<Log> &Lg, double resolution, vector<double> &coordinates) {  // вывод координат композиции Гауссианов в файл
        for (double i = 0; i < x_bound + resolution; i += resolution) {
            for (double j = 0; j < y_bound + resolution; j += resolution) {
                file << i << " " << j << " " << Off_Road_S_plus_Logs(i, j, Sp, Lg) << endl;
                coordinates.push_back(Off_Road_S_plus_Logs(i, j, Sp, Lg));
            }
        }
    }

private:
    int bells_number; // количество холмов/низин
    int max_height; // максимальная высота/глубина

    vector<Hummock> Hills; // бездорожье
};

double find_coordinates(double x, double y, vector<double> &coordinates, int x_bound, int y_bound, double resolution) { // 0.5 0.95 проверить при размерах 10 на 10
    double y_num = y_bound / resolution;
    double x0_num = x / resolution;
    double y0_num = y / resolution;

    int index_p = (int)x0_num * ((int)y_num + 1) + (int)y0_num;

    return coordinates[index_p];
}

double find_x_coord_number(int number, int y_bound, double resolution) {
    double y_num = y_bound / resolution;

    number = number / ((int)y_num + 1);

    return number * resolution;
}

double find_y_coord_number(int number, int y_bound, double resolution) {
    double y_num = y_bound / resolution;

    number = number % ((int)y_num + 1);

    return number * resolution;
}

// для графа используем вершины типа int, для этого нумеруем точки 1,...,n
double find_graph_dist(int top_1, int top_2, vector<double> &coordinates, int x_bound, int y_bound, double resolution) {
    double x_top_1 = find_x_coord_number(top_1, y_bound, resolution);
    double y_top_1 = find_y_coord_number(top_1, y_bound, resolution);
    double x_top_2 = find_x_coord_number(top_2, y_bound, resolution);
    double y_top_2 = find_y_coord_number(top_2, y_bound, resolution);

    double sq_dist = (x_top_1 - x_top_2) * (x_top_1 - x_top_2) + (y_top_1 - y_top_2) * (y_top_1 - y_top_2);
    if (sq_dist == resolution * resolution || sq_dist == 2 * resolution * resolution)
        return abs(find_coordinates(x_top_1, y_top_1, coordinates, x_bound, y_bound, resolution) - find_coordinates(x_top_2, y_top_2, coordinates, x_bound, y_bound, resolution));
    else
        return -1; // точки не соседние
}



class Boundary {
    friend class Control;
public:

    Boundary(string configuration_file_name): configuration_file_name(configuration_file_name) {}
    Boundary() = default;


    bool search_word(const string &filename, const string &word, int *number_line) {
        ifstream file(filename);
        string line;

        *number_line = 0;
        while (getline(file, line)) {
            *number_line = *number_line + 1;
            if (line.find(word) != string::npos)
                return true;
        }

        file.close();
        return false;
    }

    string read_i_line(int i_line) {
        ifstream file(configuration_file_name);

        string line;
        int temp_line = 1;
        while (temp_line <= i_line && getline(file, line)) {
            if (temp_line == i_line) {
                file.close();
                return line;
            }
            temp_line++;
        }

        file.close();
        return "";
    }

    double find_double_in_string(const string &str) {
        stringstream ss;
        double number;

        ss << str;

        while (!ss.eof()) {
            if (ss >> number)
                return number;
            ss.clear();
            ss.ignore();
        }

        return -1;
    }

    string find_brackts_word(const string &str) {
        string word;

        size_t start = str.find('"');
        if (start != string::npos) {
            size_t end = str.find('"', start + 1);

            if (end != string::npos) {
                start++;
                word = str.substr(start, end - start);
            }
        }

        return word;
    }

    bool read_files_information() {
        ifstream file(configuration_file_name);
        int line_number;

        if (!search_word(configuration_file_name, "Files used in the project", &line_number))
            return false;

        string line;

        line = read_i_line(line_number + 1);
        field_coordinates = find_brackts_word(line);
        line = read_i_line(line_number + 2);
        boundary_logs_name = find_brackts_word(line);
        line = read_i_line(line_number + 3);
        control_logs_name = find_brackts_word(line);

        file.close();

        boundary_logs.open(boundary_logs_name, ios::app);
        boundary_logs << "Поступившая команда: прочесть имена файлов, используемых в проекте\nРезультат выполнения:\n";
        boundary_logs << " Координаты поля: " << field_coordinates << endl;
        boundary_logs << " Boundary: " << boundary_logs_name << endl;
        boundary_logs << " Control: " << control_logs_name << "\n\n";
        boundary_logs.close();

        return true;
    }


    bool read_field_parameters() {
        ifstream file(configuration_file_name);
        int line_number;

        if (!search_word(configuration_file_name, "Field Parameters", &line_number))
            return false;

        string line;
        line = read_i_line(line_number + 1);
        x_field_bound = (int)find_double_in_string(line);
        line = read_i_line(line_number + 2);
        y_field_bound = (int)find_double_in_string(line);
        line = read_i_line(line_number + 3);
        field_resolution = find_double_in_string(line);

        file.close();

        boundary_logs.open(boundary_logs_name, ios::app);
        boundary_logs << "Поступившая команда: прочесть параметры поля\nРезультат выполнения:\n";
        boundary_logs << "Размер по X: " << x_field_bound << endl;
        boundary_logs << "Размер по Y: " << y_field_bound << endl;
        boundary_logs << "Разрешение вывода: " << field_resolution << "\n\n";
        boundary_logs.close();

        return true;
    }

    bool read_hills_information() {
        ifstream file(configuration_file_name);
        int line_number;

        if (!search_word(configuration_file_name, "Information about the hills", &line_number))
            return false;

        string line;
        line = read_i_line(line_number + 1);
        f_number_hills = (int)find_double_in_string(line);
        line = read_i_line(line_number + 2);
        f_max_hills_height = (int)find_double_in_string(line);

        file.close();

        boundary_logs.open(boundary_logs_name, ios::app);
        boundary_logs << "Поступившая команда: прочесть параметры холмов\nРезультат выполнения:\n";
        boundary_logs << "Количество: " << f_number_hills << endl;
        boundary_logs << "Максимальная высота: " << f_max_hills_height << "\n\n";
        boundary_logs.close();

        return true;
    }

    bool read_stones_information() {
        ifstream file(configuration_file_name);
        int line_number;

        if (!search_word(configuration_file_name, "Information about stones", &line_number))
            return false;

        string line;
        line = read_i_line(line_number + 1);
        f_number_stones = (int)find_double_in_string(line);
        line = read_i_line(line_number + 2);
        f_max_stones_height = find_double_in_string(line);

        file.close();

        boundary_logs.open(boundary_logs_name, ios::app);
        boundary_logs << "Поступившая команда: прочесть параметры камней\nРезультат выполнения:\n";
        boundary_logs << "Количество: " << f_number_stones << endl;
        boundary_logs << "Максимальная высота: " << f_max_stones_height << "\n\n";
        boundary_logs.close();

        return true;
    }

    bool read_logs_information() {
        ifstream file(configuration_file_name);
        int line_number;

        if (!search_word(configuration_file_name, "Information about logs", &line_number))
            return false;

        string line;
        line = read_i_line(line_number + 1);
        f_number_logs = (int)find_double_in_string(line);
        line = read_i_line(line_number + 2);
        f_max_logs_diam = find_double_in_string(line);
        line = read_i_line(line_number + 3);
        f_max_logs_length = find_double_in_string(line);

        file.close();

        boundary_logs.open(boundary_logs_name, ios::app);
        boundary_logs << "Поступившая команда: прочесть параметры брёвен\nРезультат выполнения:\n";
        boundary_logs << "Количество: " << f_number_logs << endl;
        boundary_logs << "Максимальный диаметр: " << f_max_logs_diam << endl;
        boundary_logs << "Максимальная длина: " << f_max_logs_length << "\n\n";
        boundary_logs.close();

        return true;
    }

    void filling_in_parameters() {
        read_files_information();
        read_field_parameters();
        read_hills_information();
        read_stones_information();
        read_logs_information();

    }

    void show() {
        cout << x_field_bound << endl << y_field_bound << endl << field_resolution << "\n\n";
        cout << f_number_hills << endl << f_max_hills_height << "\n\n";
        cout << f_number_stones << endl << f_max_stones_height << "\n\n";
        cout << f_number_logs << endl << f_max_logs_diam << endl << f_max_logs_length << "\n\n";
        cout <<  configuration_file_name << endl << field_coordinates << endl << boundary_logs_name << endl << control_logs_name << "\n\n";
    }


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

class Control {

public:
    //Control(string control_filename): control_filename(control_filename) {}
    //Control() = default;
    Boundary B{"configuration_file.txt"};

    void record_filenames() {
        B.read_files_information();
        control_filename = B.control_logs_name;

        control_logs.open(control_filename, ios::app);
        control_logs << "Команда: прочесть имена файлов, используемых в проекте\n\n";
        control_logs.close();
    }

    void create_field() {
        B.read_field_parameters();

        control_logs.open(control_filename, ios::app);
        control_logs << "Команда: прочесть параметры поля\n\n";
        control_logs.close();
    }

    void create_hills() {
        B.read_hills_information();

        control_logs.open(control_filename, ios::app);
        control_logs << "Команда: прочесть параметры холмов\n\n";
        control_logs.close();
    }

    void create_stones() {
        B.read_stones_information();

        control_logs.open(control_filename, ios::app);
        control_logs << "Команда: прочесть параметры камней\n\n";
        control_logs.close();
    }

    void create_logs() {
        B.read_logs_information();

        control_logs.open(control_filename, ios::app);
        control_logs << "Команда: прочесть параметры брёвен\n\n";
        control_logs.close();
    }

private:
    ofstream control_logs;
    string control_filename;

};

class Rover {
    friend class Processor;
public:
    Rover(double R_coord_x, double R_coord_y):
        R_coord_x(R_coord_x), R_coord_y(R_coord_y) {}
    Rover() = default;


    // directions: NN = 1, NE = 2,..., WW = 7, NW = 8
    double angle_of_inclination(double x_0, double y_0, vector<double> &coordinates, short direction, int x_bound, int y_bound, double resolution) {
        double h_1 = find_coordinates(x_0, y_0, coordinates, x_bound, y_bound, resolution);
        double h_2, tg_ang;
        double Shift = resolution;
        double Shift_sq = sqrt(2 * Shift * Shift);

        //cout << x_0 << " " << y_0 << " " << find_coordinates(x_0, y_0, coordinates, x_bound, y_bound, resolution) << endl;
        if (direction == 1 || direction == 5) {
            y_0 += Shift;
            h_2 = find_coordinates(x_0, y_0, coordinates, x_bound, y_bound, resolution);

            tg_ang = (h_2 - h_1) / Shift;
        }

        if (direction == 2 || direction == 6) {
            x_0 += Shift;
            y_0 += Shift;
            h_2 = find_coordinates(x_0, y_0, coordinates, x_bound, y_bound, resolution);

            tg_ang = (h_2 - h_1) / Shift_sq;
        }

        if (direction == 3 || direction == 7) {
            x_0 += Shift;
            h_2 = find_coordinates(x_0, y_0, coordinates, x_bound, y_bound, resolution);

            tg_ang = (h_2 - h_1) / Shift;
        }

        if (direction == 4 || direction == 8) {
            x_0 += Shift;
            y_0 -= Shift;
            h_2 = find_coordinates(x_0, y_0, coordinates, x_bound, y_bound, resolution);

            tg_ang = (h_2 - h_1) / Shift_sq;
        }
        //cout << x_0 << " " << y_0 << " " << find_coordinates(x_0, y_0, coordinates, x_bound, y_bound, resolution) << endl;

        tg_ang = abs(tg_ang);

        return atan(tg_ang);
    }

    bool calculate_clearance(double x_0, double y_0, vector<double> &coordinates, int x_bound, int y_bound, double resolution) {
        double temp = 0;
        double current_position = find_coordinates(x_0, y_0, coordinates, x_bound, y_bound, resolution);
        double height_difference = 0;

        for (double i = -0.05; i < 0.1; i += 0.05) {
            for (double j = -0.05; j < 0.1; j += 0.05) {
                if (abs(current_position - find_coordinates(x_0 + i, y_0 + j, coordinates, x_bound, y_bound, resolution)) > temp)
                    temp = abs(current_position - find_coordinates(x_0 + i, y_0 + j, coordinates, x_bound, y_bound, resolution));
            }
        }

        //cout << temp << endl;
        if (temp > clearance)
            return false;
        else
            return true;
    }

    bool sensor(double x_0, double y_0, short direction, vector<double> &coordinates, int x_bound, int y_bound, double resolution) {

        double A[5];
        double B[7];
        double C[9];

        double start_pos = find_coordinates(x_0, y_0, coordinates, x_bound, y_bound, resolution);
        double max_difference = 0;

        switch (direction) {
            case 1:
                for (int i = 0; i < 5; i++)
                    A[i] = find_coordinates(x_0 - 0.1 + 0.05 * i, y_0 + 0.1, coordinates, x_bound, y_bound, resolution);
                for (int i = 0; i < 7; i++)
                    B[i] = find_coordinates(x_0 - 0.15 + 0.05 * i, y_0 + 0.15, coordinates, x_bound, y_bound, resolution);
                for (int i = 0; i < 9; i++)
                    C[i] = find_coordinates(x_0 - 0.2 + 0.05 * i, y_0 + 0.2, coordinates, x_bound, y_bound, resolution);

                break;
            case 2:
                for (int i = 0; i < 3; i++)
                    A[i] = find_coordinates(x_0 + i * 0.05, y_0 + 0.1, coordinates, x_bound, y_bound, resolution);
                for (int i = 3; i < 5; i++)
                    A[i] = find_coordinates(x_0 + 0.1, y_0 + 0.1 - (i - 2) * 0.05, coordinates, x_bound, y_bound, resolution);

                for (int i = 0; i < 4; i++)
                    B[i] = find_coordinates(x_0 + i * 0.05, y_0 + 0.15, coordinates, x_bound, y_bound, resolution);
                for (int i = 4; i < 7; i++)
                    B[i] = find_coordinates(x_0 + 0.15, y_0 + 0.15 - (i - 3) * 0.05, coordinates, x_bound, y_bound, resolution);

                for (int i = 0; i < 5; i++)
                    C[i] = find_coordinates(x_0 + i * 0.05, y_0 + 0.2, coordinates, x_bound, y_bound, resolution);
                for (int i = 5; i < 9; i++)
                    C[i] = find_coordinates(x_0 + 0.2, y_0 + 0.2 - (i - 4) * 0.05, coordinates, x_bound, y_bound, resolution);

                break;
            case 3:
                for (int i = 0; i < 5; i++)
                    A[i] = find_coordinates(x_0 + 0.1, y_0 - 0.1 + 0.05 * i, coordinates, x_bound, y_bound, resolution);
                for (int i = 0; i < 7; i++)
                    B[i] = find_coordinates(x_0 + 0.15, y_0 - 0.15 + 0.05 * i, coordinates, x_bound, y_bound, resolution);
                for (int i = 0; i < 9; i++)
                    C[i] = find_coordinates(x_0 + 0.2, y_0 - 0.2 + 0.05 * i, coordinates, x_bound, y_bound, resolution);

                break;
            case 4:
                for (int i = 0; i < 3; i++)
                    A[i] = find_coordinates(x_0 + i * 0.05, y_0 - 0.1, coordinates, x_bound, y_bound, resolution);
                for (int i = 3; i < 5; i++)
                    A[i] = find_coordinates(x_0 + 0.1, y_0 - 0.1 + (i - 2) * 0.05, coordinates, x_bound, y_bound, resolution);

                for (int i = 0; i < 4; i++)
                    B[i] = find_coordinates(x_0 + i * 0.05, y_0 - 0.15, coordinates, x_bound, y_bound, resolution);
                for (int i = 4; i < 7; i++)
                    B[i] = find_coordinates(x_0 + 0.15, y_0 - 0.15 + (i - 3) * 0.05, coordinates, x_bound, y_bound, resolution);

                for (int i = 0; i < 5; i++)
                    C[i] = find_coordinates(x_0 + i * 0.05, y_0 - 0.2, coordinates, x_bound, y_bound, resolution);
                for (int i = 5; i < 9; i++)
                    C[i] = find_coordinates(x_0 + 0.2, y_0 - 0.2 + (i - 4) * 0.05, coordinates, x_bound, y_bound, resolution);

                break;
            case 5:
                for (int i = 0; i < 5; i++)
                    A[i] = find_coordinates(x_0 - 0.1 + 0.05 * i, y_0 - 0.1, coordinates, x_bound, y_bound, resolution);
                for (int i = 0; i < 7; i++)
                    B[i] = find_coordinates(x_0 - 0.15 + 0.05 * i, y_0 - 0.15, coordinates, x_bound, y_bound, resolution);
                for (int i = 0; i < 9; i++)
                    C[i] = find_coordinates(x_0 - 0.2 + 0.05 * i, y_0 - 0.2, coordinates, x_bound, y_bound, resolution);

                break;
            case 6:
                for (int i = 0; i < 3; i++)
                    A[i] = find_coordinates(x_0 - i * 0.05, y_0 - 0.1, coordinates, x_bound, y_bound, resolution);
                for (int i = 3; i < 5; i++)
                    A[i] = find_coordinates(x_0 - 0.1, y_0 - 0.1 + (i - 2) * 0.05, coordinates, x_bound, y_bound, resolution);

                for (int i = 0; i < 4; i++)
                    B[i] = find_coordinates(x_0 - i * 0.05, y_0 - 0.15, coordinates, x_bound, y_bound, resolution);
                for (int i = 4; i < 7; i++)
                    B[i] = find_coordinates(x_0 - 0.15, y_0 - 0.15 + (i - 3) * 0.05, coordinates, x_bound, y_bound, resolution);

                for (int i = 0; i < 5; i++)
                    C[i] = find_coordinates(x_0 - i * 0.05, y_0 - 0.2, coordinates, x_bound, y_bound, resolution);
                for (int i = 5; i < 9; i++)
                    C[i] = find_coordinates(x_0 - 0.2, y_0 - 0.2 + (i - 4) * 0.05, coordinates, x_bound, y_bound, resolution);

                break;
            case 7:
                for (int i = 0; i < 5; i++)
                    A[i] = find_coordinates(x_0 - 0.1, y_0 - 0.1 + 0.05 * i, coordinates, x_bound, y_bound, resolution);
                for (int i = 0; i < 7; i++)
                    B[i] = find_coordinates(x_0 - 0.15, y_0 - 0.15 + 0.05 * i, coordinates, x_bound, y_bound, resolution);
                for (int i = 0; i < 9; i++)
                    C[i] = find_coordinates(x_0 - 0.2, y_0 - 0.2 + 0.05 * i, coordinates, x_bound, y_bound, resolution);

                break;
            case 8:
                for (int i = 0; i < 3; i++)
                    A[i] = find_coordinates(x_0 - i * 0.05, y_0 + 0.1, coordinates, x_bound, y_bound, resolution);
                for (int i = 3; i < 5; i++)
                    A[i] = find_coordinates(x_0 - 0.1, y_0 + 0.1 - (i - 2) * 0.05, coordinates, x_bound, y_bound, resolution);

                for (int i = 0; i < 4; i++)
                    B[i] = find_coordinates(x_0 - i * 0.05, y_0 + 0.15, coordinates, x_bound, y_bound, resolution);
                for (int i = 4; i < 7; i++)
                    B[i] = find_coordinates(x_0 - 0.15, y_0 + 0.15 - (i - 3) * 0.05, coordinates, x_bound, y_bound, resolution);

                for (int i = 0; i < 5; i++)
                    C[i] = find_coordinates(x_0 - i * 0.05, y_0 + 0.2, coordinates, x_bound, y_bound, resolution);
                for (int i = 5; i < 9; i++)
                    C[i] = find_coordinates(x_0 - 0.2, y_0 + 0.2 - (i - 4) * 0.05, coordinates, x_bound, y_bound, resolution);

                break;
        }

        for (int i = 0; i < 5; i++) {
            if (abs(A[i] - start_pos) >= max_difference)
                max_difference = abs(A[i] - start_pos);
        }
        for (int i = 0; i < 7; i++) {
            if (abs(B[i] - start_pos) >= max_difference)
                max_difference = abs(B[i] - start_pos);
        }
        for (int i = 0; i < 9; i++) {
            if (abs(C[i] - start_pos) >= max_difference)
                max_difference = abs(C[i] - start_pos);
        }

        /*for (int i = 0; i < 5; i++)
            cout << A[i] << " ";
        cout << endl;*/

        if (max_difference < clearance)
            return true;
        else
            return false;
    }

private:
    double R_coord_x;
    double R_coord_y;
    //double R_coord_z;
    double clearance = 0.05;
    short initial_direction = 1; // directions: NN = 1, NE = 2,..., WW = 7, NW = 8
    double velocity = 0.1;

    double limit_angle = 1.58;

};

class Processor : public Rover {

public:
    Processor(double rov_start_coord_x, double rov__start_coord_y, short rov_start_direction, int x_p_bound, int y_p_bound, double p_resolution):
        rov_start_coord_x(rov_start_coord_x), rov_start_coord_y(rov_start_coord_y), rov_start_direction(rov_start_direction), x_p_bound(x_p_bound), y_p_bound(y_p_bound), p_resolution(p_resolution) {}
    Processor() = default;

    void find_way(ofstream &file, double current_x, double current_y, short current_direction, vector<double> &coordinates) { // начальное направлени можно убрать
        int path_length = 100;
        file << current_x << " " << current_y << " " << find_coordinates(current_x, current_y, coordinates, x_p_bound, y_p_bound, p_resolution) << endl;

        while(path_length--) {
            if (current_x < 4 * p_resolution || current_x > x_p_bound - 4 * p_resolution || current_y < p_resolution || current_y > y_p_bound - 4 * p_resolution) { // проверка принадлежности полю
                //file << -1 << " " << -1 << " " << -1;
                cout << "Вышел за пределы поля" << endl;;
                break;
            }

            if (calculate_clearance(current_x, current_y, coordinates, x_p_bound, y_p_bound, p_resolution)) {
                int k = 1;

                for (short i = 1; i < 9; i++) {
                    if (angle_of_inclination(current_x, current_y, coordinates, i, x_p_bound, y_p_bound, p_resolution) < limit_angle && sensor(current_x, current_y, i, coordinates, x_p_bound, y_p_bound, p_resolution)) {
                        switch (i) {
                        case 1:
                            current_y += p_resolution;
                            file << current_x << " " << current_y << " " << find_coordinates(current_x, current_y, coordinates, x_p_bound, y_p_bound, p_resolution) << endl;
                            break;
                        case 2:
                            current_x += p_resolution;
                            current_y += p_resolution;
                            file << current_x << " " << current_y << " " << find_coordinates(current_x, current_y, coordinates, x_p_bound, y_p_bound, p_resolution) << endl;
                            break;
                        case 3:
                            current_x += p_resolution;
                            file << current_x << " " << current_y << " " << find_coordinates(current_x, current_y, coordinates, x_p_bound, y_p_bound, p_resolution) << endl;
                            break;
                        case 4:
                            current_x += p_resolution;
                            current_y -= p_resolution;
                            file << current_x << " " << current_y << " " << find_coordinates(current_x, current_y, coordinates, x_p_bound, y_p_bound, p_resolution) << endl;
                            break;
                        case 5:
                            current_y -= p_resolution;
                            file << current_x << " " << current_y << " " << find_coordinates(current_x, current_y, coordinates, x_p_bound, y_p_bound, p_resolution) << endl;
                            break;
                        case 6:
                            current_x -= p_resolution;
                            current_y -= p_resolution;
                            file << current_x << " " << current_y << " " << find_coordinates(current_x, current_y, coordinates, x_p_bound, y_p_bound, p_resolution) << endl;
                            break;
                        case 7:
                            current_x -= p_resolution;
                            file << current_x << " " << current_y << " " << find_coordinates(current_x, current_y, coordinates, x_p_bound, y_p_bound, p_resolution) << endl;
                            break;
                        case 8:
                            current_x -= p_resolution;
                            current_y += p_resolution;
                            file << current_x << " " << current_y << " " << find_coordinates(current_x, current_y, coordinates, x_p_bound, y_p_bound, p_resolution) << endl;
                            break;
                        }

                        break;
                    }
                k++;
                }

                if (k > 8) {
                    //file << -3 << " " << -3 << " " << -3; // нет пути ни в какую сторону
                    cout << "Не может никуда проехать" << endl;
                    break;
                }
            }
            else {
                //file << -2 << " " << -2 << " " << -2; // попали в яму, из которой нельзя выбраться
                cout << "Попал в яму, из которой не может выбраться" << endl;
                break;
            }

        }
    }

private:
    double rov_start_coord_x;
    double rov_start_coord_y;
    //double rov_start_coord_z;
    short rov_start_direction;

    int x_p_bound;
    int y_p_bound;
    double p_resolution;

    //short initial_direction;
};


int main() {
    setlocale(LC_ALL, "Russian");

    /*string conf_f_name = "configuration_file.txt";

    Control *C = new Control;

    C->record_filenames();
    C->create_field();
    C->create_hills();
    C->create_stones();
    C->create_logs();

    delete C;*/


    //srand(time(NULL));
    ofstream fout1("Gauss Bell.txt");

    int X_B, Y_B; X_B = Y_B = 10;
    double resolution = 0.05;
    vector<double> coordinates;

    Off_road *Or = new Off_road(10, 10, X_B, Y_B);
    Or->Random();

    vector<Sphere> Sp;
    Stone *St = new Stone(0, 0.3, Or->x_bound, Or->y_bound);
    St->Stones_Random(Sp);

    vector<Log> Lg;
    Logs *Ls = new Logs(0, 0.15, Or->x_bound, Or->y_bound, 0.5);
    Ls->Logs_Random(Lg);

    Or->output(fout1, Sp, Lg, resolution, coordinates);

    delete Or;
    delete St;
    delete Ls;

    fout1.close();

    //cout << find_coordinates(0.5, 1.95, coordinates, X_B, Y_B, resolution);
    cout << find_graph_dist(0, 202, coordinates, X_B, Y_B, resolution);

    ofstream fout2("Rover way.txt");
    Processor *Pr = new Processor(5, 5, 1, X_B, Y_B, resolution);
    //Pr->find_way(fout2, 5, 5, 1, coordinates);

    delete Pr;
    fout2.close();


    /*Rover *Rov = new Rover(0,0);
    cout << Rov->angle_of_inclination(1.1, 2.15, coordinates, 4, X_B, Y_B, resolution);
    cout << Rov->calculate_clearance(1, 1, coordinates, X_B, Y_B, resolution);
    cout << Rov->sensor(1, 1, 1, coordinates, X_B, Y_B, resolution);
    delete Rov;*/


    return 0;
}





