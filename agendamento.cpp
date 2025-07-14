#include "agendamento.h"
#include "distancia.h"
#include <algorithm>
#include <limits>
#include <cmath>
#include <map>

void distribuir_imoveis(std::vector<Corretor>& corretores, const std::vector<Imovel>& imoveis) {
    std::vector<Corretor*> avaliadores;
    for (Corretor& corretor : corretores) {
        if (corretor.avaliador) {
            avaliadores.push_back(&corretor);
        }
    }

    if (avaliadores.empty()) {
        return; 
    }

    size_t avaliador_idx = 0;
    for (const Imovel& imovel : imoveis) {
        avaliadores[avaliador_idx]->imoveis_para_avaliar_ids.push_back(imovel.id);
        avaliador_idx = (avaliador_idx + 1) % avaliadores.size();
    }
}

void calcular_rotas(std::vector<Corretor>& corretores, const std::vector<Imovel>& imoveis) {
    std::map<int, const Imovel*> mapa_imoveis;
    for (const auto& imovel : imoveis) {
        mapa_imoveis[imovel.id] = &imovel;
    }

    for (Corretor& corretor : corretores) {
        if (!corretor.avaliador || corretor.imoveis_para_avaliar_ids.empty()) {
            continue;
        }

        std::vector<int> imoveis_a_visitar = corretor.imoveis_para_avaliar_ids;
        double current_lat = corretor.lat;
        double current_lng = corretor.lng;
        int tempo_atual_min = 9 * 60;

        while (!imoveis_a_visitar.empty()) {
            // Encontrar o imóvel não visitado mais próximo
            int proximo_imovel_id = -1;
            size_t proximo_imovel_idx_no_vetor = -1;
            double min_dist = std::numeric_limits<double>::max();

            for (size_t i = 0; i < imoveis_a_visitar.size(); ++i) {
                const Imovel* imovel_candidato = mapa_imoveis.at(imoveis_a_visitar[i]);
                double dist = haversine(current_lat, current_lng, imovel_candidato->lat, imovel_candidato->lng);
                
                if (dist < min_dist) {
                    min_dist = dist;
                    proximo_imovel_id = imovel_candidato->id;
                    proximo_imovel_idx_no_vetor = i;
                }
            }
            
            // Atualizar tempo e agendar
            int tempo_deslocamento = static_cast<int>(min_dist * 2.0);
            tempo_atual_min += tempo_deslocamento;
            
            corretor.agenda.push_back({proximo_imovel_id, tempo_atual_min});

            // Atualizar o tempo para o fim da avaliação
            tempo_atual_min += 60; 

            // Atualiza a localização atual para o imóvel visitado
            const Imovel* imovel_visitado = mapa_imoveis.at(proximo_imovel_id);
            current_lat = imovel_visitado->lat;
            current_lng = imovel_visitado->lng;
            
            // Remove imóvel da lista de visita
            imoveis_a_visitar.erase(imoveis_a_visitar.begin() + proximo_imovel_idx_no_vetor);
        }
    }
}

void processar_agendamento(std::vector<Corretor>& corretores, const std::vector<Imovel>& imoveis) {
    distribuir_imoveis(corretores, imoveis);
    calcular_rotas(corretores, imoveis);
}