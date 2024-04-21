
//
// Created by joao on 19/04/24.
//

#include "../headers/ProcessContext.h"

using namespace std;

ProcessContext::ProcessContext() {
    generalRegisters = array<Register, 6>();
    programCounter = Register();
    stackPointer = Register();
    statusRegister = Register();
}

array<Register, 6> ProcessContext::getGeneralRegisters() const {
    return generalRegisters;
}

Register ProcessContext::getPC() const {
    return programCounter;
}

Register ProcessContext::getSP() const {
    return stackPointer;
}

Register ProcessContext::getST() const {
    return statusRegister;
}

void ProcessContext::setGeneralRegisters(const std::array<Register, 6>& newGeneralRegisters) {
    generalRegisters = newGeneralRegisters;
}

void ProcessContext::setPC(const Register& newPC) {
    programCounter = newPC;
}

void ProcessContext::setSP(const Register& newSP) {
    stackPointer = newSP;
}

void ProcessContext::setST(const Register& newST) {
    statusRegister = newST;
}
