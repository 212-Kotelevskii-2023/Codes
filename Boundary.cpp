#include "Boundary.h"

Boundary::Boundary(string configuration_file_name): configuration_file_name(configuration_file_name) {}
Boundary::Boundary() = default;


bool Boundary::search_word(const string &filename, const string &word, int *number_line) {
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

string Boundary::Boundary::read_i_line(const string &filename, int i_line) {
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

double Boundary::find_double_in_string(const string &str) {
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

string Boundary::find_brackts_word(const string &str) {
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

bool Boundary::read_files_information() {
    ifstream file(configuration_file_name);
    int line_number;

    if (!search_word(configuration_file_name, "Files used in the project", &line_number))
        return false;

    string line;

    line = read_i_line(configuration_file_name, line_number + 1);
    field_coordinates = find_brackts_word(line);
    line = read_i_line(configuration_file_name, line_number + 2);
    boundary_logs_name = find_brackts_word(line);
    line = read_i_line(configuration_file_name, line_number + 3);
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


bool Boundary::read_field_parameters() {
    ifstream file(configuration_file_name);
    int line_number;

    if (!search_word(configuration_file_name, "Field Parameters", &line_number))
        return false;

    string line;
    line = read_i_line(configuration_file_name, line_number + 1);
    x_field_bound = (int)find_double_in_string(line);
    line = read_i_line(configuration_file_name, line_number + 2);
    y_field_bound = (int)find_double_in_string(line);
    line = read_i_line(configuration_file_name, line_number + 3);
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

bool Boundary::read_hills_information() {
    ifstream file(configuration_file_name);
    int line_number;

    if (!search_word(configuration_file_name, "Information about the hills", &line_number))
        return false;

    string line;
    line = read_i_line(configuration_file_name, line_number + 1);
    f_number_hills = (int)find_double_in_string(line);
    line = read_i_line(configuration_file_name, line_number + 2);
    f_max_hills_height = (int)find_double_in_string(line);

    file.close();

    boundary_logs.open(boundary_logs_name, ios::app);
    boundary_logs << "Поступившая команда: прочесть параметры холмов\nРезультат выполнения:\n";
    boundary_logs << "Количество: " << f_number_hills << endl;
    boundary_logs << "Максимальная высота: " << f_max_hills_height << "\n\n";
    boundary_logs.close();

    return true;
}

bool Boundary::read_stones_information() {
    ifstream file(configuration_file_name);
    int line_number;

    if (!search_word(configuration_file_name, "Information about stones", &line_number))
        return false;

    string line;
    line = read_i_line(configuration_file_name, line_number + 1);
    f_number_stones = (int)find_double_in_string(line);
    line = read_i_line(configuration_file_name, line_number + 2);
    f_max_stones_height = find_double_in_string(line);

    file.close();

    boundary_logs.open(boundary_logs_name, ios::app);
    boundary_logs << "Поступившая команда: прочесть параметры камней\nРезультат выполнения:\n";
    boundary_logs << "Количество: " << f_number_stones << endl;
    boundary_logs << "Максимальная высота: " << f_max_stones_height << "\n\n";
    boundary_logs.close();

    return true;
}

bool Boundary::read_logs_information() {
    ifstream file(configuration_file_name);
    int line_number;

    if (!search_word(configuration_file_name, "Information about logs", &line_number))
        return false;

    string line;
    line = read_i_line(configuration_file_name, line_number + 1);
    f_number_logs = (int)find_double_in_string(line);
    line = read_i_line(configuration_file_name, line_number + 2);
    f_max_logs_diam = find_double_in_string(line);
    line = read_i_line(configuration_file_name, line_number + 3);
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

void Boundary::filling_in_parameters() {
    read_files_information();
    read_field_parameters();
    read_hills_information();
    read_stones_information();
    read_logs_information();

}

void Boundary::show() {
    cout << x_field_bound << endl << y_field_bound << endl << field_resolution << "\n\n";
    cout << f_number_hills << endl << f_max_hills_height << "\n\n";
    cout << f_number_stones << endl << f_max_stones_height << "\n\n";
    cout << f_number_logs << endl << f_max_logs_diam << endl << f_max_logs_length << "\n\n";
    cout <<  configuration_file_name << endl << field_coordinates << endl << boundary_logs_name << endl << control_logs_name << "\n\n";
}
