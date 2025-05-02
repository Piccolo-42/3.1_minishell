# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emurillo <emurillo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/27 15:10:01 by emurillo          #+#    #+#              #
#    Updated: 2025/05/02 17:27:15 by emurillo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
##                                DIRECTORIES                                 ##

INCLUDE_DIR = ../include
SRC_DIR     = ../src
LIBFT_DIR   = ../libft
OBJ_DIR     = ../obj/tests
TESTS_DIR   = ../tests
READLINE    = readline
PARSING_DIR = parsing
EXECUTION_DIR = execution
BUILTIN_DIR = builtins

################################################################################
##                                SOURCES                                     ##

SRC_MAIN = execution/tests_main.c

SRC_RDL = _readline.c utils_rl.c

SRC_PARS = _parsing.c get_type.c get_word_type.c hndl_file_redir.c \
			link_read_write.c utl_clean.c utl_lst_mk.c utl_lst_rm.c utl_pars.c \
			X_prt_test.c XX_color_prt.c expand_env.c

SRC_EXEC = built_ins_exec.c close_wait.c exec_pipeline.c exec_utils.c locate_path.c

SRC_BUILTIN = ft_cd.c ft_echo.c ft_env.c ft_exit.c ft_export.c ft_pwd.c ft_unset.c utils_bi.c

SRC_SRC = utils_ms.c

SRC_FILES = $(SRC_MAIN) $(SRC_SRC) \
	$(addprefix $(READLINE)/, $(SRC_RDL)) \
	$(addprefix $(PARSING_DIR)/, $(SRC_PARS)) \
	$(addprefix $(EXECUTION_DIR)/, $(SRC_EXEC)) \
	$(addprefix $(BUILTIN_DIR)/, $(SRC_BUILTIN))

LIBFT_LIB = $(LIBFT_DIR)/libft.a


################################################################################
##                                ARGUMENTS                                   ##

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I$(LIBFT_DIR) -I$(INCLUDE_DIR)
LIBS = -L$(LIBFT_DIR) -lft -lreadline

TEST_BIN = $(OBJ_DIR)/test_runner

################################################################################
##                                RULES                                       ##

.PHONY: all tests clean fclean re

all: $(TEST_BIN)

$(TEST_BIN): $(addprefix $(SRC_DIR)/, $(SRC_FILES))
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) $^ -o $@ $(LIBS)

# Run test comparing .in/.out files

.PHONY: tests

tests: $(TEST_BIN)
	@for file in $(TESTS_DIR)/*.in; do \
		base=$$(basename $$file .in); \
		echo "Running test $$base..."; \
		./$(TEST_BIN) < $$file > tmp.out; \
		if diff -q tmp.out $(TESTS_DIR)/$$base.out > /dev/null; then \
			echo "✅ $$base passed"; \
		else \
			echo "❌ $$base failed"; \
			diff tmp.out $(TESTS_DIR)/$$base.out; \
		fi; \
	done; \
	rm -f tmp.out

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(TEST_BIN)

re: fclean all
