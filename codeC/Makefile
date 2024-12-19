# Nom de l'exécutable
TARGET = prog

# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -std=c99

# Fichiers sources et objets
SRCS = main.c
OBJS = main.o

# Règle principale
all: $(TARGET)

# Création de l'exécutable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

# Compilation des fichiers sources
main.o: main.c header.h conso.h
	$(CC) $(CFLAGS) -c main.c -o main.o

# Nettoyage des fichiers générés
clean:
	rm -f $(OBJS) $(TARGET)

# Nettoyage complet
distclean: clean
	rm -f *~