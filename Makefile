NAME = minishell
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
LIBS = -lreadline
# Path: src
# Sources
SRCS		= src/main.c \
			  src/arrstr.c \
			  src/basic_utils.c \
			  src/basic_utils2.c \
			  src/basic_utils3.c \
			  src/builtin_utils.c \
			  src/cd.c \
			  src/echo.c \
			  src/env_utils.c \
			  src/env_utils2.c \
			  src/exec_utils.c \
			  src/exec_utils2.c \
			  src/exit.c \
			  src/expand_and_split.c \
			  src/expand_and_split2.c \
			  src/export.c \
			  src/input_utils.c \
			  src/list.c \
			  src/list2.c \
			  src/list3.c \
			  src/minish_loop.c \
			  src/parse_tokens.c \
			  src/print_errors.c \
			  src/print_errors2.c \
			  src/print_errors3.c \
			  src/quote_utils.c \
			  src/redirect_and_execute.c \
			  src/redirect_and_execute2.c \
			  src/redirect_utils.c \
			  src/redirect_utils2.c \
			  src/redirect_utils3.c \
			  src/redirect_utils4.c \
			  src/redirect_utils5.c \
			  src/signal_utils.c \
			  src/split_words.c \
			  src/token.c \
			  src/tokenize.c \
			  src/utils_char.c \
			  src/utils_split.c \
			  src/utils_str.c \
			  src/utils_str2.c \
			  src/utils_strjoin_free.c \
			  src/xchar.c \
			  src/xtoken.c \
			  src/xtoken2.c \
			  src/xtoken3.c \
			  src/get_input.c \

# Path: objs
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LIBS) -o $(NAME)
	@echo "\033[0;32mMinishell created\033[0;38m...\033[0m"

$(OBJ_DIR)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[0;38mCompiling \033[0;37m$<\033[0;38m...\033[0m"

clean:
	@rm -f $(OBJS)
	@echo "\033[0;38mCleaning \033[0;37m$(NAME)\033[0;38m...\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;38mDeleting \033[0;37m$(NAME)\033[0;38m...\033[0m"

leaks:
	@make all
	@rm -f leaks.txt
	@echo "\033[0;38mRunning \033[0;37m$(NAME)\033[0;38m with valgrind...\033[0m"
	@valgrind --leak-check=full --show-leak-kinds=all --log-file=leaks.txt ./$(NAME)

re: fclean all

.PHONY: all clean fclean re leaks
