# Définir le compilateur et les options de compilation
CC=gcc
CFLAGS=-Wall -Wextra -g  # Activer tous les avertissements, des avertissements supplémentaires, et le débogage
LIBS=-lreadline         # Lier avec la bibliothèque readline

# Chemins des dossiers pour les fichiers objets (.o) et les exécutables
OBJDIR = /home/guillaume/Desktop/systeme_avancee/Systeme-avancee/Projet_MiniShell/bin/
BINDIR = /home/guillaume/Desktop/systeme_avancee/Systeme-avancee/Projet_MiniShell/bin/

# Déclarer des cibles qui ne correspondent pas à des noms de fichiers
.PHONY: all clean

# La cible par défaut qui sera exécutée lors de l'appel à make sans arguments
all: clean $(BINDIR)main $(BINDIR)date $(BINDIR)ls $(BINDIR)who $(BINDIR)ps

# Règles pour lier les exécutables à partir des fichiers objets
$(BINDIR)main: $(OBJDIR)main.o $(OBJDIR)minishell_functions.o
	$(CC) $(CFLAGS) $(OBJDIR)main.o $(OBJDIR)minishell_functions.o -o $(BINDIR)main $(LIBS)

$(BINDIR)date: $(OBJDIR)date.o
	$(CC) $(CFLAGS) $(OBJDIR)date.o -o $(BINDIR)date

$(BINDIR)ls: $(OBJDIR)ls.o
	$(CC) $(CFLAGS) $(OBJDIR)ls.o -o $(BINDIR)ls

$(BINDIR)who: $(OBJDIR)who.o
	$(CC) $(CFLAGS) $(OBJDIR)who.o -o $(BINDIR)who

$(BINDIR)ps: $(OBJDIR)ps.o
	$(CC) $(CFLAGS) $(OBJDIR)ps.o -o $(BINDIR)ps

# Règles pour compiler les fichiers source (.c) en fichiers objets (.o)
$(OBJDIR)main.o: main.c minishell_functions.h
	$(CC) $(CFLAGS) -c main.c -o $(OBJDIR)main.o

$(OBJDIR)minishell_functions.o: minishell_functions.c minishell_functions.h
	$(CC) $(CFLAGS) -c minishell_functions.c -o $(OBJDIR)minishell_functions.o

$(OBJDIR)date.o: date.c date.h
	$(CC) $(CFLAGS) -c date.c -o $(OBJDIR)date.o

$(OBJDIR)ls.o: ls.c ls.h
	$(CC) $(CFLAGS) -c ls.c -o $(OBJDIR)ls.o

$(OBJDIR)who.o: who.c who.h
	$(CC) $(CFLAGS) -c who.c -o $(OBJDIR)who.o

$(OBJDIR)ps.o: ps.c ps.h
	$(CC) $(CFLAGS) -c ps.c -o $(OBJDIR)ps.o

# Règle pour nettoyer les fichiers compilés
clean:
	rm -f $(BINDIR)* $(OBJDIR)*

# Créer le dossier des exécutables s'il n'existe pas
$(BINDIR):
	mkdir -p $(BINDIR)
