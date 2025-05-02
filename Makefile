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
BI_DIR		=	builtins
EXE_DIR		=	execution
ERR_DIR		=	exit+error

################################################################################
##								  SOURCES									  ##

SRC_MAIN	=	minishell.c	utils_ms.c
				
SRC_RL		=	_readline.c	utils_rl.c

SRC_PARS	=	_parsing.c 				   										\
				get_type.c	get_word_type.c	hndl_file_redir.c	link_read_write.c \
				utl_clean.c	utl_lst_mk.c	utl_lst_rm.c		utl_pars.c  	\
				expand_env.c				X_prt_test.c		XX_color_prt.c

SRC_BI		=	ft_cd.c		ft_echo.c		ft_env.c			ft_exit.c		\
				ft_export.c	ft_pwd.c		ft_unset.c			utils_bi.c		\
				builtin_tester.c

SRC_EXE		=	

SRC_ERR		=	error.c

SRC			=	$(SRC_MAIN)													   \
				$(addprefix $(RL_DIR)/, $(SRC_RL))							   \
				$(addprefix $(PARS_DIR)/, $(SRC_PARS))						   \
				$(addprefix $(BI_DIR)/, $(SRC_BI))							   \
				$(addprefix $(EXE_DIR)/, $(SRC_EXE))						   \
				$(addprefix $(ERR_DIR)/, $(SRC_ERR))

LIBFT_LIB	=	$(LIBFT_DIR)/libft.a


################################################################################
##								 ARGUMENTS									  ##


NAME		= 	minishell
CC			= 	gcc
CFLAGS		= 	-Wall -Werror -Wextra -I$(INCL_DIR) -I$(LIBFT_DIR)
LFLAGS		= 	-lreadline -Llibft -lft
OBJ			= 	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
RM			= 	rm -f
AR			= 	ar -rcs
VALGRIND	=	valgrind 
VFLAGS		=	--leak-check=full #--show-leak-kinds=all --track-origins=yes --verbose
VSUPP		=	--suppressions=resources/a.supp --log-file="resources/leaks.log"


################################################################################
##								   RULES									  ##

$(NAME): $(OBJ) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) -o $(NAME) $(LFLAGS)
	echo $(NAME) "compiled"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | create_obj_dirs
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(RL_DIR)/%.c | create_obj_dirs
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(PARS_DIR)/%.c | create_obj_dirs
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(BI_DIR)/%.c | create_obj_dirs
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(EXE_DIR)/%.c | create_obj_dirs
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: $(ERR_DIR)/%.c | create_obj_dirs
	$(CC) $(CFLAGS) -c $< -o $@

create_obj_dirs:
	mkdir -p	$(OBJ_DIR)/$(RL_DIR) $(OBJ_DIR)/$(PARS_DIR) 				\
				$(OBJ_DIR)/$(EXE_DIR) $(OBJ_DIR)/$(BI_DIR) $(OBJ_DIR)/$(ERR_DIR)

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

re: fclean all

debug: CFLAGS += -g
debug: re
	echo $(NAME) "compiled in debug mode"

valgrind: CFLAGS += -g
valgrind: re
	$(VALGRIND) $(VFLAGS) $(VSUPP) ./$(NAME)


.SILENT:

.PHONY: all clean fclean re debug red