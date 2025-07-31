# ═══════════════════════════════════════════════════════════
# 🎮 CUB3D - MAKEFILE OPTIMISÉ LINUX
# ═══════════════════════════════════════════════════════════

# ┌─────────────────────────────────────────────────────────┐
# │ 🎯 CONFIGURATION GÉNÉRALE                              │
# └─────────────────────────────────────────────────────────┘

NAME = cub3d
CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

# Sources
SRCS_DIR = srcs
SRCS = $(SRCS_DIR)/main.c \
	   $(SRCS_DIR)/controls/player_move.c \
	   $(SRCS_DIR)/rendering/raycasting.c \
	   $(SRCS_DIR)/utils/utils.c \
	   $(SRCS_DIR)/utils/error_handling.c \
	   $(SRCS_DIR)/utils/cleanup.c \
	   $(SRCS_DIR)/init/init_game.c \
	   $(SRCS_DIR)/init/init_textures.c \
	   $(SRCS_DIR)/parsing/parser.c \
	   $(SRCS_DIR)/parsing/parse_textures.c \
	   $(SRCS_DIR)/parsing/parse_colors.c \
	   $(SRCS_DIR)/parsing/parse_map.c

# Objects
OBJS_DIR = objs
OBJS = $(SRCS:$(SRCS_DIR)/%.c=$(OBJS_DIR)/%.o)

# Headers
INCLUDES = -Iincludes -I$(MLX_DIR) -I$(LIBFT_DIR)

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

# Progress
TOTAL_FILES = $(words $(SRCS))
CURRENT = 0

.PHONY: all clean fclean re run debug help verbose

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

$(NAME): $(OBJS) $(MLX_LIB) $(LIBFT_LIB)
	@echo "$(PURPLE)🔗 Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME) 2>/dev/null || \
		(echo "$(RED)❌ Linking failed!$(NC)" && exit 1)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | progress
	@mkdir -p $(dir $@)
	@$(eval CURRENT=$(shell echo $$(($(CURRENT)+1))))
	@printf "$(YELLOW)🔨 [%2d/$(TOTAL_FILES)] Compiling %-30s$(NC)\r" $(CURRENT) "$(notdir $<)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ 2>/dev/null || \
		(echo "\n$(RED)❌ Compilation failed: $<$(NC)" && exit 1)

progress:
	@$(eval CURRENT=0)

$(MLX_LIB):
	@echo "$(BLUE)📦 Building MinilibX...$(NC)"
	@make -C $(MLX_DIR) --silent 2>/dev/null || \
		(echo "$(RED)❌ MLX compilation failed!$(NC)" && exit 1)

$(LIBFT_LIB):
	@echo "$(BLUE)📚 Building libft...$(NC)"
	@make -C $(LIBFT_DIR) --silent 2>/dev/null || \
		(echo "$(RED)❌ Libft compilation failed!$(NC)" && exit 1)

clean:
	@echo "$(RED)🧹 Cleaning objects...$(NC)"
	@rm -rf $(OBJS_DIR)
	@make -C $(MLX_DIR) clean --silent 2>/dev/null
	@make -C $(LIBFT_DIR) clean --silent 2>/dev/null
	@echo "$(GREEN)✅ Objects cleaned!$(NC)"

fclean: clean
	@echo "$(RED)🧹 Deep cleaning...$(NC)"
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean --silent 2>/dev/null
	@echo "$(GREEN)✅ Everything cleaned!$(NC)"

re: fclean all

run: $(NAME)
	@echo "$(GREEN)🚀 Launching $(NAME)...$(NC)"
	@./$(NAME)

debug: CFLAGS += -g -fsanitize=address
debug: re
	@echo "$(YELLOW)🐛 Debug version ready!$(NC)"

verbose: CFLAGS += -v
verbose: 
	@echo "$(CYAN)🔍 Verbose mode enabled$(NC)"
	@make all --no-print-directory

help:
	@echo "$(BOLD)$(CYAN)📋 CUB3D MAKEFILE HELP$(NC)"
	@echo ""
	@echo "$(YELLOW)🎯 Main targets:$(NC)"
	@echo "  $(GREEN)make$(NC)         - Compile the project (silent)"
	@echo "  $(GREEN)make verbose$(NC) - Compile with full output"
	@echo "  $(GREEN)make debug$(NC)   - Compile with debug flags"
	@echo "  $(GREEN)make run$(NC)     - Compile and run"
	@echo ""
	@echo "$(YELLOW)🧹 Cleaning:$(NC)"
	@echo "  $(GREEN)make clean$(NC)   - Remove object files"
	@echo "  $(GREEN)make fclean$(NC)  - Remove all generated files"
	@echo "  $(GREEN)make re$(NC)      - Full recompilation"
	@echo ""
	@echo "$(YELLOW)ℹ️  Other:$(NC)"
	@echo "  $(GREEN)make help$(NC)    - Show this help"
	@echo ""
