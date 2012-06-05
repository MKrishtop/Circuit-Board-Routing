#ifndef MLOGIC_H
#define MLOGIC_H

#include <fstream>

using namespace std;

class MLogic
{
private:
    int n,m,sn,sm,en,em;
    int **gridt,**epath,**blocked,***params;
    const char *filename;
    bool init();
    int recwave(int,int,int,int);
    bool recpath(int,int);

public:
    MLogic();
    ~MLogic();
    bool eval();
    bool SetFN(const char* fn);
    int GetN();
    int GetM();
    int** GetGridT();
    int** GetEPath();
    int*** GetParams();
};

#endif // MLOGIC_H
