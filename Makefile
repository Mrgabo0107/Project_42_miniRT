# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yridgway <yridgway@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/19 18:59:58 by gamoreno          #+#    #+#              #
#    Updated: 2023/03/28 21:04:10 by yridgway         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### Compilation ###

CC      = cc
FLAGS  = -Wall -Werror -Wextra -g3 #-pg -A -Iincludes #-Ofast -flto #-march=native -mtune=native -fno-plt -fno-stack-protector -fomit-frame-pointer -fno-asynchronous-unwind-tables -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-unwind-tables -fno-ident -fno-st
# FLAGS  = -Wall -Werror -Wextra -Ofast -flto
# FLAGS  = -Ofast -flto
### Executable ###
#-Ofast -flto 
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
				keypress.c \
				keypress_obj1.c \
				keypress_obj2.c \
				keypress_obj3.c \
				mousepress.c \
				info_display.c \
				color_names.c \
				set_bump_map.c \

PARSE_DIR	=	parse/
PARSE		=	parsing.c \
				fill_objects.c \
				fill_options.c \
				parsing_utils.c \
				cell_filling.c \
				cell_filling_utils.c \
				save_scene.c \

UTIL_DIR	=	utils/
UTILS		=	tools.c \
				memory.c \
				memory_utils.c \
				mem_redefs.c \
				free.c \
				list_utils.c \

MAT_DIR		=	math/
MAT			=	math1.c \
				math2.c \
				math3.c \
				math4.c \
				math5.c \
				math6.c \
				math7.c \

CAM_DIR		=	cam/
CAM			=	cam.c \
				paint.c \
				chosen_obj.c \
				
COLOR_DIR	=	color/
COLOR		=	color.c \
				color_utils.c \
				color_utils2.c \
				radiance.c \

PLANE_DIR	=	plane/
PLANE		=	plane.c \
				plane_color.c \
				
SPHERE_DIR	=	sphere/
SPHERE		=	sphere.c \
				sphere_color.c \

CYLIN_DIR	=	cylinder/
CYLIN		=	cylinder.c \
				cylinder_utils.c \
				cylinder_color.c \

# LIBFT_DIR	=	libft/
# LIBFT		=	libft.a

OBJ_DIRS	+=	$(addprefix	$(OBJ_PATH),$(CORE_DIR))
OBJ_DIRS	+=	$(addprefix	$(OBJ_PATH),$(PARSE_DIR))
OBJ_DIRS	+=	$(addprefix	$(OBJ_PATH),$(UTIL_DIR))
OBJ_DIRS	+=	$(addprefix	$(OBJ_PATH),$(MAT_DIR))
OBJ_DIRS	+=	$(addprefix	$(OBJ_PATH),$(CAM_DIR))
OBJ_DIRS	+=	$(addprefix	$(OBJ_PATH),$(COLOR_DIR))
OBJ_DIRS	+=	$(addprefix	$(OBJ_PATH),$(PLANE_DIR))
OBJ_DIRS	+=	$(addprefix	$(OBJ_PATH),$(SPHERE_DIR))
OBJ_DIRS	+=	$(addprefix	$(OBJ_PATH),$(CYLIN_DIR))

SOURCES		+=	$(addprefix	$(CORE_DIR),$(CORE))
SOURCES		+=	$(addprefix	$(PARSE_DIR),$(PARSE))
SOURCES		+=	$(addprefix	$(UTIL_DIR),$(UTILS))
SOURCES		+=	$(addprefix	$(MAT_DIR),$(MAT))
SOURCES		+=	$(addprefix	$(CAM_DIR),$(CAM))
SOURCES		+=	$(addprefix	$(COLOR_DIR),$(COLOR))
SOURCES		+=	$(addprefix	$(PLANE_DIR),$(PLANE))
SOURCES		+=	$(addprefix	$(SPHERE_DIR),$(SPHERE))
SOURCES		+=	$(addprefix	$(CYLIN_DIR),$(CYLIN))

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
