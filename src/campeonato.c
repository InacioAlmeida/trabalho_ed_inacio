//Implementação da lógica de negócio central do campeonato.

#include "campeonato.h"
#include <stdlib.h> // Para NULL

void campeonato_calcular_estatisticas(BDTimes* bdt, BDPartidas* bdp) {
    int num_partidas = 0;
    
    // 1. Pega o vetor de todas as partidas (função da Parte 2)
    Partida** todas_partidas = get_todas_partidas_bd(bdp, &num_partidas);
    
    // Se num_partidas for 0 (ex: partidas_vazio.csv), o loop não roda,
    // (o que está correto).

    // 2. Itera por cada partida
    for (int i = 0; i < num_partidas; i++) {
        Partida* p = todas_partidas[i];

        // 3. Pega os dados da partida 
        int id_time1 = partida_get_id_time1(p);
        int id_time2 = partida_get_id_time2(p);
        int gols_time1 = partida_get_gols_time1(p);
        int gols_time2 = partida_get_gols_time2(p);

        // 4. Busca os ponteiros para os times 
        Time* time1 = get_time_bd_por_id(bdt, id_time1);
        Time* time2 = get_time_bd_por_id(bdt, id_time2);

        // 5. Atualiza as estatísticas de AMBOS os times
        if (time1 != NULL && time2 != NULL) {
            
            // Atualiza o Time 1:
            // Ele marcou 'gols_time1' e sofreu 'gols_time2'
            atualizar_estatisticas_time(time1, gols_time1, gols_time2);

            // Atualiza o Time 2:
            // Ex: ele marcou 'gols_time2' e sofreu 'gols_time1'
            atualizar_estatisticas_time(time2, gols_time2, gols_time1);
        }
    }
    
    // Ao final deste loop, o 'bdt' (BDTimes) está com todas as
    // estatísticas (V, E, D, GM, GS) corretamente calculadas.
}