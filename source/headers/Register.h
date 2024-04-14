//
// Created by gabri on 14/04/2024.
//

#ifndef REGISTER_H
#define REGISTER_H

#include <array>

// Classe que representa um registrador do processador
class Register {
public:

    Register();

    std::array<unsigned char, 8> getContent() const;

    void setContent(const std::array<unsigned char, 8> &newContent);

private:
    std::array<unsigned char, 8> content;
};

#endif //REGISTER_H
