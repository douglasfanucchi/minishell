NAME=minishell
CC=cc
FLAGS=-Wall -Werror -Wextra -c -I includes/ -I lib/libft -g3
LIBFT_PATH=lib/libft
LIBFT=$(LIBFT_PATH)/libft.a
LIBS=-L$(LIBFT_PATH) -lft -lreadline
TESTS_LIBS = $(LIBS) -lm -lrt

FILES=minishell.c tokens/tokenizer.c tokens/token.c tokens/redirect.c \
      analyser/redirection.c analyser/pipe.c analyser/quoted.c analyser/analyse.c \
      commands/new_command.c redirects/redirect_file_descriptor.c redirects/new_redirect.c \
	  utils/args.c commands/set_redirects.c commands/expansion.c utils/variables.c variables/variable.c \
	  commands/quote_removal.c executor/executor.c executor/exec_commands.c commands/check_command_errors.c \
	  utils/path.c utils/envp/envp.c commands/commands.c utils/quote.c commands/builtins/builtins.c \
	  executor/exec_builtin.c commands/builtins/echo.c commands/builtins/change_directory/change_directory.c \
	  commands/builtins/change_directory/navigate.c commands/builtins/pwd.c commands/builtins/unset.c \
	  commands/builtins/exit.c commands/builtins/export.c utils/envp/envp_add.c commands/builtins/env.c \
	  utils/utils.c
SRC := $(addprefix sources/, $(FILES))
OBJS := $(FILES:.c=.o)
OBJS := $(OBJS:tokens/%=%)
OBJS := $(OBJS:analyser/%=%)
OBJS := $(OBJS:redirects/%=%)
OBJS := $(OBJS:utils/%=%)
OBJS := $(OBJS:commands/%=%)
OBJS := $(OBJS:variables/%=%)
OBJS := $(OBJS:executor/%=%)
OBJS := $(OBJS:builtins/%=%)
OBJS := $(OBJS:change_directory/%=%)
OBJS := $(OBJS:envp/%=%)

all: | libft

libft:
	make -C $(LIBFT_PATH)
	make bonus -C $(LIBFT_PATH)
	make $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

$(OBJS): $(SRC)
	$(CC) $(FLAGS) $(SRC)

clean:
	@make clean -C lib/libft
	@rm -f $(OBJS) test.out

fclean: clean
	make fclean -C lib/libft
	rm -f $(NAME)

re: fclean all

tests:
	@$(CC) -g3 -Itests/includes -I./includes -I./lib/libft $(SRC:sources/minishell.c=) tests/sources/main.c $(TESTS_LIBS) -o test.out
	@./test.out

.PHONY: tests
