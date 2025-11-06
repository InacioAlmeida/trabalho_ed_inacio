#ifndef TIME_H
#define TIME_H

typedef struct time Time;

Time* criar_time(int id, const char* nome);
void deletar_time(Time* t);
void atualizar_estatisticas_time(Time* t, int gols_marcados, int gols_sofridos);

const char* time_get_nome(Time* t);
int time_get_id(Time* t);
int time_get_vitorias(Time* t);
int time_get_derrotas(Time* t);
int time_get_empates(Time* t);
int time_get_pontuacao(Time* t);
int time_get_saldoGols(Time* t);
int time_get_GM(Time* t);
int time_get_GS(Time* t);

#endif