# 🏆 Trabalho Prático - Campeonato Computacional de Futebol (Parte I)

Este projeto é um sistema de linha de comando (CLI) desenvolvido em C para gerenciamento e consulta de dados de um campeonato de futebol.

O sistema carrega os dados de times e partidas a partir de arquivos `.csv`, processa os resultados em memória (calculando vitórias, empates, derrotas, gols, etc.) e fornece ao usuário uma interface baseada em menu para consultar essas estatísticas.

Este projeto foi desenvolvido como parte de um trabalho acadêmico e implementa os requisitos da "Parte I" (foco em leitura, processamento e consulta).

## 🚀 Funcionalidades Implementadas

* **Carregamento de Dados:** Lê os arquivos `times.csv` e `partidas_completo.csv` da pasta `dados/` para a memória na inicialização.
* **Cálculo de Estatísticas:** Processa todas as partidas carregadas para calcular e acumular:
    * Vitórias (V), Empates (E), Derrotas (D)
    * Gols Marcados (GM), Gols Sofridos (GS)
    * Saldo de Gols (S) e Pontos Ganhos (PG)
* **Menu Interativo:** Exibe um menu de opções para o usuário.
* **Opção 1: Consultar Time:** Permite ao usuário buscar o desempenho de um time usando um nome ou prefixo.
* **Opção 2: Consultar Partidas:** Permite ao usuário buscar partidas específicas por time (mandante, visitante ou ambos).
* **Opção 6: Imprimir Tabela:** Exibe a tabela de classificação completa, ordenada por ID do time.
* **Gerenciamento de Memória:** Todo o `malloc` é pareado com um `free`, garantindo que não haja vazamentos de memória (`memory leaks`) na saída.

## 📂 Estrutura de Arquivos

O projeto está organizado na seguinte estrutura de pastas para modularidade:

```
trabalho_1/
├── Makefile               # Controla a compilação
├── include/               # Arquivo contendo todos os headers dos TADs criados
│   ├── bd_partidas.h      
│   ├── bd_times.h
│   ├── campeonato.h
│   ├── partida.h
│   └── time.h
├── src/                   # Pasta contendo os arquivos .c a serem compilados
│   ├── bd_partidas.c
│   ├── bd_times.c
│   ├── campeonato.c
│   ├── main.c
│   ├── partida.c
│   └── time.c
└── dados/                 # Pasta contendo todos os arquivos .csv que utilizaremos para uso
    ├── partidas_completo.csv
    ├── partidas_parcial.csv
    ├── partidas_vazio.csv
    └── times.csv
```

## 🛠️ Como Executar

Este projeto foi desenvolvido para um ambiente **Linux (Ubuntu)** e depende de `gcc` e `make`.

1.  **Pré-requisitos:** Certifique-se de ter o `build-essential` (ou `gcc` e `make`) instalados:
    ```bash
    sudo apt update
    sudo apt install build-essential
    ```

2.  **Compilar o Projeto:** Na pasta raiz (`trabalho_1/`), execute o `Makefile`:
    ```bash
    make
    ```
    Isso irá compilar todos os arquivos da pasta `src/` e criar um executável chamado `campeonato` na raiz.

3.  **Executar o Programa:**
    ```bash
    ./campeonato
    ```

4.  **Limpar Arquivos Compilados:** Para remover os arquivos `.o` e o executável:
    ```bash
    make clean
    ```

## 🧠 Módulos e TADs Implementados

O sistema é dividido em Módulos e Tipos Abstratos de Dados (TADs), onde a implementação (`struct`) é escondida no arquivo `.c` (Tipo Opaco).

### `partida.c` / `partida.h` (TAD Partida)

* **Propósito:** Modela uma única partida de futebol.
* **Funções Notáveis:**
    * `criar_partida()`: Aloca e inicializa uma partida com os IDs e placares.
    * `deletar_partida()`: Libera a memória da partida.
    * `partida_get_*()`: Funções *getter* para acessar os dados (ex: `partida_get_id_time1()`).

### `time.c` / `time.h` (TAD Time)

* **Propósito:** Modela um único time, guardando seus dados de identificação e estatísticas acumuladas.
* **Funções Notáveis:**
    * `criar_time()`: Aloca e inicializa um time com estatísticas zeradas.
    * `deletar_time()`: Libera a memória do time.
    * `atualizar_estatisticas_time()`: Função central de lógica. Recebe o placar de *um* jogo e atualiza V, E, D, GM e GS do time.
    * `time_get_*()`: Getters para dados brutos (ex: `time_get_vitorias()`) e dados calculados (ex: `time_get_pontuacao()`).

### `bd_partidas.c` / `bd_partidas.h` (TAD BDPartidas)

* **Propósito:** Gerenciador da coleção de todas as partidas, lidas do CSV.
* **Funções Notáveis:**
    * `criar_bd_partidas()`: Aloca o gerenciador e seu vetor estático interno.
    * `carregar_bd_partidas()`: Abre e lê o arquivo `.csv`, usando `criar_partida()` para cada linha.
    * `deletar_bd_partidas()`: Libera o gerenciador e *todas* as partidas que ele carregou.
    * `get_todas_partidas_bd()`: Retorna o vetor com todas as partidas.

### `bd_times.c` / `bd_times.h` (TAD BDTimes)

* **Propósito:** Gerenciador da coleção de todos os times, lidos do CSV.
* **Funções Notáveis:**
    * `criar_bd_times()`: Aloca o gerenciador e seu vetor interno.
    * `carregar_bd_times()`: Abre e lê o arquivo `.csv`, usando `criar_time()` para cada linha.
    * `deletar_bd_times()`: Libera o gerenciador e *todos* os times que ele carregou.
    * `get_time_bd_por_id()`: Acesso rápido a um time pelo seu ID (usado no cálculo).
    * `get_times_bd_por_prefixo()`: Lógica de busca. Retorna um *novo* vetor alocado dinamicamente com os times que correspondem ao prefixo.

### `campeonato.c` / `campeonato.h` (Módulo de Lógica)

* **Propósito:** Módulo "cola" que orquestra o processamento dos dados.
* **Funções Notáveis:**
    * `campeonato_calcular_estatisticas()`: Itera por todas as partidas (do `BDPartidas`), busca os times envolvidos (no `BDTimes`) e chama a função `atualizar_estatisticas_time()` para cada um.

### `main.c` (Programa Principal)

* **Propósito:** Ponto de entrada. Controla o fluxo do programa, o menu e a interface do usuário.
* **Funções Notáveis:**
    * `main()`: Orquestra a inicialização, carga, processamento, loop do menu e limpeza final.
    * `executar_consulta_time()`: Implementa a funcionalidade da Opção 1.
    * `handle_consultar_partidas()`: Implementa a funcionalidade da Opção 2.
    * `handle_imprimir_tabela()`: Implementa a funcionalidade da Opção 6.
    * `limpar_tela()`, `pausar_tela()`, `ler_opcao()`: Funções utilitárias para a interface de usuário no terminal.

## ⚠️ Limitações (Parte I)

* **Tamanhos Estáticos:** O número de times (`MAX_TIMES 10`) e partidas (`MAX_PARTIDAS 100`) é fixo por `#define`, caso queira adicionar mais times ou mais partidas, altere o valor para o que deseja.
* **Somente Leitura:** O sistema é focado em consulta. As opções de *Inserir* (3), *Atualizar* (4) e *Remover* (5) estão intencionalmente desabilitadas, provavelmente serão implementados em versões futuras do trabalho (do querido professor Thiago PX).
* **Ordenação:** A tabela de classificação (Opção 6 do menu) é impressa na ordem de ID, não ordenada por pontuação (fiz desta forma por conta dos requisitos da Parte I do trabalho).
* **Caminho dos Dados:** Os caminhos para os arquivos CSV estão fixos no `main.c` para apontar para a pasta `dados/`.
