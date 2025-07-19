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
RESET		= \033[0m
BOLD		= \033[1m

SRC			= srcs/main.c \
			  srcs/parsing/parse_file.c \
			  srcs/parsing/parse_arg.c \
			  srcs/parsing/parse_config_line.c \
			  srcs/parsing/parse_utils.c \
			  srcs/error/print_error.c \
			  srcs/error/cleanup.c \
			  srcs/init/init.c \
			  srcs/utils/utils1.c \
			  srcs/game/game_loop.c \
			  srcs/game/raycasting.c
			  

SRC_BONUS	= 

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
	@printf "\r$(MINECRAFT_GREEN)Progress: [%-50s] %3d%%$(RESET)" "$$(printf '#%.0s' $$(seq 1 $$(($(CURRENT_FILE) * 50 / $(TOTAL_FILES)))))" "$(PERCENTAGE)"
endef

define update_progress_bonus
	$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
	$(eval PERCENTAGE=$(shell echo $$(($(CURRENT_FILE) * 100 / $(TOTAL_FILES_BONUS)))))
	@printf "\r$(MINECRAFT_GREEN)Progress: [%-50s] %3d%%$(RESET)" "$$(printf '#%.0s' $$(seq 1 $$(($(CURRENT_FILE) * 50 / $(TOTAL_FILES_BONUS)))))" "$(PERCENTAGE)"
endef

all: $(OBJ_DIR) $(LIBFT) $(MLX) $(NAME)
	@printf "\n$(MINECRAFT_GREEN)$(BOLD)Compilation completed!$(RESET)\n"

bonus: $(OBJ_DIR) $(OBJ_BONUS_DIR) $(LIBFT) $(MLX) $(NAME_BONUS)
	@printf "\n$(MINECRAFT_GREEN)$(BOLD)Bonus compilation completed!$(RESET)\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_BONUS_DIR):
	@mkdir -p $(OBJ_BONUS_DIR)

$(LIBFT):
	@printf "$(MINECRAFT_GREEN)Building libft...$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@printf "$(MINECRAFT_GREEN)Building MinilibX...$(RESET)\n"
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJ)
	@printf "\n$(MINECRAFT_GREEN)$(BOLD)Linking objects...$(RESET)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) $(LIBFT) $(MLX_FLAGS)

$(NAME_BONUS): $(OBJ_BONUS)
	@printf "\n$(MINECRAFT_GREEN)$(BOLD)Linking bonus objects...$(RESET)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME_BONUS) $(OBJ_BONUS) $(LIBFT) $(MLX_FLAGS)

$(OBJ_DIR)%.o: srcs/%.c includes/cub3d.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(call update_progress)

$(OBJ_DIR)%.o: srcs/parsing/%.c includes/cub3d.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(call update_progress)

$(OBJ_DIR)%.o: srcs/error/%.c includes/cub3d.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(call update_progress)

$(OBJ_DIR)%.o: srcs/raycasting/%.c includes/cub3d.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(call update_progress)

$(OBJ_DIR)%.o: srcs/rendering/%.c includes/cub3d.h
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

$(OBJ_BONUS_DIR)%.o: srcs_bonus/%.c includes/cub3d_bonus.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(call update_progress_bonus)

$(OBJ_BONUS_DIR)%.o: srcs_bonus/parsing/%.c includes/cub3d_bonus.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(call update_progress_bonus)

$(OBJ_BONUS_DIR)%.o: srcs_bonus/raycasting/%.c includes/cub3d_bonus.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(call update_progress_bonus)

$(OBJ_BONUS_DIR)%.o: srcs_bonus/rendering/%.c includes/cub3d_bonus.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(call update_progress_bonus)

$(OBJ_BONUS_DIR)%.o: srcs_bonus/game/%.c includes/cub3d_bonus.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(call update_progress_bonus)

$(OBJ_BONUS_DIR)%.o: srcs_bonus/utils/%.c includes/cub3d_bonus.h
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(call update_progress_bonus)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	@rm -rf $(OBJ_DIR) $(OBJ_BONUS_DIR)
	@printf "$(MINECRAFT_GREEN)Objects cleaned$(RESET)\n"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -f $(MLX)
	@rm -f $(NAME) $(NAME_BONUS)
	@printf "$(MINECRAFT_GREEN)Executables cleaned$(RESET)\n"

re: fclean all

.PHONY: all bonus clean fclean re