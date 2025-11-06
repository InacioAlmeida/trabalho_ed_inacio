#ifndef BD_TIMES_H
#define BD_TIMES_H

#include "time.h" 

/*
 * Definição do TAD BDTimes (Gerenciador de Times).
 * Este TAD é responsável por carregar e armazenar em memória
 * a coleção de todos os times lidos do arquivo .csv.
 */

typedef struct bddetimes BDTimes;

/*
 * Cria uma nova instância do gerenciador de times.
 * Retorna um ponteiro para o BDTimes alocado, ou NULL em caso de erro.
 */
BDTimes* criar_bd_times();

/*
 * Libera/desaloca a memória do gerenciador e de todos os times que ele contém.
 */
void deletar_bd_times(BDTimes* bdt);

/*
 * Carrega os dados de times de um arquivo .csv para a memória.
 * Retorna 0 em caso de sucesso, ou -1 em caso de erro.
 */
int carregar_bd_times(BDTimes* bdt, const char* filename);

/* --- Funções de Acesso --- */

/* Busca um time pelo seu ID. */
Time* get_time_bd_por_id(BDTimes* bdt, int id);

/* Retorna um ponteiro para o vetor de todos os times carregados. */
Time** get_todos_times_bd(BDTimes* bdt, int* count); 

/*
 * Busca times cujos nomes começam com um dado prefixo.
 *
 * ATENÇÃO: Esta função aloca um novo vetor (Time**) para os resultados.
 * O chamador é responsável por dar `free()` neste vetor de resultados.
 *
 * O ponteiro 'count' será preenchido com o número de times encontrados.
 * Retorna o ponteiro para o vetor de resultados (alocado dinamicamente).
 */
Time** get_times_bd_por_prefixo(BDTimes* bdt, const char* prefixo, int* count);

#endif