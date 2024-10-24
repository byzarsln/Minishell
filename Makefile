NAME = minishell

SRC = minishell.c \
free/free.c free/free_data.c src/signals/signals.c initialize/initialize.c \
src/parser/parser.c src/parser/tokenizer.c src/parser/tokenizer_utils.c src/parser/tokenizer_utils2.c \
src/parser/parser_utils.c src/parser/parser_utils2.c

CFLAGS = #-Wall -Wextra -Werror -g #-fsanitize=address # MallocStackLogging=1
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