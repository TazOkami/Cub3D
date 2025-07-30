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
	   $(SRCS_DIR)/init/init_game.c

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
NC = \033[0m

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(MLX_LIB) $(LIBFT_LIB)
	@echo "$(GREEN)🔗 Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "$(GREEN)✅ $(NAME) compiled successfully!$(NC)"

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)🔨 Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(MLX_LIB):
	@echo "$(YELLOW)🔨 Compiling MLX...$(NC)"
	@make -C $(MLX_DIR)

$(LIBFT_LIB):
	@echo "$(YELLOW)🔨 Compiling libft...$(NC)"
	@make -C $(LIBFT_DIR)

clean:
	@echo "$(RED)🧹 Cleaning objects...$(NC)"
	@rm -rf $(OBJS_DIR)
	@make -C $(MLX_DIR) clean
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@echo "$(RED)🧹 Cleaning executable...$(NC)"
	@rm -f $(NAME)
	@make -C $(MLX_DIR) clean
	@make -C $(LIBFT_DIR) fclean

re: fclean all

run: $(NAME)
	@echo "$(GREEN)🚀 Running $(NAME)...$(NC)"
	@./$(NAME)

debug: CFLAGS += -g
debug: $(NAME)

help:
	@echo "$(GREEN)📋 Available targets:$(NC)"
	@echo "  all     - Compile the project"
	@echo "  clean   - Remove object files"
	@echo "  fclean  - Remove all generated files"
	@echo "  re      - Recompile everything"
	@echo "  run     - Compile and run the program"
	@echo "  debug   - Compile with debug symbols"
	@echo "  help    - Show this help message"
