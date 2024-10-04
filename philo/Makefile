# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sramos <sramos@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2024/08/26 11:45:18 by sramos        #+#    #+#                  #
#    Updated: 2024/10/04 11:16:46 by sramos        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = philo.c\
philo_utils.c\
ft_print_error.c\
parsing.c\
init.c\
start_simulation.c\
routine.c\
eating.c\
monitoring.c\
end_program.c

OBJ = $(SRC:%.c=%.o)
CC = cc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra -pthread -g
# CFLAGS += -fsanitize=thread

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

$(OBJ): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY = all, clean, fclean, re