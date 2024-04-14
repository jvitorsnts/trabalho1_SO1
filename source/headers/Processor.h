//
// Created by gabri on 14/04/2024.
//

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <array>
#include "Register.h"

class Processor {
public:

    Processor();

    std::array<Register, 6> getRegisters() const; // 6 registradores de propósito geral
    // SP (stack pointer), PC (program counter) e ST (status)
    Register getSP() const;
    Register getPC() const;
    Register getST() const;

    void setRegisters(const std::array<Register, 6> &newRegisters);
    void setSP(const Register &newSP);
    void setPC(const Register &newPC);
    void setST(const Register &newST);

private:

    std::array<Register, 6> registers;
    Register SP;
    Register PC;
    Register ST;

};



#endif //PROCESSOR_H
