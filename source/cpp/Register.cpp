
//
// Created by joao 19/04/24.
//
#include <array>
#include "../headers/Register.h"

using namespace std;

Register::Register() {
    content = array<unsigned char, 8>();
}

array<unsigned char, 8> Register::getContent() const {
    return content;
}

array<unsigned char, 8> content;

void Register::setContent(const array<unsigned char, 8> &newContent) {
    content = newContent;
}
