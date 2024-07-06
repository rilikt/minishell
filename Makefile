# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/30 12:29:08 by timschmi          #+#    #+#              #
#    Updated: 2024/07/06 17:22:48 by timschmi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


SRCS = main.c read_input.c parse_input.c execute_commands.c signals.c directory.c
OFILES = $(SRCS:.c=.o)
NAME = minishell
EXES = $(NAME)

SUBDIRS = libft/

LDFLAGS= -L./libft -lft -L/Users/timschmi/.brew/opt/readline/lib -lreadline -lncurses
IFLAGS = -I/Users/timschmi/.brew/opt/readline/include

CC = cc

CFLAGS = #-Wall -Wextra -Werror 

all: $(SUBDIRS) $(EXES)

$(SUBDIRS):
	$(MAKE) -C $@

$(EXES): $(OFILES)
	$(CC) $(CFLAGS) -o $@ $^ $(IFLAGS) $(LDFLAGS)
	rm -f $(OFILES)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	$(MAKE) -C libft/ clean
	rm -f $(OFILES)

fclean: clean
	$(MAKE) -C libft/ fclean
	rm -f $(EXES)

re: fclean all

.PHONY:  all clean fclean re $(SUBDIRS)