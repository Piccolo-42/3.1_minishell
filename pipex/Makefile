# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sravizza <sravizza@student.42lausanne.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/06 12:36:59 by sravizza          #+#    #+#              #
#    Updated: 2025/01/06 12:36:59 by sravizza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

##############################################################################################
##									DIRECTORIES												##

PRINTF_DIR	= libft/printf_src
GNL_DIR		= libft/gnl_src
LIBFT_DIR	= libft/libft_src


##############################################################################################
##									SOURCES													##

PRINTF_SRCS	=	ft_printf.c		ft_printnbr.c		ft_itoa_to_base.c	ft_unitoa.c

GNL_SRCS	=	get_next_line.c	

LIBFT_SRCS	= 	ft_isalpha.c	ft_isdigit.c		ft_isalnum.c		ft_isascii.c		\
				ft_isprint.c	ft_strlen.c			ft_memset.c			ft_bzero.c 			\
    			ft_memcpy.c		ft_memmove.c		ft_strlcpy.c		ft_strlcat.c		\
    			ft_calloc.c		ft_strdup.c			ft_toupper.c		ft_tolower.c		\
    			ft_strchr.c		ft_strncmp.c		ft_memchr.c			ft_memcmp.c			\
    			ft_strnstr.c	ft_atoi.c			ft_strrchr.c		ft_substr.c			\
    			ft_strjoin.c	ft_strtrim.c		ft_split.c			ft_itoa.c			\
    			ft_strmapi.c	ft_striteri.c		ft_putchar_fd.c		ft_putstr_fd.c		\
				ft_putendl_fd.c	ft_putnbr_fd.c					

PIPEX_SRCS 	= 	pipex_main.c	pipex_ft.c			pipex_utils.c


##############################################################################################
##									ARGUMENTS												##

SRCS		= $(addprefix $(PRINTF_DIR)/, $(PRINTF_SRCS)) 									\
			  $(addprefix $(LIBFT_DIR)/, $(LIBFT_SRCS))										\
			  $(addprefix $(GNL_DIR)/, $(GNL_SRCS))											\
			  $(PIPEX_SRCS)
OBJS		= $(SRCS:.c=.o)
NAME		= pipex
CC			= gcc 
CFLAGS		= -Werror -Wall -Wextra
RM			= rm -f
AR			= ar -rcs


##############################################################################################
##									RULES													##

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o$@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	echo "Compilation complete"
	

all: $(NAME)

clean:
	$(RM) $(OBJS)
	echo "objects removed"

fclean: clean
	$(RM) $(NAME)
	echo $(NAME) "removed" 

re: fclean all

.SILENT:

.PHONY: all, clean, fclean, re