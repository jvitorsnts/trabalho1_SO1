//
// Created by gabri on 14/04/2024.
//

#include "../headers/Processor.h"

Processor::Processor() {
    registers = std::array<Register, 6>();
    SP = Register();
    PC = Register();
    ST = Register();
}

std::array<Register, 6> Processor::getRegisters() const {
    return registers;
}

Register Processor::getSP() const {
    return SP;
}

Register Processor::getPC() const {
    return PC;
}

Register Processor::getST() const {
    return ST;
}

void Processor::setRegisters(const std::array<Register, 6> &newRegisters) {
    registers = newRegisters;
}

void Processor::setSP(const Register &newSP) {
    SP = newSP;
}

void Processor::setPC(const Register &newPC) {
    PC = newPC;
}

void Processor::setST(const Register &newST) {
    ST = newST;
}