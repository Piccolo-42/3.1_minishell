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
RL_DIR		=	readline
PARS_DIR	=	parsing
EXE_DIR		=	exe

################################################################################
##								  SOURCES									  ##

SRC_MAIN	=	minishell.c
				
SRC_RL		=	_readline.c														\
			 	utils_rl.c

SRC_PARS	=	_parsing.c 				   										\
				ast_link_rw.c		  		  					\
				lst_clean.c		lst_get_type.c  	lst_file_redir.c			\
				utl_lst_mk.c	utl_lst_rm.c		utl_pars.c   				\
				X_prt_test.c

#SRC_EXE	=	

SRC			=	$(SRC_MAIN)													   \
				$(addprefix $(PARS_DIR)/, $(SRC_PARS))						   \
				$(addprefix $(RL_DIR)/, $(SRC_RL))							   \
				$(addprefix $(EXE_DIR)/, $(SRC_EXE))

LIBFT_LIB	=	$(LIBFT_DIR)/libft.a


################################################################################
##								 ARGUMENTS									  ##


NAME		= 	minishell
CC			= 	gcc
CFLAGS		= 	-Wall -Werror -Wextra -I$(INCL_DIR) -I$(LIBFT_DIR)
LFLAGS		= 	-lreadline -Llibft -lft
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

$(OBJ_DIR)/%.o: $(RL_DIR)/%.c | create_obj_dirs
	$(CC) $(CFLAGS) -c $< -o $@

create_obj_dirs:
	mkdir -p $(OBJ_DIR)/$(PARS_DIR) $(OBJ_DIR)/$(EXE_DIR) $(OBJ_DIR)/$(RL_DIR)

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

debug: CFLAGS += -g
debug: re
	echo $(NAME) "compiled in debug mode"

.SILENT:

.PHONY: all clean fclean re debug red