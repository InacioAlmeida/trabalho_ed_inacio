#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Para toupper()
#include <stdbool.h> // Para usar valores booleanos (true/false)

// TADs criados
#include "time.h"
#include "partida.h"
#include "bd_times.h"
#include "bd_partidas.h"
#include "campeonato.h"

// --- Protótipos das Funções Auxiliares ---

void limpar_tela();
void pausar_tela();
char ler_opcao();
void imprimir_menu_principal();
void imprimir_cabecalho_tabela();

// Funções para cada opção do menu
void handle_consultar_time(BDTimes* bdt);
void handle_consultar_partidas(BDTimes* bdt, BDPartidas* bdp);
void handle_imprimir_tabela(BDTimes* bdt);

// --- Função Principal ---

int main() {
    // 1. Inicialização
    BDTimes* bdt = criar_bd_times();
    BDPartidas* bdp = criar_bd_partidas();

    if (bdt == NULL || bdp == NULL) {
        printf("Erro fatal: Falha ao alocar memória para os gerenciadores.\n");
        return 1;
    }

    // 2. Carga
    if (carregar_bd_times(bdt, "dados/times.csv") != 0) {
        printf("Erro ao carregar times.csv. Verifique se o arquivo existe.\n");
        return 1;
    }
    if (carregar_bd_partidas(bdp, "dados/partidas_vazio.csv") != 0) {
        printf("Erro ao carregar partidas.csv. Verifique se o arquivo existe.\n");
        return 1;
    }

    // 3. Processamento
    // Calcula Vitórias, Empates, Derrotas, Gols Marcos, Gols sofridos de todos os times
    campeonato_calcular_estatisticas(bdt, bdp);

    // 4. Loop Principal (UI)
    char opcao;
    do {
        limpar_tela();
        imprimir_menu_principal();
        opcao = ler_opcao();

        switch (opcao) {
            case '1':
                handle_consultar_time(bdt);
                pausar_tela();
                break;
            case '2':
                handle_consultar_partidas(bdt, bdp);
                pausar_tela();
                break;
            case '3':
            case '4':
            case '5':
                printf("\nOpção desabilitada nesta entrega (Parte I).\n");
                pausar_tela();
                break;
            case '6':
                handle_imprimir_tabela(bdt);
                pausar_tela();
                break;
            case 'Q':
                printf("\nEncerrando o sistema...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                pausar_tela();
                break;
        }

    } while (opcao != 'Q');


    // 5. Limpeza (Destroy)
    destruir_bd_times(bdt);
    destruir_bd_partidas(bdp);

    return 0;
}

//1° opção do menu: Consulta time por prefixo.
void handle_consultar_time(BDTimes* bdt) {
    char prefixo[100];
    printf("\n--- Consultar Time ---\n");
    printf("Digite o nome ou prefixo do time: ");
    
    if (fgets(prefixo, sizeof(prefixo), stdin) == NULL) {
        return; // Trata erro ou EOF
    }
    // Remove o '\n' que o fgets deixa no final
    prefixo[strcspn(prefixo, "\n")] = 0;

    int num_encontrados = 0;
    Time** encontrados = get_times_bd_por_prefixo(bdt, prefixo, &num_encontrados);

    if (num_encontrados == 0) {
        printf("Nenhum time encontrado com o prefixo '%s'.\n", prefixo);
        free(encontrados);
        return;
    }

    imprimir_cabecalho_tabela();
    for (int i = 0; i < num_encontrados; i++) {
        Time* t = encontrados[i];
        printf("%-3d %-10s %-3d %-3d %-3d %-3d %-3d %-3d %-3d\n",
               time_get_id(t),
               time_get_nome(t),
               time_get_vitorias(t),
               time_get_empates(t),
               time_get_derrotas(t),
               time_get_GM(t),
               time_get_GS(t),
               time_get_saldoGols(t),
               time_get_pontuacao(t));
    }
    free(encontrados);
}

//Opção 2: Consulta partidas por time.
void handle_consultar_partidas(BDTimes* bdt, BDPartidas* bdp) {
    printf("\n--- Consultar Partidas ---\n");
    printf("1 - Por time mandante\n");
    printf("2 - Por time visitante\n");
    printf("3 - Por time mandante ou visitante\n");
    printf("4 - Retornar ao menu principal\n");
    printf("Escolha o modo de consulta: ");
    
    char sub_opcao = ler_opcao();
    if (sub_opcao == '4') return;
    if (sub_opcao < '1' || sub_opcao > '3') {
        printf("Opção inválida.\n");
        return;
    }

    char prefixo[100];
    printf("Digite o nome ou prefixo do time: ");
    
    if (fgets(prefixo, sizeof(prefixo), stdin) == NULL) {
        return; // Trata erro ou EOF
    }
    // Remove o '\n' que o fgets deixa no final
    prefixo[strcspn(prefixo, "\n")] = 0;

    // 1. Achar os times que correspondem ao prefixo
    int num_times_filtro = 0;
    Time** times_filtro = get_times_bd_por_prefixo(bdt, prefixo, &num_times_filtro);

    if (num_times_filtro == 0) {
        printf("Nenhum time encontrado com o prefixo '%s'.\n", prefixo);
        free(times_filtro);
        return;
    }

    // 2. Pegar todas as partidas
    int num_partidas_total = 0;
    Partida** todas_partidas = get_todas_partidas_bd(bdp, &num_partidas_total);

    // 3. Iterar e filtrar
    int partidas_encontradas_count = 0;
    printf("\nPartidas encontradas:\n");
    printf("ID  Time1        x   Time2\n");
    printf("----------------------------------\n");

    for (int i = 0; i < num_partidas_total; i++) {
        Partida* p = todas_partidas[i];
        int id_time1 = partida_get_id_time1(p);
        int id_time2 = partida_get_id_time2(p);

        bool partida_time1 = false;
        bool partida_time2 = false;

        for (int j = 0; j < num_times_filtro; j++) {
            int id_filtro = time_get_id(times_filtro[j]);
            if (id_time1 == id_filtro) partida_time1 = true;
            if (id_time2 == id_filtro) partida_time2 = true;
        }

        bool imprimir = false;
        if (sub_opcao == '1' && partida_time1) imprimir = true;
        if (sub_opcao == '2' && partida_time2) imprimir = true;
        if (sub_opcao == '3' && (partida_time1 || partida_time2)) imprimir = true;

        if (imprimir) {
            Time* time1 = get_time_bd_por_id(bdt, id_time1);
            Time* time2 = get_time_bd_por_id(bdt, id_time2);
            printf("%-3d %-10s %d x %d %-10s\n",
                   partida_get_id(p),
                   time_get_nome(time1),
                   partida_get_gols_time1(p),
                   partida_get_gols_time2(p),
                   time_get_nome(time2));
            partidas_encontradas_count++;
        }
    }

    if (partidas_encontradas_count == 0) {
        printf("Nenhuma partida encontrada para os critérios.\n");
    }

    free(times_filtro);
}

// 6° opção do menu: Imprime a tabela de classificação
void handle_imprimir_tabela(BDTimes* bdt) {
    int num_times = 0;
    Time** todos_times = get_todos_times_bd(bdt, &num_times);

    if (num_times == 0) {
        printf("Nenhum time cadastrado.\n");
        return;
    }

    printf("\n--- Tabela de Classificação (Por ID) ---\n");
    imprimir_cabecalho_tabela();
    
    for (int i = 0; i < num_times; i++) {
        // Como carregamos os times usando o ID como índice,
        // o vetor todos_times[i] já está na ordem de ID 0, 1, 2...
        Time* t = todos_times[i];
        
        printf("%-3d %-10s %-3d %-3d %-3d %-3d %-3d %-3d %-3d\n",
               time_get_id(t),
               time_get_nome(t),
               time_get_vitorias(t),      // V
               time_get_empates(t),       // E
               time_get_derrotas(t),      // D
               time_get_GM(t),            // GM
               time_get_GS(t),            // GS
               time_get_saldoGols(t),     // S
               time_get_pontuacao(t));    // PG
    }
}

// --- Funções Utilitárias ---

void imprimir_menu_principal() {
    printf("==========================================\n");
    printf(" Sistema de Gerenciamento de Partidas\n");
    printf("==========================================\n");
    printf("1 - Consultar time\n");
    printf("2 - Consultar partidas\n");
    printf("3 - Atualizar partida (N/A)\n");
    printf("4 - Remover partida (N/A)\n");
    printf("5 - Inserir partida (N/A)\n");
    printf("6 - Imprimir tabela de classificação\n");
    printf("Q - Sair\n");
    printf("==========================================\n");
    printf("Escolha uma opção: ");
}

void imprimir_cabecalho_tabela() {
    // Cabeçalho para Opção 1 e 6
    printf("------------------------------------------------------------------\n");
    printf("%-3s %-10s %-3s %-3s %-3s %-3s %-3s %-3s %-3s\n",
           "ID", "Time", "V", "E", "D", "GM", "GS", "S", "PG");
    printf("------------------------------------------------------------------\n");
}

char ler_opcao() {
    char buffer[10];
    // Usei fgets por ser mais seguro e porque estava gerando erros (descobri isso com GPT e em foruns)
    if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        // Pega o primeiro caractere e o converte para maiúsculo (similar ao .upper() do py)
        return toupper(buffer[0]);
    }
    return '\0'; // Retorna nulo em caso de erro
}

void limpar_tela() {
    // Limpar console (tambem uso o ubuntu professor xD, I <3 Tux)
    system("clear"); 
}

void pausar_tela() {
    printf("\nPressione Enter para continuar...");
    // Limpa o buffer de entrada
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    // Espera pelo Enter
    getchar();
}