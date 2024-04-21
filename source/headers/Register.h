#ifndef REGISTER_H
#define REGISTER_H

#include <array>

using namespace std;

class Register {
public:
    Register();

    // Retorna o conteúdo do registrador.
    array<unsigned char, 8> getContent() const;

    // Armazena o conteúdo do registrador.
    void setContent(const std::array<unsigned char, 8> &newContent);

private:
    array<unsigned char, 8> content;
};


#endif //REGISTER_H
