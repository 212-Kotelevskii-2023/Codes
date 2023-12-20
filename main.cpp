#include "Hummock.h"
#include "Stone.h"
#include "Logs.h"
#include "Off_road.h"

#include "Control.h"

//#define eps 0.05
//#define eps_offset 0.001

// splot 'C:\Users\Андрей\Desktop\прога на ЭВМ\прога на ЭВМ 3\Rover\Gauss Bell.txt' with lines

using namespace std;

int main() {

    //string conf_f_name = "configuration_file.txt";

    //Boundary *B = new Boundary(conf_f_name);
    Control *C = new Control;

    //B->filling_in_parameters();
    //B->show();
    //B->read_files_information();

    C->record_filenames();
    C->create_field();
    C->create_hills();
    C->create_stones();
    C->create_logs();

    //delete B;
    delete C;

    /*//srand(time(NULL));
    ofstream fout("Gauss Bell.txt");

    int X_B, Y_B; X_B = Y_B = 5;
    double resolution = 0.05;

    Off_road *Or = new Off_road(1, 1, X_B, Y_B);
    Or->Random();

    vector<Sphere> Sp;
    Stone *St = new Stone(0, 0.05, Or->x_bound, Or->y_bound);
    St->Stones_Random(Sp);

    vector<Log> Lg;
    Logs *Ls = new Logs(0, 0.05, Or->x_bound, Or->y_bound, 5);
    Ls->Logs_Random(Lg);

    Or->output(fout, Sp, Lg, resolution);

    delete Or;
    delete St;
    delete Ls;

    fout.close(); */


    return 0;
}






