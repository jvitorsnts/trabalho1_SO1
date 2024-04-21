//
// Created by joao on 18/04/2024
//

#ifndef PROCESS_CONTEXT_H
#define PROCESS_CONTEXT_H

#include <array>
#include "Register.h"

using namespace std;

class ProcessContext {
public:
    ProcessContext();

    array<Register, 6> getGeneralRegisters() const;
    Register getPC() const;
    Register getSP() const;
    Register getST() const;
    
    void setGeneralRegisters(const array<Register, 6>& newGeneralRegisters);
    void setPC(const Register& newPC);
    void setSP(const Register& newSP);
    void setST(const Register& newST);

private:
    array<Register, 6> generalRegisters;
    Register programCounter;
    Register stackPointer;
    Register statusRegister;
};

#endif // PROCESS_CONTEXT_H