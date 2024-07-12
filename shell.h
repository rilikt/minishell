/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:17:50 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/12 16:27:37 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

#include "include/libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

enum e_type {
	WORD,
	VARIABLE,
	IN_REDIRECT,
	IN_HEREDOC,
	OUT_REDIRECT,
	OUT_RED_APPEND,
	PIPE,
} ;

enum e_mode {
	INTERACTIVE,
	NON_INTERACTIVE,
} ;

typedef struct s_redirect {
	int		type;
	char	*filename;
	struct s_redirect	*next;
} t_rdct;


typedef struct s_tokenlist {
	int		type;
	char	*str;
	int		index;
	struct s_tokenlist	*prev;
	struct s_tokenlist	*next;
} t_token;


typedef struct s_command {
	char	**args;
	t_rdct	*reds;
	struct s_command	*next;
} t_cmd;

typedef struct s_shell {
	int		mode;
	char	*input;
	t_token	*tokens;
	t_cmd	*commands;
	int		cmd_nb;
	int		exitstatus;
	
} t_shell;


/*		builtins		*/


/*		error and utils	*/


/*		executer		*/


/*		expander		*/


/*		mode_nd_signals	*/


/*		parser			*/


/*		tokenizer		*/
void tokenize(t_shell **shell);
int is_whitespace(char c);
int is_operator(char *str, int *input_i);
int in_qoutes(char *str, int *input_i);
void append_node(t_token **head, char *str);
int operator_check(char c);
void print_tokens(t_shell *shell);





char *read_input(void);
void execute_commands(char **arg);
void signal_handle(int signum);
void go_home(void);
void change_directory(char **arg);
void display_pwd(char **arg);
void exit_shell(void);
void clean_shell(char **str);
void print_env(char **arg);
int check_operators(char *arg);
void parse_input(char **arg);
void print_list(t_cmd *head);




#endif