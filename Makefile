# ========================
#        VARIABLES
# ========================

NAME        := tinyshell
CC          := gcc
CFLAGS      := -Wall -Wextra -Iinclude
SRC_DIR     := src
OBJ_DIR     := obj

# Recherche de tous les fichiers .c récursivement
SRC         := $(shell find $(SRC_DIR) -name '*.c')
OBJ         := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# ========================
#        COMMANDES
# ========================

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $^

# Compilation des .c en .o
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage des fichiers objets
clean:
	@rm -rf $(OBJ_DIR)

# Nettoyage complet
fclean: clean
	@rm -f $(NAME)

# Recompilation complète
re: fclean all

# Règle par défaut
all: $(NAME)

.PHONY: all clean fclean re
