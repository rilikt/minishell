# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/08 10:32:41 by pstrohal          #+#    #+#              #
#    Updated: 2024/08/03 15:11:06 by timschmi         ###   ########.fr        #
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

BUILTINS :=	directory.c\
			builtin.c\
			echo.c\
			env.c\
			export.c\
			export_2.c\
			unset.c
ERR_CLEAN:=	error.c\
			cleaning.c
EXECUTING:= child.c\
			execute_commands.c\
			piping_utils.c\
			redirecting.c
EXPANDING:= expanding.c\
			expanding_utils.c
MDE_SGNL :=	signals.c
PARSING  :=	parse.c\
			parse_redir.c\
			parse_utils.c\
			parse_arr_and_nodes.c
TOKENIZER:=	read_input.c\
			token_list.c\
			tokenizer.c\
			quotes.c\
			expander_flags.c

SOURCES = main.c\
		$(addprefix builtins/,$(BUILTINS))\
		$(addprefix error_and_cleaning/,$(ERR_CLEAN))\
		$(addprefix executing/,$(EXECUTING))\
		$(addprefix expanding/,$(EXPANDING))\
		$(addprefix mode_and_signals/,$(MDE_SGNL))\
		$(addprefix parsing/,$(PARSING))\
		$(addprefix tokenizing/,$(TOKENIZER))
		
		
SRC =	$(addprefix $(SRC_PATH),$(SOURCES))


OBJS	:= $(patsubst $(SRC_PATH)%.c, $(OBJ_PATH)%.o,$(SRC))
NAME := minishell
LIB := $(INCLUDE_PATH)libft
LIBG := $(INCLUDE_PATH)get_next_line
LIBFT :=	$(INCLUDE_PATH)libft/libft.a\
			$(INCLUDE_PATH)get_next_line/get_next_line.a
HEADER := shell.h
ART = $(INCLUDE_PATH)art.txt
CC = cc
CFLAGS = # -Wall -Wextra -Werror
LFLAGS = -L$(LIB) -lft -lreadline -L$(LIBG) -lget_next_line

all: $(NAME)
$(LIBFT):

	@$(MAKE) -C $(LIBG)
	@printf "$(CYAN)Building libraries$(RESET)"
	@$(MAKE) -C $(LIB) & PID=$$!; \
	while kill -0 $$PID 2>/dev/null; do \
		printf "$(CYAN). $(RESET)"; \
		sleep 0.1; \
	done; \
	wait $$PID;
	@printf "$(GREEN)\nBuild complete.$(RESET)\n\n"
	@sleep 1
	@printf "$(YELLOW)Compiling $(NAME)$(RESET)\n\n"
	
$(NAME): $(OBJS)
	@$(MAKE) print
	@$(MAKE) $(LIBFT)
	@$(CC) $(CFLAGS) -o $@ $^ $(LFLAGS) -O0 -g
	@printf "$(GREEN)$(NAME) successfully compiled!$(RESET)\n\\n"
	@printf "$(MAGENTA)WELCOME TO MINISHELL!!!$(RESET)\n\n"
	# @$(MAKE) welcome 
	
obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -o $@ -c $^ -O0 -g
	@printf "$(GREEN)█ $(RESET)"

clean:
	@printf "\n$(BLUE)MAKING CLEAN$(RESET)\n\n"
	@$(MAKE) -C $(LIB)/ clean
	@printf "$(BLUE)REMOVING OBJECT FILES$(RESET)\n\n"
	@rm -rf obj

fclean: clean
	@printf "$(BLUE)"
	@$(MAKE) -C $(LIB)/ fclean
	@$(MAKE) -C $(LIBG)/ fclean
	@printf "$(BLUE)REMOVING EXECUTABLE$(RESET)\n\n"
	@rm -rf $(NAME)

print:
	@printf "\n\n$(YELLOW)$(NAME) is compiling please wait$(RESET)\n\n"

welcome:
	@printf "$(MAGENTA)"
	@cat $(ART)
	@printf "$(RESET)\n\n\n"
	

re: fclean all

.PHONY: all clean fclean re print welcome ft
