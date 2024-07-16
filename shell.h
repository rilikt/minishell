/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:17:50 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/16 18:57:11 by pstrohal         ###   ########.fr       */
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
#include <sys/wait.h>

enum e_errorcodes {
	ERR_MALLOC = 1,
	ERR_SYNTAX,
	ERR_PIPE,
	ERR_FORK,
	ERR_DUP2,
	ERR_READ,
	ERR_CLOSE,
	ERR_SPLIT,
} ;

enum e_forkmode {
	START,
	MIDDLE,
	END,
} ;

enum e_pipeends {
	READ,
	WRITE,
} ;

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
	int					type;
	char				*str;
	int					index;
	struct s_tokenlist	*prev;
	struct s_tokenlist	*next;
} t_token;


typedef struct s_command {
	char	**args;
	int		is_var;

	int		var_in_redir;
	struct s_command	*next;
} t_cmd;

typedef struct s_piping {
	int		pipe[2];
	int		last_pipe;
} t_pipe;

typedef struct s_shell {
	int		mode;
	char	**envp;
	char	*input;
	t_token	*tokens;
	t_cmd	*commands;
	int		cmd_nb;
	int		exitstatus;
	
} t_shell;


/*		builtins		*/
void	go_home(void);
void	change_directory(char **arg);
void	display_pwd(char **arg);
void	print_env(char **arg);


/*		error and utils	*/
void	ft_error(char *msg, int errorcode);
void	clean_shell(char **str);
void	exit_shell(void);


/*		executer		*/
//child.c
void	run_childprocess(t_cmd *cmd, t_pipe *pipes, t_shell *shell, int mode);

//execute_commandline.c
void	execute_commandline(t_shell *shell);
int		wait_for_children(int  *pid, int nb);

//piping_utils.c
void	close_accordingly(t_pipe *pipes, int mode);
int		*allocate_pid(int nb);
void	change_std_fd(t_pipe *pipes, int mode);

/*		expander		*/
//expanding.c
void	expande(t_cmd *cmd, char **envp);


/*		mode_nd_signals	*/
void	signal_handle(int signum);


/*		parser			*/
void parse_tokens(t_shell *shell);
void print_commands(t_shell *shell);



/*		tokenizer		*/
char	*read_input(void);
void	tokenize(t_shell *shell);
int		is_whitespace(char c);
int		is_operator(char *str, int *input_i);
int		in_qoutes(char *str, int *input_i);
void	append_node(t_token **head, char *str);
int		operator_check(char *str, int *input_i);
void	print_tokens(t_shell *shell);
int		check_operators(char *arg);

#endif