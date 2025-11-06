#include "bd_partidas.h"
#include <stdio.h>
#include <stdlib.h>

// Ao analisar o csv, 91 partidas aconteceram, usei 100 para ser um valor seguro
#define MAX_PARTIDAS 100 

// Estrutura interna do gerenciador de partidas.
struct bddepartidas {
    Partida* partidas[MAX_PARTIDAS]; 
    int count;
};

BDPartidas* criar_bd_partidas() {
    BDPartidas* bdp = malloc(sizeof(struct bddepartidas));
    if (bdp != NULL) {
        bdp->count = 0;
        // Inicializa o vetor para evitar lixo de memória
        for (int i = 0; i < MAX_PARTIDAS; i++) {
            bdp->partidas[i] = NULL;
        }
    }
    return bdp;
}

void deletar_bd_partidas(BDPartidas* bdp) {
    if (bdp == NULL) return;
    
    // Libera cada partida individualmente
    for (int i = 0; i < bdp->count; i++) {
        deletar_partida(bdp->partidas[i]); 
    }
    // Libera o próprio gerenciador
    free(bdp);
}

int carregar_bd_partidas(BDPartidas* bdp, const char* filename) {
    FILE* f = fopen(filename, "r");
    if (f == NULL) {
        printf("Erro ao abrir arquivo %s\n", filename);
        return -1;
    }

    bdp->count = 0;
    char buffer[256];
    
    // Pula a linha do cabeçalho (ID,Time1ID,...)
    fgets(buffer, sizeof(buffer), f); 
    
    // Se o arquivo só tem cabeçalho (ex: partidas_vazio.csv), 
    // o 'while' não roda, e o 'count' fica 0 (o que está correto).

    int id, id1, id2, gols1, gols2;
    
    // Lê o arquivo linha por linha usando fscanf
    while (fscanf(f, "%d,%d,%d,%d,%d", &id, &id1, &id2, &gols1, &gols2) == 5) {
        if (bdp->count < MAX_PARTIDAS) {
            // Cria a partida e armazena no vetor
            Partida* p = criar_partida(id, id1, id2, gols1, gols2); 
            bdp->partidas[bdp->count] = p;
            bdp->count++;
        }
    }

    fclose(f);
    return 0;
}

Partida** get_todas_partidas_bd(BDPartidas* bdp, int* count) {
    *count = bdp->count;
    return bdp->partidas;
}