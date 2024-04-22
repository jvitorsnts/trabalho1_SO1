#ifndef INE5412_H
#define INE5412_H

#include "Process.h"
#include <vector>

using namespace std;

class INE5412 {

public:
    
    // Estados da CPU
    enum CPU_STATE {
        RUNNING,
        NOT_RUNNING
    };

    // Construtor
    INE5412();

    // Destrutor
    ~INE5412();
    
    // Estabelece o contexto do processador
    void setContext(Process *runningProcess);

    // LImpa o contexto do processador
    void clearContext();

private:
    int R1;
    int R2;
    int R3;
    int R4;
    int R5;
    int R6;
    CPU_STATE ST;
    Process *PC;
    vector<Process::ProcessContext> SP= vector<Process:: ProcessContext>();
};


#endif // INE5412_H