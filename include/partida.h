#ifndef PARTIDA_H
#define PARTIDA_H

typedef struct partida Partida;

Partida* criar_partida(int id, int id_time1, int id_time2, int gols_time1, int gols_time2);
void deletar_partida(Partida* p);

//Conjunto de getters
int partida_get_id(Partida* p);
int partida_get_id_time1(Partida* p);
int partida_get_id_time2(Partida* p);
int partida_get_gols_time1(Partida* p);
int partida_get_gols_time2(Partida* p);

#endif