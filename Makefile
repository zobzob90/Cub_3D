NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INC = -Iinc -Ilibft
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a
MLX_DIR = mlx
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a

BUILD_DIR = build

define progress_bar
	@echo -n "["
	@for i in $$(seq 1 20); do \
		sleep 0.005; \
		printf "#"; \
	done
	@echo "] Done! 🚀"
endef

SRCS = 	src/main.c \
		src/event/event.c \
		src/raycasting/raycaster.c \
		src/raycasting/raycaster_dda.c \
		src/raycasting/draw.c \
		src/raycasting/draw2.c \
		src/raycasting/draw_gun.c \
		src/raycasting/texture.c \
		src/collision/collision.c \
		src/parsing/pars_utils.c \
		src/parsing/parse_color.c \
		src/parsing/parse_file.c \
		src/parsing/parse_map.c \
		src/parsing/parse_texture.c \
		src/parsing/valid_map.c \
		src/parsing/parse_grid.c \
		src/parsing/parse_player.c \
		src/utils/free.c \
		src/utils/init.c \
		src/utils/init_dir.c \
		src/move/move.c \
		src/fire/fire.c

OBJS = $(SRCS:%.c=$(BUILD_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

MLX_FLAGS =  -L$(MLX_DIR) -lmlx_Linux -L/usr/lib/x11 -lXext -lX11 -lm

all: $(MLX_LIB) $(LIBFT_LIB) $(NAME)

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

$(LIBFT_LIB):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(INC) $(OBJS) -L$(LIBFT_DIR) -lft $(MLX_FLAGS) -lreadline -o $(NAME)
	$(progress_bar)
	@echo "✅ Compilation de $(NAME) terminée."
	@echo "\033[32m" 
	@echo "\033[5m"  # Active le clignotement
	@figlet "CUB 3D"
	@echo "\033[0m"  # Réinitialise les styles
	@echo "\n"

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -I$(MLX_DIR) $(INC) -MMD -MP -c $< -o $@

clean:
	@rm -rf $(BUILD_DIR)
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(MLX_DIR)
	@echo "🧹 Suppression des fichiers objets et dépendances terminée."

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(MLX_DIR)
	@echo "🗑️ Suppression de $(NAME) terminée."

re: fclean all

-include $(DEPS)

.PHONY: all clean fclean re