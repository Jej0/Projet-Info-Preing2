
CC = gcc        # Compiler C
CFLAGS = -Wall 

# Fichiers sources
SRC_FILES = main.c

# Fichiers d'en-tête
HEADER_FILES = header.h conso.h

# Sortie
EXECUTABLE = prog

all: $(EXECUTABLE)

$(EXECUTABLE): $(SRC_FILES) $(HEADER_FILES)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SRC_FILES)

.PHONY: clean

clean:
	rm -f $(EXECUTABLE)