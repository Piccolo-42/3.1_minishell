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
LIBFT_DIR	= libft
SRC_DIR		= src
OBJ_DIR		= obj


################################################################################
##								  SOURCES									  ##

SRC			=	minishell.c		parsing.c	utils_lst.c

LIBFT_LIB	= $(LIBFT_DIR)/libft.a


################################################################################
##								 ARGUMENTS									  ##


NAME		= minishell
CC			= gcc
CFLAGS		= -Wall -Werror -Wextra -I$(MLX_DIR) -I$(LIBFT_DIR)
LFLAGS		= -lreadline 
#LFLAGS		= -L$(MLX_DIR) -L$(LIBFT_DIR) -lmlx -lXext -lX11 -lm -lft
OBJ			= $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
RM			= rm -f
AR			= ar -rcs


################################################################################
##								   RULES									  ##

$(NAME): $(OBJ) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_LIB) -o $(NAME) $(LFLAGS)
	echo $(NAME) "compiled"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

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