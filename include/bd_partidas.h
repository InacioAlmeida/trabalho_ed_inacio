#ifndef BD_PARTIDAS_H
#define BD_PARTIDAS_H

#include "partida.h" 

/*
 * Definição do TAD BDPartidas (Gerenciador de Partidas).
 * Este TAD é responsável por carregar e armazenar em memória
 * a coleção de todas as partidas lidas do arquivo .csv.
 */

typedef struct bddepartidas BDPartidas;

/*
 * Cria uma nova instância do gerenciador de partidas.
 * Retorna um ponteiro para o BDPartidas alocado, ou NULL em caso de erro.
 */
BDPartidas* criar_bd_partidas();

//Libera a memória do gerenciador e de todas as partidas que ele contém.
void deletar_bd_partidas(BDPartidas* bdp);

/*
 * Carrega os dados de partidas de um arquivo .csv para a memória.
 * Retorna 0 em caso de sucesso, ou -1 em caso de erro.
 */
int carregar_bd_partidas(BDPartidas* bdp, const char* filename);

/*
 * Retorna um ponteiro para o vetor de todas as partidas carregadas.
 * O ponteiro 'count' será preenchido com o número de partidas no vetor.
 */
Partida** get_todas_partidas_bd(BDPartidas* bdp, int* count);

#endif