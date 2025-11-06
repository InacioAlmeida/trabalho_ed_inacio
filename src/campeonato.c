#include "campeonato.h"
#include <stdlib.h>

// Note que este .c não precisa de stdlib ou string,
// pois ele apenas "orquestra" os outros TADs.
// Ele usa as funções públicas que já criamos.

void campeonato_calcular_estatisticas(BDTimes* bdt, BDPartidas* bdp) {
    int num_partidas = 0;
    
    // 1. Pega o vetor de todas as partidas (função da Parte 2)
    Partida** todas_partidas = get_todas_partidas_bd(bdp, &num_partidas);
    
    // Se num_partidas for 0 (ex: partidas_vazio.csv), 

    // 2. Itera por cada partida
    for (int i = 0; i < num_partidas; i++) {
        Partida* p = todas_partidas[i];

        // 3. Pega os dados da partida (funções da Parte 1)
        int id_time1 = partida_get_id_time1(p);
        int id_time2 = partida_get_id_time2(p);
        int gols_time1 = partida_get_gols_time1(p);
        int gols_time2 = partida_get_gols_time2(p);

        // 4. Busca os ponteiros para os times (função da Parte 2)
        Time* time1 = get_time_bd_por_id(bdt, id_time1);
        Time* time2 = get_time_bd_por_id(bdt, id_time2);

        // 5. Atualiza as estatísticas de AMBOS os times (função da Parte 1)
        if (time1 != NULL && time2 != NULL) {
            
            // Atualiza o Time 1:
            // Ele marcou 'gols_time1' e sofreu 'gols_time2'
            atualizar_estatisticas_time(time1, gols_time1, gols_time2);

            // Atualiza o Time 2:
            // Ele marcou 'gols_time2' e sofreu 'gols_time1'
            atualizar_estatisticas_time(time2, gols_time2, gols_time1);
        }
    }
    
    // Ao final deste loop, o 'bdt' (BDTimes) está com todas as
    // estatísticas (V, E, D, GM, GS) corretamente calculadas.
}