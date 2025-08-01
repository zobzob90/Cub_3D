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


INVALID_MAPS = \
	map/invalid_map/vide.cub \
	map/invalid_map/map.txt \
	map/invalid_map/inexistant_map.cub \
	map/invalid_map/additionnal_element.cub \
	map/invalid_map/doople_element.cub \
	map/invalid_map/doople_F_C.cub \
	map/invalid_map/invalid_path.cub \
	map/invalid_map/invalid_path_2.cub \
	map/invalid_map/lower_case.cub \
	map/invalid_map/missing_F_C.cub \
	map/invalid_map/missing_link.cub \
	map/invalid_map/missing_player.cub \
	map/invalid_map/wrong_border.cub \
	map/invalid_map/wrong_border_2.cub \
	map/invalid_map/wrong_char.cub \
	map/invalid_map/invalid_texture.cub \
	map/invalid_map/wrong_color.cub \
	map/invalid_map/wrong_color_2.cub \
	map/invalid_map/wrong_color_3.cub \
	map/invalid_map/overflow_color.cub

SRCS = 	src/main.c \
		src/event/event.c \
		src/event/mouse_event.c \
		src/event/door.c \
		src/event/door_utils.c \
		src/raycasting/raycaster.c \
		src/raycasting/raycaster_dda.c \
		src/raycasting/draw.c \
		src/raycasting/draw2.c \
		src/raycasting/draw_gun.c \
        src/raycasting/texture.c \
		src/raycasting/draw_cross.c \
		src/raycasting/draw_cross_utils.c \
        src/collision/collision.c \
		src/minimap/minimap_utils.c\
        src/minimap/draw_minimap.c \
        src/parsing/pars_utils.c \
        src/parsing/parse_color.c \
		src/parsing/parse_file_utils.c\
        src/parsing/parse_file.c \
        src/parsing/parse_map.c \
        src/parsing/parse_texture.c \
		src/parsing/parse_texture_utils.c\
        src/parsing/valid_map.c \
        src/parsing/parse_grid.c \
        src/parsing/parse_player.c \
        src/utils/free.c \
        src/utils/init.c \
		src/utils/init_dir.c\
		src/utils/init_map.c\
        src/utils/init_main_struct.c \
        src/npc/init_npc.c \
        src/npc/update_npc.c \
        src/npc/draw_npc.c \
		src/npc/draw_npc_utils.c\
		src/npc/draw_npc_utils_2.c \
        src/npc/load_sprite.c \
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


test: all
	@for file in $(INVALID_MAPS); do \
		echo ""; \
		echo "Testing $$file..."; \
		./$(NAME) $$file || true; \
	done
	@echo ""; echo "Testing without arguments..."; \
	./$(NAME) || true


-include $(DEPS)

.PHONY: all clean fclean re