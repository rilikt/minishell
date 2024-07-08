# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/08 10:32:41 by pstrohal          #+#    #+#              #
#    Updated: 2024/07/08 12:12:45 by pstrohal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
MAGENTA = \033[35m
CYAN = \033[36m
RESET = \033[0m

SRC_PATH := src/
OBJ_PATH := obj/
INCLUDE_PATH := include/

SRCS := main.c\
		read_input.c\
		parse_input.c\
		execute_commands.c\
		signals.c\
		directory.c

SRC =	$(addprefix $(SRC_PATH),$(SRCS))


OBJS	:= $(patsubst $(SRC_PATH)%.c, $(OBJ_PATH)%.o,$(SRC))

NAME := minishell

LIBFT := $(INCLUDE_PATH)libtf/libft.a

HEADER := shell.h

ART = $(INCLUDE_PATH)art.txt

CC = cc

CFLAGS = # -Wall -Wextra -Werror
LFLAGS = -lreadline
all: printing $(LIBS) $(NAME)

$(LIBFT):
	@echo -e "$(CYAN)Building libraries $(RESET)"
	@$(MAKE) -C $@ & PID=$$!; \
	while kill -0 $$PID 2>/dev/null; do \
		echo -n ". "; \
		sleep 0.5; \
	done; \
	wait $$PID;
	@echo ""
	@echo "$(GREEN)Build complete.$(RESET)"
	@sleep 1
	@echo " $(YELLOW)Compiling $(NAME)$(RESET)"

$(NAME): $(OBJS) welcome
	@echo ""
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "$(GREEN)$(NAME) successfully compiled!$(RESET)"
	@echo ""
	@echo "$(MAGENTA)WELCOME TO MINISHELL!!!"

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $^ -g
	@echo -n "$(GREEN)█ "

clean:
	$(MAKE) -C $(LIBFT)/ clean
	@rm -rf obj

fclean: clean
	$(MAKE) -C $(LIBFT)/ fclean
	@rm -rf $(NAME)

printing:
	@echo "$(YELLOW) $(NAME) is compiling please wait$(RESET)"

welcome:
	@cat $(ART)
	@echo "$(RESET)"
		
re: fclean all

.PHONY:  all clean fclean re 