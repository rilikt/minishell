/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:17:50 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/11 14:44:33 by timschmi         ###   ########.fr       */
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
	t_rdct	*next;
} t_rdct;

typedef struct s_token
{
	int		type;
	char	*str;
} t_token;

typedef struct s_tokenlist {
	int		index;
	t_token	*token;
	t_list	*prev;
	t_list	*next;
} t_list;


typedef struct s_command {
	char	**args;
	t_rdct	*reds;
	t_cmd	*next;
} t_cmd;

typedef struct s_shell {
	int		mode;
	char	*input;
	t_list	*tokens;
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

typedef struct s_cmd 
{
	char *op;

	char *cmd1;
	char *arg1;

	char *cmd2;
	char *arg2;

	struct s_cmd *next;

}	t_cmd;

char *read_input(void);
char **tokenize(char *str);
void execute_commands(char **arg);
void signal_handle(int signum);
void go_home(void);
void change_directory(char **arg);
void display_pwd(char **arg);
void exit_shell(void);
void clean_shell(char **str);
void print_env(char **arg);
int check_operators(char *arg);
void append_node(t_cmd **head, char **arg, int i);
void parse_input(char **arg);
void print_list(t_cmd *head);




#endif