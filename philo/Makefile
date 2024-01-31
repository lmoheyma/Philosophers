CC = cc

FLAGS = -Wall -Wextra -Werror

INCLUDE = -I inc/philo.h

SRCS = src/philo.c \
		src/parsing.c \
		src/utils.c \
		src/routine.c \
		src/monitor.c

OBJS = $(SRCS:.c=.o)

NAME = philo

all: $(NAME)

%.o : %.c
	$(CC) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) $(INCLUDE)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
