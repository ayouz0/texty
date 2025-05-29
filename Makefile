NAME = texty
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = engine/signal_handeling.c engine/textyLoop.c src/file_openning.c src/main.c
OBJS = $(SRCS:.c=.o)

HEADER = engine/engine.h header.h

all: $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
