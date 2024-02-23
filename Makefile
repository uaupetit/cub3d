NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
DEPS = ${OBJS:.o=.d}
INC = ./includes/cub.h
SRC_PATH = ./srcs
OBJS_PATH = ./objs

SRCS =  main.c angle.c draw.c key.c raycast.c raycast_utils.c check_color_utils.c \
		check_file_utils.c check_file.c check_map_utils.c check_map_utils2.c ft_split.c \
		get_next_line.c get_next_line_utils.c ft_trim.c parsing.c \

OBJS = $(addprefix $(OBJS_PATH)/, $(SRCS:.c=.o))

GREEN = \033[0;32m
RED = \033[0;31m
NC = \033[0m
YELLOW = \033[33m

MLX_PATH = ./mlx-linux/
MLX_LIB = $(MLX_PATH)libmlx.a
MLX_INC = -I $(MLX_PATH)

all: $(NAME)

$(MLX_LIB):
	@echo "$(YELLOW)Compiling MiniLibX...$(NC)"
	@cd $(MLX_PATH) && ./configure && make

all: $(MLX_LIB) $(NAME)

$(NAME): $(OBJS) $(INC) $(MLX_LIB)
	@$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) -o $(NAME) -lXext -lX11 -lm
	@echo "$(GREEN)Compilation complete! \n$(YELLOW)$(NAME) is ready to execute.$(NC)"

$(OBJS_PATH)/%.o: $(SRC_PATH)/%.c $(INC)
	@mkdir -p $(OBJS_PATH)
	@$(CC) $(CFLAGS) $(MLX_INC) -MMD -MP -c $< -o $@
	@echo "$(GREEN)Compiled:$(NC) $<"

clean:
	@rm -rf $(OBJS_PATH)
	@echo "$(RED)Cleaned up object files.$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)Cleaned up executables.$(NC)"

re: fclean all

-include $(DEPS)

.PHONY: mandatory all clean fclean re