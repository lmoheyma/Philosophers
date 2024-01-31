CC = cc

FLAGS = -Wall -Wextra -Werror

INCLUDE = -I /inc/philo.h

SRCS = src/philo.c \
		src/parsing.c \
		src/utils.c \
		src/routine.c \
		src/monitor.c \
		src/check_args.c \
		src/semaphore.c

OBJS = $(SRCS:.c=.o)

NAME = philo_bonus

all: $(NAME)

bonus: $(NAME)

%.o : %.c
	$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@

$(NAME) : $(OBJS)
	$(CC) $(FLAGS) $(INCLUDE) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re bonus
