#include "bd_partidas.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_PARTIDAS 100 

struct bddepartidas {
    Partida* partidas[MAX_PARTIDAS]; 
    int count;
};

BDPartidas* criar_bd_partidas() {
    BDPartidas* bdp = malloc(sizeof(struct bddepartidas));
    if (bdp != NULL) {
        bdp->count = 0;
        for (int i = 0; i < MAX_PARTIDAS; i++) {
            bdp->partidas[i] = NULL;
        }
    }
    return bdp;
}

void destruir_bd_partidas(BDPartidas* bdp) {
    if (bdp == NULL) return;
    for (int i = 0; i < bdp->count; i++) {
        // Usa a função da Parte 1
        deletar_partida(bdp->partidas[i]); 
    }
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
    
    // Pular o cabeçalho
    fgets(buffer, sizeof(buffer), f); 
    
    // Se o arquivo só tem cabeçalho, o 'while' não roda,
    // e o 'count' fica 0, o que está correto.

    int id, id1, id2, gols1, gols2;
    
    while (fscanf(f, "%d,%d,%d,%d,%d", &id, &id1, &id2, &gols1, &gols2) == 5) {
        if (bdp->count < MAX_PARTIDAS) {
            // Usa a função da Parte 1
            Partida* p = criar_partida(id, id1, id2, gols1, gols2); 
            bdp->partidas[bdp->count] = p;
            bdp->count++;
        }
    }

    fclose(f);
    return 0; // Sucesso
}

Partida** get_todas_partidas_bd(BDPartidas* bdp, int* count) {
    *count = bdp->count;
    return bdp->partidas;
}