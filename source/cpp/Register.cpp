//
// Created by gabri on 14/04/2024.
//

#include "../headers/Register.h"
#include <array>

Register::Register() {
    content = std::array<unsigned char, 8>();
}

std::array<unsigned char, 8> Register::getContent() const {
    return content;
}

void Register::setContent(const std::array<unsigned char, 8> &newContent) {
    content = newContent;
}

std::array<unsigned char, 8> content;
