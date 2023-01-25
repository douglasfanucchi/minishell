NAME=minishell
CC=cc
FLAGS=-Wall -Werror -Wextra -c -I includes/ -I lib/libft
LIBFT_PATH=lib/libft
LIBFT=$(LIBFT_PATH)/libft.a
LIBS=-L$(LIBFT_PATH) -lft -lreadline
TESTS_LIBS = $(LIBS) -lm -lrt

FILES=minishell.c tokens/tokenizer.c tokens/token.c tokens/redirect.c \
      analyser/redirection.c analyser/pipe.c analyser/quoted.c analyser/analyse.c
SRC := $(addprefix sources/, $(FILES))
OBJS := $(FILES:.c=.o)
OBJS := $(OBJS:tokens/%=%)

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
