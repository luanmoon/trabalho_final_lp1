#ifndef IMOVEL_H
#define IMOVEL_H

#include <string>

enum class TipoImovel { Casa, Apartamento, Terreno };

struct Imovel {
    static int nextId;
    int id;
    TipoImovel tipo;
    int proprietarioId;
    double lat, lng;
    double preco;
    std::string endereco;

    Imovel(); 
};

#endif