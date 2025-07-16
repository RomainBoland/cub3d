NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -fPIE
RESET = \033[0m
CYAN = \033[36m
BOLD = \033[1m

# Create objects directory paths
OBJ_DIR = objects/
OBJ_LIBFT_DIR = $(OBJ_DIR)libft/
OBJ_PRINTF_DIR = $(OBJ_DIR)printf/
OBJ_GNL_DIR = $(OBJ_DIR)gnl/

SRC_LIBFT = src/libft/ft_atoi.c \
            src/libft/ft_split.c \
            src/libft/ft_bzero.c \
			src/libft/ft_calloc.c \
			src/libft/ft_isalnum.c \
			src/libft/ft_isalpha.c \
			src/libft/ft_isascii.c \
			src/libft/ft_isdigit.c \
			src/libft/ft_isprint.c \
			src/libft/ft_itoa.c \
			src/libft/ft_lstadd_back.c \
			src/libft/ft_lstadd_front.c \
			src/libft/ft_lstclear.c \
			src/libft/ft_lstdelone.c \
			src/libft/ft_lstiter.c \
			src/libft/ft_lstlast.c \
			src/libft/ft_lstmap.c \
			src/libft/ft_lstnew.c \
			src/libft/ft_lstsize.c \
			src/libft/ft_memchr.c \
			src/libft/ft_memcmp.c \
			src/libft/ft_memcpy.c \
			src/libft/ft_memmove.c \
			src/libft/ft_memset.c \
			src/libft/ft_putchar_fd.c \
			src/libft/ft_putendl_fd.c \
			src/libft/ft_putnbr_fd.c \
			src/libft/ft_putstr_fd.c \
			src/libft/ft_strchr.c \
			src/libft/ft_strdup.c \
			src/libft/ft_striteri.c \
			src/libft/ft_strjoin.c \
			src/libft/ft_strlcat.c \
			src/libft/ft_strlcpy.c \
			src/libft/ft_strlen.c \
			src/libft/ft_strmapi.c \
			src/libft/ft_strncmp.c \
			src/libft/ft_strnstr.c \
			src/libft/ft_strrchr.c \
			src/libft/ft_strtrim.c \
			src/libft/ft_substr.c \
			src/libft/ft_tolower.c \
			src/libft/ft_toupper.c

SRC_PRINTF = src/ft_printf/ft_printf.c \
             src/ft_printf/ft_put_str.c \
             src/ft_printf/ft_put_int.c \
			 src/ft_printf/ft_put_ptr.c \
			 src/ft_printf/ft_put_unsigned.c \
			 src/ft_printf/ft_put_hexa.c

SRC_GNL = src/get_next_line/get_next_line_bonus.c \
          src/get_next_line/get_next_line_utils_bonus.c

# Count total files for progress bar
TOTAL_FILES := $(words $(SRC_LIBFT) $(SRC_PRINTF) $(SRC_GNL))
CURRENT_FILE = 0

# Progress bar function
define update_progress
    $(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE) + 1))))
    $(eval PERCENTAGE=$(shell echo $$(($(CURRENT_FILE) * 100 / $(TOTAL_FILES)))))
    @printf "\r$(CYAN)Progress: [%-50s] %3d%%$(RESET)" "$$(printf '#%.0s' $$(seq 1 $$(($(CURRENT_FILE) * 50 / $(TOTAL_FILES)))))" "$(PERCENTAGE)"
endef

OBJ_LIBFT = $(patsubst src/libft/%.c,$(OBJ_LIBFT_DIR)%.o,$(SRC_LIBFT))
OBJ_PRINTF = $(patsubst src/ft_printf/%.c,$(OBJ_PRINTF_DIR)%.o,$(SRC_PRINTF))
OBJ_GNL = $(patsubst src/get_next_line/%.c,$(OBJ_GNL_DIR)%.o,$(SRC_GNL))

OBJ = $(OBJ_LIBFT) $(OBJ_PRINTF) $(OBJ_GNL)

all: create_dirs $(NAME)
	@printf "\n$(CYAN)$(BOLD)Library compilation completed!$(RESET)\n"

create_dirs:
	@mkdir -p $(OBJ_LIBFT_DIR) $(OBJ_PRINTF_DIR) $(OBJ_GNL_DIR)

# Compile rules for each directory
$(OBJ_LIBFT_DIR)%.o: src/libft/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	$(call update_progress)

$(OBJ_PRINTF_DIR)%.o: src/ft_printf/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	$(call update_progress)

$(OBJ_GNL_DIR)%.o: src/get_next_line/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	$(call update_progress)

$(NAME): $(OBJ)
	@printf "\n$(CYAN)$(BOLD)Creating library archive...$(RESET)"
	@ar rcs $(NAME) $(OBJ)

clean:
	@rm -rf $(OBJ_DIR)
	@printf "$(CYAN)Objects cleaned$(RESET)\n"

fclean: clean
	@rm -f $(NAME)
	@printf "$(CYAN)Library cleaned$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re create_dirs