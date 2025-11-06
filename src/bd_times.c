#include "bd_times.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// O PDF especifica 10 clubes
#define MAX_TIMES 10 

// Estrutura interna do gerenciador de times.
struct bddetimes {
    Time* times[MAX_TIMES]; // Usa um vetor estático de ponteiros
    int count;
};

BDTimes* criar_bd_times() {
    BDTimes* bdt = malloc(sizeof(struct bddetimes));
    if (bdt != NULL) {
        bdt->count = 0;
        // Inicializa o vetor
        for (int i = 0; i < MAX_TIMES; i++) {
            bdt->times[i] = NULL;
        }
    }
    return bdt;
}

void deletar_bd_times(BDTimes* bdt) {
    if (bdt == NULL) return;

    // Libera cada time individualmente
    for (int i = 0; i < bdt->count; i++) {
        deletar_time(bdt->times[i]); 
    }
    // Libera o gerenciador
    free(bdt);
}

int carregar_bd_times(BDTimes* bdt, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        printf("Erro ao abrir arquivo %s\n", filename);
        return -1; 
    }

    char buffer[256];
    // Pula a linha do cabeçalho (ID,Nome)
    fgets(buffer, sizeof(buffer), f); 

    int id;
    char nome[100];
    
    // Lê o arquivo linha por linha
    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        // Usa sscanf para extrair dados do buffer
        // %99[^\n] lê uma string de até 99 chars que não contenha a quebra de linha
        if (sscanf(buffer, "%d,%99[^\n]", &id, nome) == 2) {
            if (id >= 0 && id < MAX_TIMES) {
                // Cria o time 
                Time* t = criar_time(id, nome); 
                // Armazena no vetor usando o ID como índice
                bdt->times[id] = t; 
                bdt->count++;
            }
        }
    }

    fclose(f);
    return 0; // Se rodou é pq obteve Sucesso
}

Time* get_time_bd_por_id(BDTimes* bdt, int id) {
    // Acesso direto O(1)
    if (id >= 0 && id < bdt->count) {
        return bdt->times[id];
    }
    return NULL;
}

Time** get_todos_times_bd(BDTimes* bdt, int* count) {
    *count = bdt->count;
    return bdt->times;
}

Time** get_times_bd_por_prefixo(BDTimes* bdt, const char* prefixo, int* count) {
    *count = 0;
    
    // Aloca um vetor de resultados. O chamador DEVE liberar isso.
    Time** resultados = malloc(sizeof(Time*) * MAX_TIMES);
    if (resultados == NULL) return NULL; 

    int tam_prefixo = strlen(prefixo);

    for (int i = 0; i < bdt->count; i++) {
        const char* nome_time = time_get_nome(bdt->times[i]); 
        
        // Compara apenas os primeiros 'tam_prefixo' caracteres
        if (strncmp(nome_time, prefixo, tam_prefixo) == 0) {
            resultados[*count] = bdt->times[i];
            (*count)++;
        }
    }

    return resultados;
}