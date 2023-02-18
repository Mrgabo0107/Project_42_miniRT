# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ionorb <ionorb@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/19 18:59:58 by gamoreno          #+#    #+#              #
#    Updated: 2023/02/18 21:18:37 by ionorb           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### Compilation ###

CC      = gcc
FLAGS  = -Wall -Wextra -Werror -g
### Executable ###

NAME   = minirt

### Includes ###

OBJ_PATH  = objs/
HEADER = includes/
SRC_PATH  = sources/
MLX = libs/minilibx-linux
LIBFT = libs/libft
INCLUDES = -I $(HEADER) -I $(MLX) -I $(LIBFT)/includes

### Source Files ###
CORE_DIR	=	core/
CORE		=	main.c \
				init.c \

PARSE_DIR	=	parse/
PARSE		=	parsing.c \
				check_global_objects.c \
				check_objects.c \
				parsing_utils.c \

UTIL_DIR	=	utils/
UTILS		=	tools.c \
				memory.c \
				memory_utils.c \
				mem_redefs.c \
				free.c \
				list_utils.c \

MAT_DIR		=	math/
MAT			=	math.c \

CAM_DIR		=	cam/
CAM			=	cam.c \

# LIBFT_DIR	=	libft/
# LIBFT		=	libft.a

OBJ_DIRS	+=	$(addprefix	$(OBJ_PATH),$(CORE_DIR))
OBJ_DIRS	+=	$(addprefix	$(OBJ_PATH),$(PARSE_DIR))
OBJ_DIRS	+=	$(addprefix	$(OBJ_PATH),$(UTIL_DIR))
OBJ_DIRS	+=	$(addprefix	$(OBJ_PATH),$(MAT_DIR))
OBJ_DIRS	+=	$(addprefix	$(OBJ_PATH),$(CAM_DIR))

SOURCES		+=	$(addprefix	$(CORE_DIR),$(CORE))
SOURCES		+=	$(addprefix	$(PARSE_DIR),$(PARSE))
SOURCES		+=	$(addprefix	$(UTIL_DIR),$(UTILS))
SOURCES		+=	$(addprefix	$(MAT_DIR),$(MAT))
SOURCES		+=	$(addprefix	$(CAM_DIR),$(CAM))

### Objects ###

SRCS = $(addprefix $(SRC_PATH),$(SOURCES))
OBJS = $(addprefix $(OBJ_PATH),$(SOURCES:.c=.o))
DEPS = $(addprefix $(OBJ_PATH),$(SOURCES:.c=.d))

### COLORS ###
NOC         = \033[0m
GREEN       = \033[1;32m
CYAN        = \033[1;36m

### RULES ###

all: header lib tmp $(NAME)

lib:
	@echo "$(GREEN)Creating lib files$(NOC)"
	@make -C $(MLX)
	@make -C $(LIBFT)

tmp:
	@mkdir -p $(OBJ_DIRS)
# @mkdir -p $(OBJ_PATH)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -L $(LIBFT) -L $(MLX) $(INCLUDES) -O3 -o $@ $^ -l:libft.a -lmlx -lXext -lX11 -lm 
	@echo "$(GREEN)Project compiled succesfully$(NOC)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@$(CC) $(FLAGS) $(INCLUDES) -MMD -c -o $@ $<
	@echo "$(CYAN)Creation of object file -> $(CYAN)$(notdir $@)... $(GREEN)[Done]$(NOC)"

clean:
	@echo "$(GREEN)Cleaning libraries files$(NOC)"
	@make clean -C $(LIBFT)
	@rm -rf $(OBJ_PATH)

fclean:
	@echo "$(GREEN)Cleaning all$(NOC)"
	@rm -rf $(OBJ_PATH)
	@rm -f $(NAME)
	@make clean -C $(MLX)
	@make fclean -C $(LIBFT)

header:
	clear
	@echo "$$HEADER_PROJECT"

re: fclean all

run: all
	clear
	valgrind --leak-check=full --show-leak-kinds=all -s ./$(NAME) test.rt

-include $(DEPS)

.PHONY: tmp, re, fclean, clean, run

define HEADER_PROJECT
                  ░░░░▒▒░░                                            
            ░░▒▒▒▒░░▒▒▒▒▒▒▒▒▒▒                                        
          ▓▓▒▒▒▒▒▒▒▒░░░░▒▒▒▒▒▒▒▒░░                                    
        ▓▓▒▒▒▒▒▒▒▒▒▒░░░░▒▒▒▒▒▒▒▒▓▓░░                                  
      ▓▓▓▓▒▒▒▒▒▒▒▒▒▒░░░░░░▒▒▒▒▒▒▒▒▓▓                                  
    ░░██▓▓▓▓▒▒▒▒▒▒▒▒░░░░░░░░░░▒▒▒▒▓▓▓▓                                
    ▓▓██▓▓▓▓▒▒▒▒▒▒░░░░░░░░░░░░▒▒▒▒▒▒▓▓                                
    ████▓▓▓▓▓▓▒▒▒▒░░      ░░░░▒▒▒▒▒▒▓▓░░                              
    ████▓▓▓▓▓▓▓▓▒▒░░      ░░░░▒▒▒▒▓▓▓▓▒▒                              
    ██████▓▓▓▓▓▓▒▒░░      ░░░░▒▒▒▒▓▓▓▓▒▒                              
    ██████████▓▓▒▒░░░░  ░░░░▒▒▒▒▒▒▓▓▓▓▒▒                              
    ██████████▓▓▒▒▒▒░░░░░░▒▒▒▒▓▓▓▓▓▓▓▓░░                              
    ▓▓████████▓▓▓▓▒▒▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓                                
    ░░████████▓▓▓▓▒▒▒▒▒▒▒▒▒▒▓▓▓▓▓▓▓▓▒▒                                
      ▓▓██████▓▓▓▓▓▓▓▓▒▒▓▓▓▓▓▓▓▓▓▓▓▓                                  
        ██████▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓░░                                  
        ░░████████▓▓▓▓▓▓▓▓▓▓▓▓██░░                                    
            ▓▓████████████████░░                                      
                ▒▒▓▓██▓▓▒▒                                            

███╗   ███╗██╗███╗   ██╗██╗██████╗ ████████╗
████╗ ████║██║████╗  ██║██║██╔══██╗╚══██╔══╝
██╔████╔██║██║██╔██╗ ██║██║██████╔╝   ██║   
██║╚██╔╝██║██║██║╚██╗██║██║██╔══██╗   ██║   
██║ ╚═╝ ██║██║██║ ╚████║██║██║  ██║   ██║   
╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚═╝  ╚═╝   ╚═╝   
endef
export HEADER_PROJECT