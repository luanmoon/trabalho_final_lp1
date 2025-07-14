#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>

struct Cliente {
    static int nextId;
    int id;
    std::string nome;
    std::string telefone;

    Cliente();
};

#endif