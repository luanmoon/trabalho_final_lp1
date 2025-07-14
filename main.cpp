#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdexcept>

#include "corretor.h"
#include "cliente.h"
#include "imovel.h"
#include "agendamento.h"

TipoImovel string_para_tipo(const std::string& s) {
    if (s == "Casa") return TipoImovel::Casa;
    if (s == "Apartamento") return TipoImovel::Apartamento;
    if (s == "Terreno") return TipoImovel::Terreno;
    throw std::invalid_argument("Tipo de imóvel desconhecido: " + s);
}

void ler_corretores(int n, std::vector<Corretor>& corretores) {
    for (int i = 0; i < n; ++i) {
        Corretor c;
        int avaliador_bool;
        std::cin >> c.telefone >> avaliador_bool >> c.lat >> c.lng;
        c.avaliador = (avaliador_bool == 1);
        std::getline(std::cin >> std::ws, c.nome);
        corretores.push_back(c);
    }
}

void ler_clientes(int n, std::vector<Cliente>& clientes) {
    for (int i = 0; i < n; ++i) {
        Cliente c;
        std::cin >> c.telefone;
        std::getline(std::cin >> std::ws, c.nome);
        clientes.push_back(c);
    }
}

void ler_imoveis(int n, std::vector<Imovel>& imoveis) {
    for (int i = 0; i < n; ++i) {
        Imovel im;
        std::string tipo_str;
        std::cin >> tipo_str >> im.proprietarioId >> im.lat >> im.lng >> im.preco;
        im.tipo = string_para_tipo(tipo_str);
        std::getline(std::cin >> std::ws, im.endereco);
        imoveis.push_back(im);
    }
}

void imprimir_saida(const std::vector<Corretor>& corretores) {
    bool primeira_saida = true;
    for (const auto& corretor : corretores) {
        if (corretor.avaliador && !corretor.agenda.empty()) {
            if (!primeira_saida) {
                std::cout << std::endl;
            }
            std::cout << "Corretor " << corretor.id << std::endl;
            for (const auto& agendamento : corretor.agenda) {
                int id_imovel = agendamento.first;
                int tempo_total_min = agendamento.second;
                int hora = tempo_total_min / 60;
                int minuto = tempo_total_min % 60;

                std::cout << std::setfill('0') << std::setw(2) << hora << ":"
                          << std::setw(2) << minuto << " Imóvel " << id_imovel << std::endl;
            }
            primeira_saida = false;
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::vector<Corretor> corretores;
    std::vector<Cliente> clientes;
    std::vector<Imovel> imoveis;

    int num_corretores, num_clientes, num_imoveis;

    std::cin >> num_corretores;
    ler_corretores(num_corretores, corretores);

    std::cin >> num_clientes;
    ler_clientes(num_clientes, clientes);

    std::cin >> num_imoveis;
    ler_imoveis(num_imoveis, imoveis);

    processar_agendamento(corretores, imoveis);

    imprimir_saida(corretores);

    return 0;
}