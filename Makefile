# ═══════════════════════════════════════════════════════════
# 🎮 CUB3D - MAKEFILE OPTIMISÉ LINUX
# ═══════════════════════════════════════════════════════════

# ┌─────────────────────────────────────────────────────────┐
# │ 🎯 CONFIGURATION GÉNÉRALE                              │
# └─────────────────────────────────────────────────────────┘

NAME        = cub3d
CC          = cc
CFLAGS      = -Wall -Wextra -Werror
OPTIMFLAGS  = -O2 -march=native -mtune=native
DEBUGFLAGS  = -g3 -fsanitize=address -DDEBUG=1
MATHFLAGS   = -lm

# ┌─────────────────────────────────────────────────────────┐
# │ 📂 CHEMINS ET DOSSIERS                                 │
# └─────────────────────────────────────────────────────────┘

SRCDIR      = srcs
INCDIR      = includes
OBJDIR      = objs
LIBDIR      = minilibx-linux

# Sous-dossiers sources
SRCSUBDIRS  = init parsing rendering controls utils

# ┌─────────────────────────────────────────────────────────┐
# │ 🔗 CONFIGURATION MLX LINUX                             │
# └─────────────────────────────────────────────────────────┘

MLX_PATH    = $(LIBDIR)
MLX_LIB     = $(MLX_PATH)/libmlx.a
MLX_FLAGS   = -L$(MLX_PATH) -lmlx -lXext -lX11

# ┌─────────────────────────────────────────────────────────┐
# │ 📄 FICHIERS SOURCES                                    │
# └─────────────────────────────────────────────────────────┘

# 🎯 Sources par module
INIT_SRCS       = init_game.c init_mlx.c
PARSING_SRCS    = parcer.c parse_map.c parse_textures.c verif.c
RENDERING_SRCS  = raycasting.c wall_rendering.c sprite_rendering.c  
CONTROLS_SRCS   = keyboard.c player_move.c
UTILS_SRCS      = cleanup.c error_handling.c math_utils.c

# 🔗 Assemblage complet
SRCS = $(addprefix $(SRCDIR)/init/, $(INIT_SRCS)) \
	   $(addprefix $(SRCDIR)/parsing/, $(PARSING_SRCS)) \
	   $(addprefix $(SRCDIR)/rendering/, $(RENDERING_SRCS)) \
	   $(addprefix $(SRCDIR)/controls/, $(CONTROLS_SRCS)) \
	   $(addprefix $(SRCDIR)/utils/, $(UTILS_SRCS)) \
	   $(SRCDIR)/main.c

# 📦 Fichiers objets
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# ┌─────────────────────────────────────────────────────────┐
# │ 🎨 COULEURS POUR L'AFFICHAGE                           │
# └─────────────────────────────────────────────────────────┘

RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
BLUE    = \033[0;34m
PURPLE  = \033[0;35m
CYAN    = \033[0;36m
WHITE   = \033[0;37m
RESET   = \033[0m
BOLD    = \033[1m

# ┌─────────────────────────────────────────────────────────┐
# │ 🎯 RÈGLES PRINCIPALES                                  │
# └─────────────────────────────────────────────────────────┘

# 🏗️ Compilation principale
all: banner $(MLX_LIB) $(NAME)
	@echo "$(GREEN)$(BOLD)🎮 Cub3D compilé avec succès !$(RESET)"
	@echo "$(CYAN)💡 Utilisation: ./$(NAME) maps/map.cub$(RESET)"

# 🎯 Création de l'exécutable
$(NAME): $(OBJS)
	@echo "$(PURPLE)🔗 Linkage de $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OPTIMFLAGS) $(OBJS) $(MLX_FLAGS) $(MATHFLAGS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) créé !$(RESET)"

# 🏗️ Compilation MLX
$(MLX_LIB):
	@echo "$(YELLOW)🔧 Compilation de la MinilibX...$(RESET)"
	@make -C $(MLX_PATH) --silent
	@echo "$(GREEN)✅ MinilibX compilée !$(RESET)"

# 📦 Règle générale pour les objets
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)🔨 Compilation: $(notdir $<)$(RESET)"
	@$(CC) $(CFLAGS) $(OPTIMFLAGS) -I$(INCDIR) -I$(MLX_PATH) -c $< -o $@

# ┌─────────────────────────────────────────────────────────┐
# │ 🧹 RÈGLES DE NETTOYAGE                                 │
# └─────────────────────────────────────────────────────────┘

# 🗑️ Nettoyage objets
clean:
	@echo "$(RED)🧹 Nettoyage des objets...$(RESET)"
	@rm -rf $(OBJDIR)
	@make -C $(MLX_PATH) clean --silent
	@echo "$(GREEN)✅ Objets supprimés !$(RESET)"

# 🗑️ Nettoyage complet
fclean: clean
	@echo "$(RED)🧹 Nettoyage complet...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)✅ Projet nettoyé !$(RESET)"

# 🔄 Reconstruction complète
re: fclean all

# ┌─────────────────────────────────────────────────────────┐
# │ 🛠️ RÈGLES DE DÉVELOPPEMENT                             │
# └─────────────────────────────────────────────────────────┘

# 🐛 Version debug avec AddressSanitizer
debug: CFLAGS += $(DEBUGFLAGS)
debug: OPTIMFLAGS = 
debug: $(MLX_LIB) $(NAME)
	@echo "$(YELLOW)🐛 Version DEBUG compilée !$(RESET)"
	@echo "$(RED)⚠️  AddressSanitizer activé$(RESET)"

# ⚡ Version super optimisée
fast: OPTIMFLAGS += -Ofast -flto -funroll-loops
fast: $(MLX_LIB) $(NAME)
	@echo "$(GREEN)⚡ Version ULTRA-RAPIDE compilée !$(RESET)"

# 🧪 Tests automatiques
test: $(NAME)
	@echo "$(CYAN)🧪 Lancement des tests...$(RESET)"
	@./$(NAME) maps/map.cub || echo "$(RED)❌ Test échoué$(RESET)"
	@echo "$(GREEN)✅ Tests terminés !$(RESET)"

# 📊 Infos sur le projet
info:
	@echo "$(BOLD)$(BLUE)📊 INFORMATIONS PROJET$(RESET)"
	@echo "$(YELLOW)Nom:$(RESET) $(NAME)"
	@echo "$(YELLOW)Sources:$(RESET) $(words $(SRCS)) fichiers"
	@echo "$(YELLOW)Compilateur:$(RESET) $(CC)"
	@echo "$(YELLOW)Flags:$(RESET) $(CFLAGS)"
	@echo "$(YELLOW)MLX Path:$(RESET) $(MLX_PATH)"

# ┌─────────────────────────────────────────────────────────┐
# │ 🎮 RÈGLES D'UTILISATION                                │
# └─────────────────────────────────────────────────────────┘

# 🚀 Compilation et lancement direct
run: $(NAME)
	@echo "$(GREEN)🚀 Lancement de Cub3D...$(RESET)"
	@./$(NAME) maps/map.cub

# 🗺️ Test avec différentes cartes
test-maps: $(NAME)
	@echo "$(CYAN)🗺️ Test de toutes les cartes...$(RESET)"
	@for map in maps/*.cub; do \
		echo "$(YELLOW)Testing: $$map$(RESET)"; \
		./$(NAME) "$$map" || echo "$(RED)❌ Échec: $$map$(RESET)"; \
	done

# 📝 Générer la documentation
doc:
	@echo "$(BLUE)📝 Génération de la documentation...$(RESET)"
	@doxygen Doxyfile 2>/dev/null || echo "$(YELLOW)⚠️ Doxygen non installé$(RESET)"

# ┌─────────────────────────────────────────────────────────┐
# │ 🖼️ BANNIÈRE ET STYLE                                   │
# └─────────────────────────────────────────────────────────┘

banner:
	@echo "$(CYAN)$(BOLD)"
	@echo "  ╔══════════════════════════════════════════════════╗"
	@echo "  ║                                                  ║"
	@echo "  ║               🎮 CUB3D OPTIMIZED 🎮              ║" 
	@echo "  ║                                                  ║"
	@echo "  ║          Raycasting Engine - Linux Version      ║"
	@echo "  ║                                                  ║"
	@echo "  ╚══════════════════════════════════════════════════╝"
	@echo "$(RESET)"

# ┌─────────────────────────────────────────────────────────┐
# │ 🔧 RÈGLES BONUS ET MAINTENANCE                         │
# └─────────────────────────────────────────────────────────┘

# 📦 Installation des dépendances (Ubuntu/Debian)
install-deps:
	@echo "$(YELLOW)📦 Installation des dépendances Linux...$(RESET)"
	@sudo apt-get update
	@sudo apt-get install -y gcc make libbsd-dev libx11-dev libxext-dev libtool
	@echo "$(GREEN)✅ Dépendances installées !$(RESET)"

# 🔍 Vérification de la norme (si norminette installée)
norm:
	@echo "$(BLUE)🔍 Vérification de la norme...$(RESET)"
	@norminette $(SRCS) $(INCDIR)/*.h || echo "$(YELLOW)⚠️ Norminette non trouvée$(RESET)"

# 📈 Statistiques du code
stats:
	@echo "$(BOLD)$(PURPLE)📈 STATISTIQUES DU PROJET$(RESET)"
	@echo "$(YELLOW)Lignes de code:$(RESET)"
	@wc -l $(SRCS) $(INCDIR)/*.h | tail -1
	@echo "$(YELLOW)Fichiers .c:$(RESET) $(words $(SRCS))"
	@echo "$(YELLOW)Taille objets:$(RESET)"
	@du -sh $(OBJDIR) 2>/dev/null || echo "Pas encore compilé"

# 🧹 Nettoyage approfondi
deep-clean: fclean
	@echo "$(RED)🧹 Nettoyage approfondi...$(RESET)"
	@rm -rf .vscode/ *.dSYM/ .DS_Store
	@find . -name "*~" -delete
	@find . -name "*.swp" -delete
	@echo "$(GREEN)✅ Nettoyage approfondi terminé !$(RESET)"

# ┌─────────────────────────────────────────────────────────┐
# │ 🎯 DÉCLARATIONS PHONY                                  │
# └─────────────────────────────────────────────────────────┘

.PHONY: all clean fclean re debug fast test info run test-maps doc banner \
		install-deps norm stats deep-clean

# ┌─────────────────────────────────────────────────────────┐
# │ 💡 AIDE ET UTILISATION                                 │
# └─────────────────────────────────────────────────────────┘

help:
	@echo "$(BOLD)$(CYAN)🎯 AIDE MAKEFILE CUB3D$(RESET)"
	@echo ""
	@echo "$(YELLOW)📋 Règles principales:$(RESET)"
	@echo "  $(GREEN)make$(RESET)          - Compilation normale"
	@echo "  $(GREEN)make debug$(RESET)    - Version debug avec AddressSanitizer" 
	@echo "  $(GREEN)make fast$(RESET)     - Version ultra-optimisée"
	@echo "  $(GREEN)make clean$(RESET)    - Supprime les objets"
	@echo "  $(GREEN)make fclean$(RESET)   - Nettoyage complet"
	@echo "  $(GREEN)make re$(RESET)       - Recompilation complète"
	@echo ""
	@echo "$(YELLOW)🎮 Règles d'utilisation:$(RESET)"
	@echo "  $(GREEN)make run$(RESET)      - Compile et lance le jeu"
	@echo "  $(GREEN)make test$(RESET)     - Lance les tests"
	@echo "  $(GREEN)make test-maps$(RESET) - Teste toutes les cartes"
	@echo ""
	@echo "$(YELLOW)🔧 Règles maintenance:$(RESET)"
	@echo "  $(GREEN)make info$(RESET)     - Infos projet"
	@echo "  $(GREEN)make stats$(RESET)    - Statistiques code"
	@echo "  $(GREEN)make norm$(RESET)     - Vérification norme"
	@echo "  $(GREEN)make install-deps$(RESET) - Installe dépendances Linux"
	@echo ""
