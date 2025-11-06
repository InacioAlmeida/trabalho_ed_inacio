#include "bd_times.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TIMES 10 

// Renomeado para bddetimes
struct bddetimes {
    Time* times[MAX_TIMES]; 
    int count;
};

BDTimes* criar_bd_times() {
    BDTimes* bdt = malloc(sizeof(struct bddetimes));
    if (bdt != NULL) {
        bdt->count = 0;
        for (int i = 0; i < MAX_TIMES; i++) {
            bdt->times[i] = NULL;
        }
    }
    return bdt;
}

void destruir_bd_times(BDTimes* bdt) {
    if (bdt == NULL) return;
    for (int i = 0; i < bdt->count; i++) {
        // Usa a função da Parte 1 (que deixamos em português)
        deletar_time(bdt->times[i]); 
    }
    free(bdt);
}

int carregar_bd_times(BDTimes* bdt, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        printf("Erro ao abrir arquivo %s\n", filename);
        return -1; 
    }

    char buffer[256];
    fgets(buffer, sizeof(buffer), f); // Pular cabeçalho

    int id;
    char nome[100];
    
    while (fgets(buffer, sizeof(buffer), f) != NULL) {
        if (sscanf(buffer, "%d,%99[^\n]", &id, nome) == 2) {
            if (id >= 0 && id < MAX_TIMES) {
                // Usa a função da Parte 1
                Time* t = criar_time(id, nome); 
                bdt->times[id] = t; 
                bdt->count++;
            }
        }
    }

    fclose(f);
    return 0; // Sucesso
}

Time* get_time_bd_por_id(BDTimes* bdt, int id) {
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
    Time** resultados = malloc(sizeof(Time*) * MAX_TIMES);
    if (resultados == NULL) return NULL; 

    int tam_prefixo = strlen(prefixo);

    for (int i = 0; i < bdt->count; i++) {
        // Usa a função da Parte 1
        const char* nome_time = time_get_nome(bdt->times[i]); 
        
        // strncmp compara os 'n' primeiros caracteres
        if (strncmp(nome_time, prefixo, tam_prefixo) == 0) {
            resultados[*count] = bdt->times[i];
            (*count)++;
        }
    }
    
    // Lembrete: O 'main.c' (na Parte 4) será responsável por dar 'free(resultados)'!
    return resultados;
}