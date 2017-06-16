#include <iostream>
#include <fstream>
#include <signal.h>
using namespace std;

bool cca(ifstream &file);

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
  
  bool res = cca(file);
  if(res){
    cout << "SATISFIABLE" << endl;
  }
  else{
    cout << "UNSATISFIABLE" << endl;
  }
}

bool cca(ifstream &file)
{
  file.close();
  
  return false;
}
