#include <iostream>
#include <fstream>
#include <signal.h>

#include "ccasolver.h"

using namespace std;

void sigintHandler(int param)
{
    cout << "UNKNOWN" << endl;
    exit(0);
}

int main(int argc, char *argv[])
{
    signal(SIGINT, sigintHandler);

    if(argc < 2){
        cout << "File is not specified!" << endl;
        return 0;
    }

    ifstream file(argv[1]);
    if(!file.is_open()){
        cout << "Can not open file!" << endl;
        return 0;
    }

    CcaSolver solver;
    solver.readFromFile(file);
    file.close();
    solver.run();
}
