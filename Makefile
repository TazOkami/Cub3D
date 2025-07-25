NAME = cub3D
CC = gcc
# CFLAGS = -Wall -Wextra -Werror
RM = rm -f

SRCDIR = srcs
INCDIR = includes
OBJDIR = objs

MLX_DIR = minilibx-linux/minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRCS = $(SRCDIR)/main.c \
	   $(SRCDIR)/init/init_game.c \
	   $(SRCDIR)/init/init_player.c \
	   $(SRCDIR)/init/init_textures.c \
	   $(SRCDIR)/parsing/parse_map.c \
	   $(SRCDIR)/parsing/parse_textures.c \
	   $(SRCDIR)/parsing/parse_colors.c \
	   $(SRCDIR)/raycasting/raycasting.c \
	   $(SRCDIR)/raycasting/algorithm.c \
	   $(SRCDIR)/raycasting/wall_distance.c \
	   $(SRCDIR)/raycasting/texture_calcul.c \
	   $(SRCDIR)/rendering/render.c \
	   $(SRCDIR)/rendering/draw_walls.c \
	   $(SRCDIR)/rendering/draw_floor_ceiling.c \
	   $(SRCDIR)/rendering/put_pixels.c \
	   $(SRCDIR)/events/key_events.c \
	   $(SRCDIR)/events/mouse_events.c \
	   $(SRCDIR)/events/window_events.c \
	   $(SRCDIR)/movement/player_movement.c \
	   $(SRCDIR)/movement/rotation.c \
	   $(SRCDIR)/movement/collision.c \
	   $(SRCDIR)/utils/error_handling.c \
	   $(SRCDIR)/utils/math_utils.c \
	   $(SRCDIR)/utils/memory_management.c \
	   $(SRCDIR)/utils/string_utils.c

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

HEADERS = $(INCDIR)/cub3d.h $(INCDIR)/struct.h $(INCDIR)/keys.h
INC_FLAGS = -I$(INCDIR) -I$(MLX_DIR)

all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)
	@echo "✅ cub3D compiled successfully!"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS) | $(OBJDIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(MLX_LIB):
	@echo "⚙️ Compiling MiniLibX..."
	@make -C $(MLX_DIR) > /dev/null 2>&1
	@echo "✅ MiniLibX compiled!"

clean:
	@$(RM) -r $(OBJDIR)
	@make -C $(MLX_DIR) clean > /dev/null 2>&1
	@echo "🧹 Objects cleaned"

fclean: clean
	@$(RM) $(NAME)
	@echo "🗑️ cub3D removed"

re: fclean all

.PHONY: all clean fclean re
