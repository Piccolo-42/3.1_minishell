# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/27 15:10:01 by emurillo          #+#    #+#              #
#    Updated: 2025/04/27 15:37:35 by emurillo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
##								DIRECTORIES									  ##

INCLUDE_DIR = ../include
SRC_DIR = ../src
LIBFT_DIR = ../libft
OBJ_DIR = ../obj/tests
PARSING_DIR = parsing
EXECUTION_DIR = execution
BI_DIR = builtins
READLINE = readline


################################################################################
##								  SOURCES									  ##

SRC_MAIN = execution/execution_main.c

SRC_RDL = _readline.c utils_rl.C

SRC_PARS	=	_parsing.c
				get_type.c	get_word_type.c	hndl_file_redir.c	link_read_write.c
				utl_clean.c	utl_lst_mk.c	utl_lst_rm.c		utl_pars.c
				X_prt_test.c				XX_color_prt.c

SRC_BI		=	ft_cd.c		ft_echo.c		ft_env.c			ft_exit.c
				ft_export.c	ft_pwd.c		ft_unset.c			utils_bi.c

SRC_EXEC	=	built_ins_exec.c close_wait.c exec_pipeline.c exec_utils.c
				locate_path.c

SRC			=	$(SRC_MAIN)
				$(addprefix $(RL_DIR)/, $(SRC_RDL) )
				$(addprefix $(PARS_DIR)/, $(SRC_PARS))
				$(addprefix $(BI_DIR)/, $(SRC_BI))
				$(addprefix $(EXECUTION_DIR)/ $(SRC_EXEC))

LIBFT_LIB = $(LIBFT_DIR)/libft.a


################################################################################
##								 ARGUMENTS									  ##

NAME	=	minishell

CC		=	cc

C_FLAGS	=	-Wall -Wextra -Werror

INCS	=	-I$(LIBFT_DIR) -I$(INCLUDE_DIR)

LIBS	=	-L$(LIBFT_DIR) -lft -lreadline

