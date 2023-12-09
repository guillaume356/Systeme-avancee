CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Répertoires de travail
SRC_DIRS := $(wildcard */src)
BIN_DIRS := $(SRC_DIRS:src=bin)

# Fichiers sources et objets
SRCS := $(wildcard $(addsuffix /*.c, $(SRC_DIRS)))
OBJS := $(SRCS:%.c=%.o)
EXES := $(SRCS:%.c=%)

# Règles par défaut
all: clean-bin $(EXES)

# Nettoyage du contenu des répertoires bin
clean-bin:
	@$(foreach bin,$(BIN_DIRS),rm -f $(bin)/*;)

# Règle pour compiler chaque fichier source en un objet puis en un exécutable
$(EXES): % : %.c
	@mkdir -p $(@D)/../bin
	$(CC) $(CFLAGS) -c $< -o $(@D)/../bin/$(notdir $@).o
	$(CC) $(CFLAGS) $(@D)/../bin/$(notdir $@).o -o $(@D)/../bin/$(notdir $@)

# Nettoyage complet
clean:
	@rm -rf $(BIN_DIRS)

# Informations de débogage
print-%:
	@echo $* = $($*)
