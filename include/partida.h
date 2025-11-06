#ifndef PARTIDA_H
#define PARTIDA_H

/*
 * Definição do TAD Partida.
 * Este TAD modela uma única partida de futebol, encapsulando
 * seus dados de identificação e placar.
 */

// Tipo opaco para a struct Partida
typedef struct partida Partida;

/*
 * Cria uma nova instância de Partida.
 * Retorna um ponteiro para a Partida alocada, ou NULL em caso de erro.
 */
Partida* criar_partida(int id, int id_time1, int id_time2, int gols_time1, int gols_time2);

//Libera a memória alocada para uma Partida.
 
void deletar_partida(Partida* p);

// --- Funções Getters ---
int partida_get_id(Partida* p);
int partida_get_id_time1(Partida* p);
int partida_get_id_time2(Partida* p);
int partida_get_gols_time1(Partida* p);
int partida_get_gols_time2(Partida* p);

#endif