# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    template_Makefile                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/11 09:56:12 by sravizza          #+#    #+#              #
#    Updated: 2025/02/21 16:14:08 by sravizza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
##								DIRECTORIES									  ##
LIBFT_DIR	=	libft
SRC_DIR		=	src
OBJ_DIR		=	obj
INCL_DIR	=	include
PARS_DIR	=	parsing
EXE_DIR		=	exe

################################################################################
##								  SOURCES									  ##

SRC_MAIN	=	minishell.c		
				

SRC_PARS	=	parsing.c 		token.c			ast.c			zgeg.c			\
				utils_lst.c		utils_ast.c		utils_pars.c	utils_token.c

#SRC_EXE	=	

SRC			=	$(SRC_MAIN)													   \
				$(addprefix $(PARS_DIR)/, $(SRC_PARS))						   \
				$(addprefix $(EXE_DIR)/, $(SRC_EXE))

LIBFT_LIB	=	$(LIBFT_DIR)/libft.a


################################################################################
##								 ARGUMENTS									  ##


NAME		= 	minishell
CC			= 	gcc
CFLAGS		= 	-Wall -Werror -Wextra -I$(INCL_DIR) -I$(LIBFT_DIR)
LFLAGS		= 	-lreadline 
#LFLAGS		= 	-L$(MLX_DIR) -L$(LIBFT_DIR) -lmlx -lXext -lX11 -lm -lft
OBJ			= 	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
RM			= 	rm -f
AR			= 	ar -rcs


################################################################################
##								   RULES									  ##

$(NAME): $(OBJ) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) -o $(NAME) $(LFLAGS)
	echo $(NAME) "compiled"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | create_obj_dirs
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(PARS_DIR)/%.c | create_obj_dirs
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(EXE_DIR)/%.c | create_obj_dirs
	$(CC) $(CFLAGS) -c $< -o $@

create_obj_dirs:
	mkdir -p $(OBJ_DIR)/parsing $(OBJ_DIR)/exe

#$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
#	mkdir -p $(OBJ_DIR)
#	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_LIB):
	$(MAKE) -C $(LIBFT_DIR) > /dev/null

	
################################################################################
##								   COMMANDS									  ##

all: $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	echo $(NAME) "obj removed"
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	echo $(NAME) "removed"
	$(MAKE) -C $(LIBFT_DIR) fclean

re: clean all

#debug: $(OBJ) $(MLX_LIB) $(LIBFT_LIB)
#	$(CC) $(CFLAGS) -g $(OBJ) -o $(NAME) $(LFLAGS)
#	echo $(NAME) "compiled"

#red: clean debug

.SILENT:

.PHONY: all clean fclean re debug red