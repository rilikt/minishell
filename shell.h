/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:17:50 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/31 16:52:44 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "include/libft/libft.h"
# include "include/get_next_line/get_next_line.h"
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <errno.h>
# include <termios.h>
# include <string.h>
# include <sys/wait.h>

# ifndef GLOBAL_H
#  define GLOBAL_H
	extern int sig;
# endif 

enum e_errorcodes {
	ERR_EXIT = 1,
	ERR_MALLOC = ENOMEM,
	ERR_SYNTAX,
	ERR_PIPE,
	ERR_FORK,
	ERR_DUP2,
	ERR_OPEN,
	ERR_READ,
	ERR_CLOSE,
	ERR_SPLIT,
	ERR_PATH = 127,
	ERR_EXPORT,
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

enum e_builtins {
	NOT_SET = -1,
	FT_ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	EXTERN,
} ;

enum e_type {
	WORD,
	VARIABLE,
	IN_REDIRECT,
	IN_HEREDOC,
	OUT_REDIRECT,
	OUT_RED_APPEND,
	PIPE,
	IN_QUOTES,
} ;

enum e_mode {
	INTERACTIVE,
	NON_INTERACTIVE,
} ;

typedef struct s_redirect {
	int					type;
	char				*filename;
	char				*vars;
	int					in_fd;
	int					out_fd;
	struct s_redirect	*next;
}	t_rdct;

typedef struct s_tokenlist {
	int					type;
	char				*str;
	char				*vars;
	int					index;
	struct s_tokenlist	*prev;
	struct s_tokenlist	*next;
}	t_token;

typedef struct s_command {
	char				**args;
	int					is_var;
	char				*vars;
	int					builtin_flag;
	int					stdout_fd;
	t_rdct				*reds;
	int					var_in_redir;
	struct termios		term;
	struct s_command	*next;
}	t_cmd;

typedef struct s_piping {
	int		pipe[2];
	int		last_pipe;
}	t_pipe;

typedef struct s_expand_help {
	char	**envp;
	char	*vars;
	int		exit;
} t_exp_help ;

typedef struct s_shell {
	int					mode;
	char				**envp;
	char				*input;
	t_token				*tokens;
	t_cmd				*commands;
	char				*vars;
	int					cmd_nb;
	int					exitstatus;
	int					err;
	struct termios		term[2];
	struct sigaction	signals;
}	t_shell;

/*		main.c			*/
void	setup_shell(t_shell *shell, char **envp);
void	check_mode_handle_signals(t_shell *shell);


/*		builtins		*/
// builtin.c
int		single_cmd_check(t_cmd *cmd, int exitstatus, char **envp);
void	check_and_exec_builtins(t_cmd *cmd, char ***envp, int *err);
void	check_builtins(t_cmd *cmd);

// directory.c
void	pwd(char **arg);
void	cd(char **arg, char ***envp);
void	go_home(void);
void	update_env(char ***envp);

// echo.c
void	echo(char **args);

// env.c
void	env(char **arg, char **envp);
char 	**copy_env(char **envp);

// export.c export_2.c
void	export(char **args, char ***envp);
char	*ft_getenv(char *find, char **env);
int		var_len(char *str, char *str2);
char	**append_env(char *var, char **envp);
void	add_qoutes(char **envp);
int		copy_envp(char ***local_envp, char **envp);
void	export_print(char **envp);
int		check_and_print(char **args, char ***envp);

// unset.c
void	unset(char **args, char ***envp);
int		compare_to_envp(char **args, char *envp);

/*		error and utils	*/
void	ft_error(char *msg, int errorcode);
void	error_check(void *ptr, char *msg, int error_code);

// cleaning.c
void	free_string_array(char **str);
void	exit_shell(void);

/*		executer		*/
//child.c
void	run_childprocess(t_cmd *cmd, t_pipe *pipes, t_shell *shell, int mode);
char	*get_path(char *cmd);

//execute_commandline.c
void	execute_commandline(t_shell *shell);
int		wait_for_children(int *pid, int nb);

//piping_utils.c
void	close_accordingly(t_pipe *pipes, int *mode);
int		*allocate_pid(int nb);
void	change_std_fd(t_pipe *pipes, int mode);
void	ft_close(int fd);
void	ft_dup2(int new, int old);


//redirecting.c
void	change_input_fd(t_rdct *reds);
void	change_output_fd(t_rdct *reds, int mode);
void	redirect_accordingly(t_rdct *reds);

/*		expander		*/

//expanding.c
void	expand_cmd(t_cmd *cmd, int exitstatus, char **envp);

//expanding_utils.c
void	check_char_behind(char **pos, char **str, int *tmp);
char	**split_and_arrange_cmd(char **args);

/*		mode_nd_signals	*/
void	signal_handler(int signum);

/*		parser			*/

//parse_nodes.c
char	**create_array(t_token *start, t_token *end);
char	**append_array(char **arr, t_token *start, t_token *end);
void	append_cmd_node(t_cmd **head);
void	store_in_cmd(t_cmd **head, char **arr, int is_var, char *vars);

//parse_redir.c
t_token	*check_redir(t_cmd **command, t_token *tkn_temp);
void	append_rdct_node(t_cmd **head, int type, char *filename, int is_var, char *vars);
int		is_redir(t_token *token);

// parse_utils.c
void	print_commands(t_shell *shell);
void	print_arr(char **arr);

//parse.c
void	while_not_op(t_token **temp, int *is_var, t_shell *shell, char **vars);
void	parse_tokens(t_shell *shell);
void	create_var_list(t_shell *shell);

/*		general utils	*/
void	free_struct(t_shell *shell);

/*		tokenizer		*/

//read_input.c
int		check_whitespace(char *input);
char	*read_input(int mode);

//token_list.c
int		check_variable(char *str, int q_flag);
int		find_type(char *str, int q_flag);
t_token	*create_node(char *str, int q_flag, char *vars);
void	is_heredoc(t_token *node);
void	append_node(t_token **head, char *str, int q_flag, t_shell *shell);
char	*set_vars(char *str, char *vars);


//tokenizer.c
void	tokenize(t_shell *shell);
int		operator_check(char *str, int *input_i);
int		is_operator(char *str, int *input_i);
int		is_whitespace(char c);
void	print_tokens(t_shell *shell);
int		token_loop(int i, char *str, t_shell *shell);

// quotes.c
char	*check_qoutes(char *str, int *q_flag, t_shell *shell);
char	*rm_qoutes(char *str);
int		in_qoutes(char *str, int *input_i, t_shell *shell);
int		is_closed(char *str, int q_count, int start, t_shell *shell);
char	*create_string(char *str, char *re, int i, int k, int start);

// int		check_operators(char *arg);

#endif