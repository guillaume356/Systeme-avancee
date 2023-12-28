CC=gcc
CFLAGS=-Wall -Wextra -g
LIBS=-lreadline

# Chemins des dossiers pour les fichiers objets et les exécutables
OBJDIR = /home/guillaume/Desktop/systeme_avancee/Systeme-avancee/Projet_MiniShell/bin/
BINDIR = /home/guillaume/Desktop/systeme_avancee/Systeme-avancee/Projet_MiniShell/bin/

.PHONY: all clean

all: clean $(BINDIR)mini-shell $(BINDIR)date $(BINDIR)ls $(BINDIR)who $(BINDIR)ps

$(BINDIR)mini-shell: $(OBJDIR)main.o
	$(CC) $(CFLAGS) $(OBJDIR)main.o -o $(BINDIR)mini-shell $(LIBS)

$(BINDIR)date: $(OBJDIR)date.o
	$(CC) $(CFLAGS) $(OBJDIR)date.o -o $(BINDIR)date

$(BINDIR)ls: $(OBJDIR)ls.o
	$(CC) $(CFLAGS) $(OBJDIR)ls.o -o $(BINDIR)ls

$(BINDIR)who: $(OBJDIR)who.o
	$(CC) $(CFLAGS) $(OBJDIR)who.o -o $(BINDIR)who

$(BINDIR)ps: $(OBJDIR)ps.o
	$(CC) $(CFLAGS) $(OBJDIR)ps.o -o $(BINDIR)ps

$(OBJDIR)%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BINDIR)* $(OBJDIR)*

# Créer le dossier s'il n'existe pas
$(BINDIR):
	mkdir -p $(BINDIR)
