NAME = minishell

SRC = minishell.c \
free/free.c free/free_utils.c free/free_data.c src/signals/signals.c initialize/initialize.c \
src/parser/parser.c src/parser/tokenizer.c src/parser/tokenizer_utils.c src/parser/tokenizer_utils2.c \
src/parser/handle_quotes.c src/dollar/dollar.c src/dollar/dollar_utils.c src/dollar/dollar_utils2.c \
src/parser/handle_quotes2.c src/commands/command.c src/commands/command_word.c src/commands/command_word_utils.c \
src/commands/command_word_utils2.c src/commands/create_command.c src/commands/create_command_utils.c \
src/errors/error.c src/commands/command_heredoc.c src/commands/command_heredoc2.c src/commands/command_heredoc3.c \
src/commands/command_append.c src/commands/command_pipe.c src/executor/executor.c src/executor/executor_utils.c \
builtins/cd.c builtins/cd_utils.c builtins/echo.c builtins/env.c builtins/export.c builtins/pwd.c \
builtins/unset.c builtins/exit.c src/executor/execute_cmd.c src/executor/execute_cmd_utils.c src/executor/execute_cmd_utils2.c\
builtins/export_utils.c

CFLAGS = -Wall -Wextra -Werror -g
LIBFT = lib/libft/libft.a
READLINE = lib/readline/lib/libreadline.a

RM = @rm -rf
CC = @cc

OBJS = $(SRC:.c=.o)

RESET = \033[0m
BOLD = \033[1m
YELLOW = \033[33m
GREEN = \033[32m
RED = \033[31m

all: $(READLINE) $(NAME) $(LIBFT)

$(READLINE):
	@echo "$(BOLD)$(YELLOW)[DOWNLOADING READLINE...]$(RESET)"
	@curl -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
	@tar -xvf readline-8.2.tar.gz
	@$(RM) readline-8.2.tar.gz
	@cd readline-8.2 && ./configure --prefix=${PWD}/lib/readline
	@cd readline-8.2 && make install
	@$(RM) readline-8.2

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(BOLD)$(YELLOW)[COMPILING...]$(RESET)"
	@sleep 0.5
	@$(CC) -o $(NAME) $(OBJS) $(CFLAGS) $(LIBFT) -I${PWD}/lib/readline/include/ -lreadline -L${PWD}/lib/readline/lib
	@clear
	@echo "$(BOLD)$(YELLOW)[COMPILATION COMPLETE]$(RESET)"

$(LIBFT):
	@echo "$(BOLD)$(GREEN)[BUILDING LIBFT...]$(RESET)"
	@sleep 0.5
	@make -C lib/libft



%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I${PWD}/lib/readline/include/

fclean: clean
	@echo "$(BOLD)$(RED)[DELETING...]$(RESET)"
	@sleep 0.5
	@$(RM) $(NAME)
	@make -C lib/libft/ fclean
	@echo "$(BOLD)$(RED)[ALL FİLE DELETED]$(RESET)"

clean:
	@echo "$(BOLD)$(YELLOW)[DELETING OBJECTS...]$(RESET)"
	@sleep 0.5
	@$(RM) $(OBJS)
	@make -C lib/libft/ clean
	@echo "$(BOLD)$(RED)[ALL OBJECTS DELETED]$(RESET)"

re: fclean all

test: 
	cd minishell_tester && ./tester > results.txt
	cd minishell_tester && ./tester ./manual_tests/heredoc >> results.txt
	cd minishell_tester && ./tester ./manual_tests/mandatory >> results.txt
	cd minishell_tester && ./tester ./manual_tests/not_mandatory >> results.txt
	cd minishell_tester && ./tester ./manual_tests/signals >> results.txt

.PHONY: all fclean clean re