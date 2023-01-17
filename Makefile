NAME=minishell
CC=cc
FLAGS=-Wall -Werror -Wextra -c -I includes/
LIBFT_PATH=lib/libft
LIBFT=$(LIBFT_PATH)/libft.a
LIBS=-L$(LIBFT_PATH) -lft
TESTS_LIBS := $(LIBS)
TESTS_LIBS += -lm -lrt

FILES=minishell.c
SRC := $(addprefix sources/, $(FILES));
OBJS := $(FILES:.c=.o)

TESTS_SRCS := SRC
TESTS_SRCS := $(TESTS_SRCS:sources/minishell.c=)
TESTS_SRCS := main.c
TESTS_SRCS := $(addprefix tests/sources/, $(TESTS_SRCS))

all: | libft

libft:
	make -C $(LIBFT_PATH)
	make $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

$(OBJS): $(SRC)
	$(CC) $(FLAGS) $(SRC)

tests:
	@$(CC) -I tests/includes $(TESTS_SRCS) $(TESTS_LIBS) -o test.out
	@./test.out
	@rm -rf test.out

.PHONY: tests
