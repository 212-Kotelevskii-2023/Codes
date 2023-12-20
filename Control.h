#ifndef CONTROL_H_INCLUDED
#define CONTROL_H_INCLUDED

#include "includes.h"
#include "Boundary.h"

using std::vector;
using std::ofstream;
using std::endl;

class Control {

public:
    //Control(string control_filename): control_filename(control_filename) {}
    //Control() = default;
    Boundary *B = new Boundary("configuration_file.txt");  // delete не работает
    //Boundary B{"configuration_file.txt"};

    void record_filenames() {
        B->read_files_information();
        control_filename = B->control_logs_name;

        control_logs.open(control_filename, ios::app);
        control_logs << "Команда: прочесть имена файлов, используемых в проекте\n\n";
        control_logs.close();
    }

    void create_field() {
        B->read_field_parameters();

        control_logs.open(control_filename, ios::app);
        control_logs << "Команда: прочесть параметры поля\n\n";
        control_logs.close();
    }

    void create_hills() {
        B->read_hills_information();

        control_logs.open(control_filename, ios::app);
        control_logs << "Команда: прочесть параметры холмов\n\n";
        control_logs.close();
    }

    void create_stones() {
        B->read_stones_information();

        control_logs.open(control_filename, ios::app);
        control_logs << "Команда: прочесть параметры камней\n\n";
        control_logs.close();
    }

    void create_logs() {
        B->read_logs_information();

        control_logs.open(control_filename, ios::app);
        control_logs << "Команда: прочесть параметры брёвен\n\n";
        control_logs.close();
    }

    //delete B;

private:
    ofstream control_logs;
    string control_filename;

};

#endif // CONTROL_H_INCLUDED
