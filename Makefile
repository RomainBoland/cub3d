# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rboland <rboland@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/17 00:01:24 by rboland           #+#    #+#              #
#    Updated: 2025/07/17 00:01:24 by rboland          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d
NAME_BONUS	= cub3d_bonus

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -I includes/ -I libft/includes/ -I mlx/
MLX_FLAGS	= -Lmlx -lmlx -L/usr/lib -Imlx -lXext -lX11 -lm -lz
MINECRAFT_GREEN = \033[38;5;70m
BLUE		= \033[0;34m
YELLOW		= \033[0;33m
RED			= \033[0;31m
RESET		= \033[0m
BOLD		= \033[1m

# Original mandatory sources
SRC			= srcs/main.c \
			  srcs/parsing/parse_file.c \
			  srcs/parsing/parse_arg.c \
			  srcs/parsing/parse_config_line.c \
			  srcs/parsing/parse_config_line2.c \
			  srcs/parsing/parse_utils.c \
			  srcs/parsing/fill_map.c \
			  srcs/parsing/parse_map.c \
			  srcs/parsing/parse_map_utils.c \
			  srcs/parsing/map_validation.c \
			  srcs/parsing/validate_textures.c \
			  srcs/error/print_error.c \
			  srcs/error/cleanup.c \
			  srcs/init/init.c \
			  srcs/init/texture_loading.c \
			  srcs/game/game_loop.c \
			  srcs/game/game_loop2.c \
			  srcs/game/raycasting.c \
			  srcs/game/dda_calculation.c \
			  srcs/game/dda_calculation_utils.c \
			  srcs/game/render_wall.c \
			  srcs/game/render_wall_utils.c \
			  srcs/game/movement.c \
			  srcs/game/events.c \
			  srcs/utils/utils1.c \
			  srcs/utils/normalize_line.c

SRC_BONUS	= srcs_bonus/main.c \
			  srcs_bonus/parsing/parse_file.c \
			  srcs_bonus/parsing/parse_arg.c \
			  srcs_bonus/parsing/parse_config_line.c \
			  srcs_bonus/parsing/parse_utils.c \
			  srcs_bonus/parsing/fill_map.c \
			  srcs_bonus/parsing/parse_map.c \
			  srcs_bonus/parsing/parse_map2.c \
			  srcs_bonus/parsing/parse_map_utils.c \
			  srcs_bonus/parsing/map_validation.c \
			  srcs_bonus/parsing/validate_textures.c \
			  srcs_bonus/error/print_error.c \
			  srcs_bonus/error/cleanup.c \
			  srcs_bonus/error/ft_free_split.c \
			  srcs_bonus/init/init.c \
			  srcs_bonus/init/texture_loading.c \
			  srcs_bonus/game/game_loop.c \
			  srcs_bonus/game/game_loop2.c \
			  srcs_bonus/game/interactive.c \
			  srcs_bonus/game/raycasting.c \
			  srcs_bonus/game/raycasting_get_texture.c \
			  srcs_bonus/game/dda_calculation.c \
			  srcs_bonus/game/dda_calculation_utils.c \
			  srcs_bonus/game/render_wall.c \
			  srcs_bonus/game/render_wall_utils.c \
			  srcs_bonus/game/render_ceiling_floor.c \
			  srcs_bonus/game/movement.c \
			  srcs_bonus/game/events.c \
			  srcs_bonus/game/menu.c \
			  srcs_bonus/game/update_game.c \
			  srcs_bonus/game/check_door_win_cond.c \
			  srcs_bonus/game/handle_menu_input.c \
			  srcs_bonus/utils/utils1.c \
			  srcs_bonus/utils/normalize_line.c \
			  srcs_bonus/utils/mini_map.c \
			  srcs_bonus/utils/mini_map_draw.c \
			  srcs_bonus/utils/mini_map_draw2.c \
			  srcs_bonus/utils/mini_map_get_color.c 

OBJ_DIR		= objects/
OBJ_BONUS_DIR = objects_bonus/
OBJ			= $(addprefix $(OBJ_DIR), $(notdir $(SRC:.c=.o)))
OBJ_BONUS	= $(addprefix $(OBJ_BONUS_DIR), $(notdir $(SRC_BONUS:.c=.o)))

LIBFT_DIR	= libft/
LIBFT		= $(LIBFT_DIR)libft.a

MLX_DIR		= mlx/
MLX			= $(MLX_DIR)libmlx.a

TOTAL_FILES := $(words $(SRC))
TOTAL_FILES_BONUS := $(words $(SRC_BONUS))
CURRENT_FILE = 0

define update_progress
	$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
	$(eval PERCENTAGE=$(shell echo $$(($(CURRENT_FILE) * 100 / $(TOTAL_FILES)))))
	@printf "\r$(MINECRAFT_GREEN)Mandatory Progress: [%-50s] %3d%%$(RESET)" "$$(printf '#%.0s' $$(seq 1 $$(($(CURRENT_FILE) * 50 / $(TOTAL_FILES)))))" "$(PERCENTAGE)"
endef

define update_progress_bonus
	$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
	$(eval PERCENTAGE=$(shell echo $$(($(CURRENT_FILE) * 100 / $(TOTAL_FILES_BONUS)))))
	@printf "\r$(BLUE)Bonus Progress: [%-50s] %3d%%$(RESET)" "$$(printf '#%.0s' $$(seq 1 $$(($(CURRENT_FILE) * 50 / $(TOTAL_FILES_BONUS)))))" "$(PERCENTAGE)"
endef

all: $(OBJ_DIR) $(LIBFT) $(MLX) $(NAME)
	@printf "\n$(MINECRAFT_GREEN)$(BOLD)✓ Mandatory compilation completed!$(RESET)\n"

bonus: $(OBJ_BONUS_DIR) $(LIBFT) $(MLX) $(NAME_BONUS)
	@printf "\n$(BLUE)$(BOLD)✓ Bonus compilation completed!$(RESET)\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_BONUS_DIR):
	@mkdir -p $(OBJ_BONUS_DIR)

$(LIBFT):
	@printf "$(MINECRAFT_GREEN)Building libft...$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

$(MLX):
	@printf "$(MINECRAFT_GREEN)Building MinilibX...$(RESET)\n"
	@$(MAKE) -C $(MLX_DIR) --no-print-directory

$(NAME): $(OBJ)
	@printf "\n$(MINECRAFT_GREEN)$(BOLD)Linking mandatory objects...$(RESET)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBFT) $(MLX_FLAGS)

$(NAME_BONUS): $(OBJ_BONUS)
	@printf "\n$(BLUE)$(BOLD)Linking bonus objects...$(RESET)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME_BONUS) $(OBJ_BONUS) $(LIBFT) $(MLX_FLAGS)

# Mandatory compilation rules
$(OBJ_DIR)%.o: srcs/%.c includes/cub3d.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(call update_progress)

$(OBJ_DIR)%.o: srcs/parsing/%.c includes/cub3d.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(call update_progress)

$(OBJ_DIR)%.o: srcs/error/%.c includes/cub3d.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(call update_progress)

$(OBJ_DIR)%.o: srcs/init/%.c includes/cub3d.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(call update_progress)

$(OBJ_DIR)%.o: srcs/game/%.c includes/cub3d.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(call update_progress)

$(OBJ_DIR)%.o: srcs/utils/%.c includes/cub3d.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(call update_progress)

# Bonus compilation rules
$(OBJ_BONUS_DIR)%.o: srcs_bonus/%.c includes/cub3d_bonus.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(call update_progress_bonus)

$(OBJ_BONUS_DIR)%.o: srcs_bonus/parsing/%.c includes/cub3d_bonus.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(call update_progress_bonus)

$(OBJ_BONUS_DIR)%.o: srcs_bonus/error/%.c includes/cub3d_bonus.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(call update_progress_bonus)

$(OBJ_BONUS_DIR)%.o: srcs_bonus/init/%.c includes/cub3d_bonus.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(call update_progress_bonus)

$(OBJ_BONUS_DIR)%.o: srcs_bonus/game/%.c includes/cub3d_bonus.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(call update_progress_bonus)

$(OBJ_BONUS_DIR)%.o: srcs_bonus/systems/%.c includes/cub3d_bonus.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(call update_progress_bonus)

$(OBJ_BONUS_DIR)%.o: srcs_bonus/rendering/%.c includes/cub3d_bonus.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(call update_progress_bonus)

$(OBJ_BONUS_DIR)%.o: srcs_bonus/utils/%.c includes/cub3d_bonus.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(call update_progress_bonus)

# Utility targets
test: $(NAME)
	@printf "$(YELLOW)Testing mandatory version...$(RESET)\n"
	@./$(NAME) maps/test.cub

test_bonus: $(NAME_BONUS)
	@printf "$(BLUE)Testing bonus version...$(RESET)\n"
	@./$(NAME_BONUS) maps/test_bonus.cub

setup_bonus:
	@printf "$(BLUE)Setting up bonus directory structure...$(RESET)\n"
	@mkdir -p srcs_bonus/systems
	@mkdir -p srcs_bonus/rendering
	@mkdir -p includes
	@printf "$(MINECRAFT_GREEN)✓ Bonus directories created$(RESET)\n"

info:
	@printf "$(BOLD)Cub3D Project Information:$(RESET)\n"
	@printf "$(MINECRAFT_GREEN)Mandatory:$(RESET)\n"
	@printf "  Sources: $(words $(SRC)) files\n"
	@printf "  Executable: $(NAME)\n"
	@printf "$(BLUE)Bonus:$(RESET)\n"
	@printf "  Sources: $(words $(SRC_BONUS)) files\n"
	@printf "  Executable: $(NAME_BONUS)\n"
	@printf "$(YELLOW)Usage:$(RESET)\n"
	@printf "  make          - Build mandatory version\n"
	@printf "  make bonus    - Build enhanced version\n"
	@printf "  make test     - Test mandatory version\n"
	@printf "  make test_bonus - Test bonus version\n"

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@$(MAKE) -C $(MLX_DIR) clean --no-print-directory
	@rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR)
	@printf "$(MINECRAFT_GREEN)✓ Objects cleaned$(RESET)\n"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@rm -f $(MLX)
	@rm -f $(NAME) $(NAME_BONUS)
	@printf "$(MINECRAFT_GREEN)✓ Executables cleaned$(RESET)\n"

re: fclean all

re_bonus: fclean bonus

# Prevent issues with files named like targets
.PHONY: all bonus clean fclean re re_bonus test test_bonus setup_bonus info