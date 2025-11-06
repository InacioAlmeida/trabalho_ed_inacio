#include <stdio.h>
#include <stdlib.h>
#include "partida.h"

struct partida
{
    int id;
    int id_time1;
    int id_time2;
    int gols_time1;
    int gols_time2;
};

Partida* criar_partida(int id, int id_time1, int id_time2, int gols_time1, int gols_time2){
    Partida *p = malloc(sizeof(struct partida));

    if (p == NULL){
        printf("Erro de alocação de memória da partida");
        return NULL;
    }

    p->id = id;
    p->id_time1 = id_time1;
    p->id_time2 = id_time2;
    p->gols_time1 = gols_time1;
    p->gols_time2 = gols_time2;

    return p;
}

void deletar_partida(Partida* p){
    free(p);
}

//Implementando os getters
int partida_get_id(Partida* p){
    return p->id;
}

int partida_get_id_time1(Partida* p){
    return p->id_time1;
}

int partida_get_id_time2(Partida* p){
    return p->id_time2;
}

int partida_get_gols_time1(Partida* p){
    return p->gols_time1;
}

int partida_get_gols_time2(Partida* p){
    return p->gols_time2;
}