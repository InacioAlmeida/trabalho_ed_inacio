#ifndef BD_PARTIDAS_H
#define BD_PARTIDAS_H

#include "partida.h" 

// Renomeado para BDPartidas
typedef struct bddepartidas BDPartidas;

// Construtor/Destrutor
BDPartidas* criar_bd_partidas();
void destruir_bd_partidas(BDPartidas* bdp);

// Função de carga
int carregar_bd_partidas(BDPartidas* bdp, const char* filename);

// Função de acesso
Partida** get_todas_partidas_bd(BDPartidas* bdp, int* count);

#endif