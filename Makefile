# ═══════════════════════════════════════════════════════════
# 🎮 CUB3D - MAKEFILE OPTIMISÉ POUR DÉVELOPPEMENT
# ═══════════════════════════════════════════════════════════

# ┌─────────────────────────────────────────────────────────┐
# │ 🎯 CONFIGURATION GÉNÉRALE                              │
# └─────────────────────────────────────────────────────────┘

NAME = cub3d
CC = gcc

# Flags de base
CFLAGS = -Wall -Wextra -Werror -g3

# Flags de développement
DEBUG_FLAGS = -fsanitize=address -fsanitize=undefined -fno-omit-frame-pointer
LEAK_FLAGS = -fsanitize=leak
THREAD_FLAGS = -fsanitize=thread

# Directories
SRCS_DIR = srcs
OBJS_DIR = objs
INCLUDES_DIR = includes
MLX_DIR = minilibx-linux
LIBFT_DIR = libft

# Libraries
MLX_LIB = $(MLX_DIR)/libmlx.a
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# Sources
SRCS = $(SRCS_DIR)/main.c \
	   $(SRCS_DIR)/player_move.c \
	   $(SRCS_DIR)/raycasting.c \
	   $(SRCS_DIR)/utils.c \
	   $(SRCS_DIR)/error_handling.c \
	   $(SRCS_DIR)/cleanup.c \
	   $(SRCS_DIR)/init_game.c \
	   $(SRCS_DIR)/init_textures.c \
	   $(SRCS_DIR)/parser.c \
	   $(SRCS_DIR)/parse_textures.c \
	   $(SRCS_DIR)/parse_colors.c \
	   $(SRCS_DIR)/parse_map.c

# Objects
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# Headers
INCLUDES = -I$(INCLUDES_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

# Libraries
LIBS = -L$(MLX_DIR) -lmlx -L$(LIBFT_DIR) -lft -lXext -lX11 -lm

# Colors
GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
NC = \033[0m
BOLD = \033[1m

.PHONY: all clean fclean re debug leaks run run-debug run-leaks valgrind help

# ┌─────────────────────────────────────────────────────────┐
# │ 🏗️ RÈGLES PRINCIPALES                                   │
# └─────────────────────────────────────────────────────────┘

all: banner $(NAME)
	@echo "$(GREEN)$(BOLD)✅ $(NAME) compiled successfully!$(NC)"
	@echo "$(CYAN)💡 Run with: ./$(NAME) maps/map.cub$(NC)"

banner:
	@echo "$(PURPLE)$(BOLD)"
	@echo "  ░█████╗░██╗░░░██╗██████╗░███████╗██████╗░"
	@echo "  ██╔══██╗██║░░░██║██╔══██╗╚════██║██╔══██╗"
	@echo "  ██║░░╚═╝██║░░░██║██████╦╝███████║██║░░██║"
	@echo "  ██║░░██╗██║░░░██║██╔══██╗╚════██║██║░░██║"
	@echo "  ╚█████╔╝╚██████╔╝██████╦╝███████║██████╔╝"
	@echo "  ░╚════╝░░╚═════╝░╚═════╝░╚══════╝╚═════╝░$(NC)"
	@echo "$(CYAN)🎮 Building Cub3D...$(NC)"
	@echo ""

# ┌─────────────────────────────────────────────────────────┐
# │ 🔗 COMPILATION VERSIONS                                 │
# └─────────────────────────────────────────────────────────┘

$(NAME): $(OBJS) $(MLX_LIB) $(LIBFT_LIB)
	@echo "$(PURPLE)🔗 Linking $(NAME)...$(NC)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

# Version debug
$(NAME)_debug: CFLAGS += $(DEBUG_FLAGS)
$(NAME)_debug: $(OBJS) $(MLX_LIB) $(LIBFT_LIB)
	@echo "$(YELLOW)🐛 Linking DEBUG version...$(NC)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)_debug

# Version leak detection
$(NAME)_leaks: CFLAGS += $(LEAK_FLAGS)
$(NAME)_leaks: $(OBJS) $(MLX_LIB) $(LIBFT_LIB)
	@echo "$(RED)🔍 Linking LEAK detection version...$(NC)"
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)_leaks

# ┌─────────────────────────────────────────────────────────┐
# │ 🔨 COMPILATION OBJETS                                   │
# └─────────────────────────────────────────────────────────┘

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)🔨 Compiling $(notdir $<)...$(NC)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# ┌─────────────────────────────────────────────────────────┐
# │ 📚 LIBRAIRIES                                           │
# └─────────────────────────────────────────────────────────┘

$(MLX_LIB):
	@echo "$(BLUE)📦 Building MinilibX...$(NC)"
	@make -C $(MLX_DIR) > /dev/null 2>&1

$(LIBFT_LIB):
	@echo "$(BLUE)📚 Building libft...$(NC)"
	@make -C $(LIBFT_DIR) > /dev/null 2>&1

# ┌─────────────────────────────────────────────────────────┐
# │ 🐛 MODES DEBUG ET EXÉCUTION                            │
# └─────────────────────────────────────────────────────────┘

debug: banner
	@echo "$(YELLOW)🐛 Building DEBUG version...$(NC)"
	@make $(NAME)_debug CFLAGS="$(CFLAGS) $(DEBUG_FLAGS)" --no-print-directory
	@echo "$(GREEN)✅ Debug version ready!$(NC)"
	@echo "$(CYAN)💡 Launch with: make run-debug$(NC)"

leaks: banner
	@echo "$(RED)🔍 Building LEAK detection version...$(NC)"
	@make $(NAME)_leaks CFLAGS="$(CFLAGS) $(LEAK_FLAGS)" --no-print-directory
	@echo "$(GREEN)✅ Leak detection version ready!$(NC)"
	@echo "$(CYAN)💡 Launch with: make run-leaks$(NC)"

# ┌─────────────────────────────────────────────────────────┐
# │ 🚀 EXÉCUTION AVEC DIFFÉRENTS MODES                     │
# └─────────────────────────────────────────────────────────┘

run: $(NAME)
	@echo "$(GREEN)🚀 Launching $(NAME) (normal mode)...$(NC)"
	@if [ -f "maps/map.cub" ]; then \
		./$(NAME) maps/map.cub; \
	elif [ -f "test.cub" ]; then \
		./$(NAME) test.cub; \
	else \
		echo "$(YELLOW)⚠️  No map found. Usage: ./$(NAME) <map.cub>$(NC)"; \
	fi

run-debug: debug
	@echo "$(YELLOW)🐛 Launching DEBUG version with AddressSanitizer...$(NC)"
	@echo "$(RED)🔥 ASAN_OPTIONS: halt_on_error=1:abort_on_error=1$(NC)"
	@export ASAN_OPTIONS="halt_on_error=1:abort_on_error=1:print_stats=1"; \
	if [ -f "maps/map.cub" ]; then \
		./$(NAME)_debug maps/map.cub; \
	elif [ -f "test.cub" ]; then \
		./$(NAME)_debug test.cub; \
	else \
		echo "$(YELLOW)⚠️  No map found. Usage: ./$(NAME)_debug <map.cub>$(NC)"; \
	fi

run-leaks: leaks
	@echo "$(RED)🔍 Launching LEAK detection version...$(NC)"
	@export LSAN_OPTIONS="print_stats=1"; \
	if [ -f "maps/map.cub" ]; then \
		./$(NAME)_leaks maps/map.cub; \
	elif [ -f "test.cub" ]; then \
		./$(NAME)_leaks test.cub; \
	else \
		echo "$(YELLOW)⚠️  No map found. Usage: ./$(NAME)_leaks <map.cub>$(NC)"; \
	fi

valgrind: $(NAME)
	@echo "$(PURPLE)🔍 Running with Valgrind...$(NC)"
	@if [ -f "maps/map.cub" ]; then \
		valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=/usr/share/glib-2.0/valgrind/glib.supp ./$(NAME) maps/map.cub; \
	else \
		echo "$(YELLOW)⚠️  No map found for Valgrind test$(NC)"; \
	fi

# ┌─────────────────────────────────────────────────────────┐
# │ 🧹 NETTOYAGE                                           │
# └─────────────────────────────────────────────────────────┘

clean:
	@echo "$(RED)🧹 Cleaning objects...$(NC)"
	@rm -rf $(OBJS_DIR)
	@make -C $(MLX_DIR) clean > /dev/null 2>&1
	@make -C $(LIBFT_DIR) clean > /dev/null 2>&1

fclean: clean
	@echo "$(RED)🧹 Deep cleaning...$(NC)"
	@rm -f $(NAME) $(NAME)_debug $(NAME)_leaks
	@make -C $(LIBFT_DIR) fclean > /dev/null 2>&1
	@echo "$(GREEN)✅ Everything cleaned!$(NC)"

re: fclean all

# ┌─────────────────────────────────────────────────────────┐
# │ 📋 AIDE ET UTILITAIRES                                 │
# └─────────────────────────────────────────────────────────┘

help:
	@echo "$(BOLD)$(CYAN)📋 CUB3D MAKEFILE HELP$(NC)"
	@echo ""
	@echo "$(YELLOW)🎯 Compilation:$(NC)"
	@echo "  $(GREEN)make$(NC)           - Compile version normale"
	@echo "  $(GREEN)make debug$(NC)     - Compile version debug (AddressSanitizer)"
	@echo "  $(GREEN)make leaks$(NC)     - Compile version leak detection"
	@echo ""
	@echo "$(YELLOW)🚀 Exécution:$(NC)"
	@echo "  $(GREEN)make run$(NC)       - Lancer version normale"
	@echo "  $(GREEN)make run-debug$(NC) - Lancer version debug (avec ASAN)"
	@echo "  $(GREEN)make run-leaks$(NC) - Lancer version leak detection"
	@echo "  $(GREEN)make valgrind$(NC)  - Lancer avec Valgrind"
	@echo ""
	@echo "$(YELLOW)🧹 Nettoyage:$(NC)"
	@echo "  $(GREEN)make clean$(NC)     - Nettoyer objets"
	@echo "  $(GREEN)make fclean$(NC)    - Nettoyage complet"
	@echo "  $(GREEN)make re$(NC)        - Recompilation complète"
	@echo ""
	@echo "$(YELLOW)💡 Exemples:$(NC)"
	@echo "  $(CYAN)make run-debug$(NC)  - Pour débugger les erreurs"
	@echo "  $(CYAN)make run-leaks$(NC)  - Pour traquer les fuites mémoire"
	@echo "  $(CYAN)make valgrind$(NC)   - Pour analyse mémoire complète"
	@echo ""

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS): | $(OBJS_DIR)
