#ifndef TIME_H
#define TIME_H

/*
 * Definição do TAD Time.
 * Este TAD modela uma única equipe de futebol, encapsulando
 * seus dados de identificação (ID, Nome) e estatísticas
 * acumuladas (Vitórias, Empates, Derrotdas, Gols Marcados, Gols sofridos).
 */

typedef struct time Time;

/*
 * Cria uma nova instância de Time.
 * Retorna um ponteiro para o Time alocado, ou NULL em caso de erro.
 */
Time* criar_time(int id, const char* nome);

// Libera a memória alocada para um Time
void deletar_time(Time* t);

/*
 * Atualiza as estatísticas de um time com base no resultado de um jogo.
 * Recebe os gols que o time fez e os gols que sofreu na partida.
 */
void atualizar_estatisticas_time(Time* t, int gols_marcados, int gols_sofridos);

// --- Funções Getters ---

const char* time_get_nome(Time* t);
int time_get_id(Time* t);
int time_get_vitorias(Time* t);
int time_get_derrotas(Time* t);
int time_get_empates(Time* t);

// Retorna a pontuação total do time (3 * V + E).
int time_get_pontuacao(Time* t);

// Retorna o saldo de gols do time (GM - GS).
int time_get_saldoGols(Time* t);

int time_get_GM(Time* t);
int time_get_GS(Time* t);

#endif