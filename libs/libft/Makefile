# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoel <yoel@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/24 18:26:55 by gamoreno          #+#    #+#              #
#    Updated: 2023/03/12 22:08:52 by yoel             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### Compilation ###

CC	= cc
CFLAGS	= -Wall -Wextra -Werror -I.

### Executable ###

NAME	=	libft.a

### Inculdes ###

OBJ_PATH = objs/
HEADER = ../../includes/
SRC_PATH = sources/
MLX = ../../libs/minilibx-linux
LIBFT = ../../libs/libft
INCLUDES = -I $(HEADER) -I $(MLX) -I $(LIBFT)/includes

### Sources ###

FTSTR_DIR	=	ft_str/
FTSTR		=	ft_strcmp.c ft_strchr.c ft_substr.c ft_strlen.c\
				ft_strdup.c ft_strjoin.c ft_split.c ft_split_ws.c

FTMATH_DIR	=	ft_math/
FTMATH		=	ft_atof.c ft_isdigit.c ft_itoa.c ft_ftoa.c ft_abs.c\
				ft_atoli.c ft_atoi.c 

FTPUT_DIR	=	ft_put/
FTPUT		=	ft_putstr_fd.c

FTMEM_DIR	=	ft_mem/
FTMEM		=	ft_bzero.c ft_calloc.c ft_memcpy.c

SOURCES		+=	$(addprefix	$(FTSTR_DIR),$(FTSTR))
SOURCES		+=	$(addprefix	$(FTMATH_DIR),$(FTMATH))
SOURCES		+=	$(addprefix	$(FTPUT_DIR),$(FTPUT))
SOURCES		+=	$(addprefix	$(FTMEM_DIR),$(FTMEM))
### Objects ###

SRCS = $(addprefix $(SRC_PATH),$(SOURCES))
OBJS = $(addprefix $(OBJ_PATH),$(SOURCES:.c=.o))
DEPS = $(addprefix $(OBJ_PATH),$(SOURCES:.c=.d))

### COLORS ###
NOC         = \033[0m
GREEN       = \033[1;32m
CYAN        = \033[1;36m

### RULES ###

all:		tmp $(NAME)

$(NAME):	$(OBJS)
		ar rcs $(NAME) $(OBJS)
		@echo "$(GREEN)libft made succesfully$(NOC)"

tmp:
		@mkdir -p $(OBJ_PATH)
		@mkdir -p $(OBJ_PATH)$(FTSTR_DIR)
		@mkdir -p $(OBJ_PATH)$(FTMATH_DIR)
		@mkdir -p $(OBJ_PATH)$(FTPUT_DIR)
		@mkdir -p $(OBJ_PATH)$(FTMEM_DIR)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
		@$(CC) $(FLAGS) $(INCLUDES) -MMD -c -o $@ $<
		@echo "$(CYAN)Creation of object file -> $(CYAN)$(notdir $@)... $(GREEN)[Done]$(NOC)"

clean:
		rm -rf $(OBJ_PATH)


fclean:		clean
		rm -f $(NAME)

re:		fclean all

-include $(DEPS)

.PHONY:		all clean fclean re bonus
