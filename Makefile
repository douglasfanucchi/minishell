NAME=minishell
CC=cc
FLAGS=-Wall -Werror -Wextra -c -I includes/
LIBFT_PATH=lib/libft
LIBFT=$(LIBFT_PATH)/libft.a
LIBS=-L$(LIBFT_PATH) -lft
TESTS_LIBS = $(LIBS) -lm -lrt

FILES=minishell.c tokens/tokenizer.c tokens/token.c tokens/redirect.c
SRC := $(addprefix sources/, $(FILES))
OBJS := $(FILES:.c=.o)

all: | libft

libft:
	make -C $(LIBFT_PATH)
	make $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

$(OBJS): $(SRC)
	$(CC) $(FLAGS) $(SRC)

tests:
	@$(CC) -g3 -Itests/includes -I./includes -I./lib/libft $(SRC:sources/minishell.c=) tests/sources/main.c $(TESTS_LIBS) -o test.out
	@./test.out

.PHONY: tests
