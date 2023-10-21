# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: srall <srall@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/07 01:23:49 by srall             #+#    #+#              #
#    Updated: 2023/08/07 01:23:51 by srall            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# formatting
DEF_COLOR	=	\033[0;39m
ORANGE		=	\033[0;33m
GRAY		=	\033[0;90m
RED			=	\033[0;91m
GREEN		=	\033[1;92m
YELLOW		=	\033[1;93m
BLUE		=	\033[0;94m
MAGENTA		=	\033[0;95m
CYAN		=	\033[0;96m
WHITE		=	\033[0;97m

NAME			=	miniRT
CC				=	cc
CFLAGS			=	-Werror -Wall -Wextra -I$(HEADER_DIR1) -I$(HEADER_DIR2)
LDFLAGS			=	-L$(LIB_DIR) -lft -lmlx -framework OpenGL -framework AppKit

LIB_DIR			=	libft

# headers
HEADER_DIR1		=	./inc
HEADER_FILES1	+=	miniRT_utils.h parser.h define.h
HEADER_DIR2		=	./libft/inc
HEADER_FILES2	=	libft.h
HEADERS1		=	$(addprefix $(HEADER_DIR1)/,$(HEADER_FILES1))
HEADERS2		=	$(addprefix $(HEADER_DIR2)/,$(HEADER_FILES2))
HEADERS			=	$(HEADERS1) + $(HEADERS2)

# source files
SRC_DIR1		=	./src
SRC_FILES1		=	math_vec1.c math_vec2.c math.c \
					main.c miniRT_utils.c window.c ray_tracing.c objects.c shading.c
SRC_DIR2		=	./src/parser
SRC_FILES2		=	parser_checker.c parser_init.c parser_utils.c parser.c extra_rt_parser.c
SRCS			=	$(addprefix $(SRC_DIR1)/,$(SRC_FILES1))
SRCS			+=	$(addprefix $(SRC_DIR2)/,$(SRC_FILES2))

# rules
all: $(NAME)
$(NAME): $(HEADER_FILES)
	@make -C libft
	@$(CC) $(CFLAGS) $(LDFLAGS) $(SRCS) -o $(NAME)
	@echo "$(YELLOW)[$(NAME)]:\t$(DEF_COLOR) $(GREEN) => Success!$(DEF_COLOR)"
clean:
	@make clean -C libft
	@echo "$(BLUE)[$(NAME)]:\t\tobject files$(DEF_COLOR)$(GREEN) => Cleaned!$(DEF_COLOR)"
fclean: clean
	@make fclean -C libft
	@rm -f $(NAME) $(NAME_DEBUG)
	@echo "$(CYAN)[$(NAME)]:\t\ttarget files$(DEF_COLOR)$(GREEN) => Cleaned!$(DEF_COLOR)"
re:	fclean all

norm:
	norminette $(SRCS) | grep -v Norme -B1 || true

# for debug
NAME_DEBUG	=	$(addprefix "debug_",$(NAME))
FSANITIZE	=	-fsanitize=address -g # -fsanitize=thread
debug:
	@make -C libft
	@$(CC) $(CFLAGS) $(LDFLAGS) $(FSANITIZE) $(SRCS) -o $(NAME_DEBUG)
	@echo "$(YELLOW)[$(NAME_DEBUG)]:\t$(DEF_COLOR) $(GREEN) => Success!$(DEF_COLOR)"

.PHONY : all clean fclean re norm debug
