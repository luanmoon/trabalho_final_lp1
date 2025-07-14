#ifndef CORRETOR_H
#define CORRETOR_H

#include <string>
#include <vector>
#include <utility> 

struct Corretor {
    static int nextId;
    int id;
    std::string nome;
    std::string telefone;
    bool avaliador;
    double lat, lng;
    
    // Armazena os imóveis 
    std::vector<int> imoveis_para_avaliar_ids;
    
    // Armazena o agendamento final
    std::vector<std::pair<int, int>> agenda;

    Corretor();
};

#endif