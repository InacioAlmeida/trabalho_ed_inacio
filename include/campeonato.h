#ifndef CAMPEONATO_H
#define CAMPEONATO_H

#include "bd_times.h"
#include "bd_partidas.h"

/*
 * Processa todas as partidas e atualiza as estatísticas (V, E, D, GM, GS)
 * de cada time no banco de dados de times (BDTimes).
 */
void campeonato_calcular_estatisticas(BDTimes* bdt, BDPartidas* bdp);

#endif