#ifndef BD_TIMES_H
#define BD_TIMES_H

#include "time.h" 

// Renomeado para BDTimes (em vez de bd_times)
typedef struct bddetimes BDTimes;

// Construtor/Destrutor
BDTimes* criar_bd_times();
void destruir_bd_times(BDTimes* bdt);

// Função de carga
int carregar_bd_times(BDTimes* bdt, const char* filename);

// Funções de acesso (Getters)
Time* get_time_bd_por_id(BDTimes* bdt, int id);
Time** get_todos_times_bd(BDTimes* bdt, int* count); 
Time** get_times_bd_por_prefixo(BDTimes* bdt, const char* prefixo, int* count);

#endif