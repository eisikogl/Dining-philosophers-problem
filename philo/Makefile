NAME = philo

CC = gcc

CFLAGS = -Wall -Wextra -Werror

TFLAG = -pthread

RM = rm -rf

SRCS = $(wildcard srcs/*.c)

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(TFLAG) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
		$(RM) $(OBJS)
	
fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY:all clean fclean re


