NAME=minishell
CC=cc
FLAGS=-Wall -Werror -Wextra -c -I includes/
LIBFT_PATH=lib/libft
LIBFT=$(LIBFT_PATH)/libft.a
LIBS=-L$(LIBFT_PATH) -lft

FILES=minishell.c
SRC := $(addprefix sources/, $(FILES));
OBJS := $(FILES:.c=.o)

all: | libft

libft:
	make -C $(LIBFT_PATH)
	make $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

$(OBJS): $(SRC)
	$(CC) $(FLAGS) $(SRC)
