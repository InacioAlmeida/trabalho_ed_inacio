# --- Variáveis de Compilação ---

# Compilador (GCC)
CC = gcc

# Nome do executável final
EXEC = campeonato

# --- Variáveis de Pastas ---

# Define onde estão os códigos-fonte (.c)
SRC_DIR = src

# Define onde estão os cabeçalhos (.h)
INC_DIR = include

# --- Flags de Compilação ---

# Adicionamos a flag -I$(INC_DIR)
# -I diz ao GCC: "Procure por arquivos .h também na pasta 'include'"
# É por isso que você não precisa mudar seus #includes.
CFLAGS = -Wall -Wextra -g -std=c99 -I$(INC_DIR)

# --- Listas de Arquivos ---

C_FILES = main.c \
          time.c \
          partida.c \
          bd_times.c \
          bd_partidas.c \
          campeonato.c

# Gera a lista de arquivos de objeto (.o) que serão criados
# (ex: main.o, time.o, etc.)
OBJS = $(C_FILES:.c=.o)

# --- Regras de Compilação ---

# Regra principal (default): "make" ou "make all"
# Cria o executável final a partir dos arquivos .o
all: $(EXEC)

# Regra de ligação: Junta todos os .o no executável
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJS)

# Regra de compilação: Transforma um .c em .o
# Esta regra agora diz:
# "Para criar um arquivo.o, procure o arquivo.c correspondente na pasta $(SRC_DIR)"
%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra de limpeza: "make clean"
# Remove os arquivos gerados (objetos e executável)
clean:
	rm -f $(OBJS) $(EXEC)

# Regra de execução: "make run"
run: all
	./$(EXEC)

# Informa ao Make que 'all', 'clean' e 'run' não são nomes de arquivos
.PHONY: all clean run