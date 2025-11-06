#ifndef CAMPEONATO_H
#define CAMPEONATO_H

#include "bd_times.h"
#include "bd_partidas.h"

/**
 * @brief Processa todas as partidas e atualiza as estatísticas (V, E, D, GM, GS)
 * de cada time no banco de dados de times.
 * * @param bdt O ponteiro para o BDTimes (que contém os times a serem atualizados).
 * @param bdp O ponteiro para o BDPartidas (que contém os resultados dos jogos).
 */
void campeonato_calcular_estatisticas(BDTimes* bdt, BDPartidas* bdp);

#endif