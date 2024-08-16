/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:17:50 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/16 12:00:35 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "include/get_next_line/get_next_line.h"
# include "include/libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <sys/stat.h>

# ifndef GLOBAL_H
#  define GLOBAL_H

extern int				g_sig;
# endif

enum	e_errorcodes
{
	ERR_EXIT = 1,
	ERR_MALLOC = ENOMEM,
	ERR_FILE = 2,
	ERR_SYNTAX,
	ERR_PIPE,
	ERR_FORK,
	ERR_DUP2,
	ERR_OPEN,
	ERR_READ,
	ERR_CLOSE,
	ERR_SPLIT,
	ERR_PERMISSION = 13,
	ERR_EXPORT,
	ERR_WRITE,
	ERR_DIR = 126,
	ERR_PATH = 127,
};

enum	e_forkmode
{
	START,
	MIDDLE,
	END,
};

enum	e_pipeends
{
	READ,
	WRITE,
};

enum	e_builtins
{
	NOT_SET = -1,
	FT_ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	EXTERN,
	NO_CMD,
};

enum	e_type
{
	WORD,
	VARIABLE,
	IN_REDIRECT,
	IN_HEREDOC,
	OUT_REDIRECT,
	OUT_RED_APPEND,
	PIPE,
	IN_QUOTES,
};

enum	e_mode
{
	INTERACTIVE,
	NON_INTERACTIVE,
};

typedef struct s_redirect
{
	int					type;
	char				*filename;
	char				*char_vars;
	int					*int_vars;
	int					in_fd;
	int					out_fd;
	struct s_redirect	*next;
}						t_rdct;

typedef struct s_tokenlist
{
	int					type;
	char				*str;
	char				*char_vars;
	int					*int_vars;
	int					index;
	struct s_tokenlist	*prev;
	struct s_tokenlist	*next;
}						t_token;

typedef struct s_command
{
	char				**args;
	int					is_var;
	char				*char_vars;
	int					*int_vars;
	int					builtin_flag;
	int					stdout_fd;
	int					stdin_fd;
	t_rdct				*reds;
	int					var_in_redir;

	struct s_command	*next;
}						t_cmd;

typedef struct s_piping
{
	int					pipe[2];
	int					last_pipe;
}						t_pipe;

typedef struct arg_vars
{
	int					*s_index;
	int					*e_index;
	char				*type;
}						t_avars;

typedef struct s_expand_help
{
	char				**envp;
	t_avars				*arg_vars;
	int					v_count;
	char				**str;
	int					exit;
}						t_exp;

typedef struct s_shell
{
	int					mode;
	char				**envp;
	char				*input;
	t_token				*tokens;
	t_cmd				*commands;
	char				*char_vars;
	int					*int_vars;
	int					cmd_nb;
	int					exitstatus;
	int					err;
	struct termios		term[2];
	struct sigaction	signals;
}						t_shell;

typedef struct s_redir_val
{
	char				*filename;
	int					type;
	int					*int_vars;
	char				*vars;
}						t_redir_val;

/*========================================================*/
/*==				main.c								==*/
/*========================================================*/
// main
/*========================================================*/
/*==				builtins							==*/
/*========================================================*/
// builtin.c
int		single_cmd_check(t_shell *shell);
int		check_and_exec_builtins(t_cmd *cmd, t_shell *shell);
void	check_builtins(t_cmd *cmd);

// directory.c
int		pwd(void);
int		cd(char **arg, char ***envp);
void	go_home(void);
void	update_env(char ***envp);

// echo.c
int		echo(char **args);

// env.c
int		env(char **arg, char **envp);
char	**copy_env(char **envp);

// export.c
int		export(char **args, char ***envp);
int		var_len(char *str, char *str2);
char	**append_env(char *var, char **envp);

// export_append.c
char	*rm_plus(char *str);
int		ex_append_loop(char ***envp, char *arg, int len);
int		check_plus(char *arg);
int		export_append(char **args, char ***envp, int *j);

// export_print.c
void	add_qoutes(char **envp);
int		copy_envp(char ***local_envp, char **envp);
void	export_print(char **envp);
int		check_and_print(char **args, char ***envp);

// unset.c
int		unset(char **args, char ***envp);
char	**unset_loop(char **re, char ***envp, char **args);
int		compare_to_envp(char **args, char *envp);

// export_unset_input_check.c
int		check_input(char **args, char ***envp, int mode);
int		invalid_char(char *c, int mode);

// ft_getenv.c
char	*ft_getenv(char *find, char **env);

// exit.c
int		ft_exit(char **args, int *err, int exitstatus);

// set_.c
void	set_last_arg(t_cmd *cmd, char ***envp, int mode);

/*========================================================*/
/*==				error and utils						==*/
/*========================================================*/
// error.c
void	ft_error(char *arg, char *msg, int errorcode);
void	ft_sytax_error(int *err, t_token *tkn);
void	error_check(void *ptr, const char *msg, int error_code);
void	quotes_err(int *err);

// cleaning.c
void	free_string_array(char **str);
void	exit_shell(void);
void	free_tokens(t_shell *shell);

//wrapper_functions.c
char	*ms_strdup(const char *str);
char	*ms_substr(const char *str, unsigned int start, size_t len);
char	**ms_split(char *str, char c);
char	*ms_strjoin(char const *s1, char const *s2);
char	*ms_freejoin(char *s1, char const *s2);

/*========================================================*/
/*==				executer							==*/
/*========================================================*/
// child.c
void	run_childprocess(t_cmd *cmd, t_pipe *pipes, t_shell *shell, int mode);
char	*get_path(char *cmd, t_shell *shell);

// execute_commandline.c
void	execute_commandline(t_shell *shell);
int		wait_for_children(int *pid, int nb);

// piping_utils.c
void	close_accordingly(t_pipe *pipes, int *mode);
int		*allocate_pid(int nb);
void	change_std_fd(t_pipe *pipes, int mode);
void	ft_close(int fd, char *msg);
void	ft_dup2(int new, int old, char *msg);

// redirecting.c
void	change_input_fd(t_rdct *reds, int *err);
void	change_output_fd(t_rdct *reds, int mode, int *err);
void	pipe_heredoc(t_rdct *reds, int *err);
void	redirect_accordingly(t_rdct *reds, int *err);

/*========================================================*/
/*==				expander							==*/
/*========================================================*/
// expanding.c
void	expand_string(char **str, int type, t_exp *utils, int i);
int		expand_redirects(t_rdct *reds, t_exp *utils);
int		expand_cmd(t_cmd *cmd, int exitstatus, char **envp);

// expanding_utils.c
int		*check_char_behind(char **pos);
int		ft_arr_len(char **arr);
void	free_arg_vars(t_exp *utils, int arg_len);
void	setup_help_struct(t_cmd *cmd, t_exp *utils, int arg_len, int vars_used);
int		count_vars_in_str(char *str);
void	expand_heredoc(char **str, t_exp *utils);

//expand_heredoc.c
int		*check_char_behind(char **pos);
void	expand_heredoc(char **str, t_exp *utils);

//handle_var.c
char	*get_var(char *pos, char **var_name, int var_len, t_exp *utils);
int		insert_var(char **str, char *pos, char *var_value, char *var_name);
void	handle_case_one_two(int i, char **pos, int *tmp, t_exp *utils);
void	handle_var(int i, char **pos, int *tmp, t_exp *utils);

// splitting_utils.c
int		check_if_must_split(char *arg, t_avars *arg_vars);
char	**split_arg(char **args, t_avars *arg_vars, int *i, int a);
void	rejoin_args(char **args, char **new_args, char **arr, int *i);

//divide_argument.c
char	**make_arr_from_list(t_list **new_arg);
void	fill_node(t_list **new_arg, char *str);
void	setup_for_splitting(int *i, int *prev, t_list **new_arg);
void	iterate_index_area(char *str, t_list **new_arg, int *index, int *prev);
char	**divide_string_correctly(char *str, t_avars arg_vars);

/*========================================================*/
/*==				mode_nd_signals						==*/
/*========================================================*/

// initialize.c
void	setup_shell(t_shell *shell, char **envp, int argc, char **argv);
char	*put_input(int argc, char **argv);

// signals.c
void	signal_handler(int signum);
void	check_mode_handle_signals(t_shell *shell);

/*========================================================*/
/*==				parser								==*/
/*========================================================*/

// parse_nodes.c
char	**create_array(t_token *start, t_token *end);
char	**append_array(char **arr, t_token *start, t_token *end);
void	append_cmd_node(t_cmd **head);
void	store_in_cmd(t_cmd **head, char **arr, char *vars, int *int_vars);

// parse_redir.c
int		check_redir(t_cmd **command, t_token **tkn_temp, int *err);
void	append_rdct_node(t_cmd **head, t_redir_val *redir);
int		is_redir(t_token *token);

// parse_utils.c
void	print_commands(t_shell *shell);
void	print_arr(char **arr);

// parse.c
void	while_not_op(t_token **temp, t_shell *shell,
			char **vars, int **int_vars);
void	parse_tokens(t_shell *shell);
int		*add_to_arr(char *vars, int *arr, char *added, int *int_vars);

/*		general utils	*/
void	free_struct(t_shell *shell);

/*========================================================*/
/*==				tokenizer							==*/
/*========================================================*/

// read_input.c
int		check_whitespace(char *input);
char	*use_get_next(void);
char	*read_input(int mode, t_shell *shell);

// token_list.c
int		find_type(char *str, int q_flag);
t_token	*create_node(char *str, int q_flag, t_shell *shell);
void	append_node(t_token **head, char *str, int q_flag, t_shell *shell);

// tokenizer.c
void	tokenize(t_shell *shell);
int		operator_check(char *str, int *input_i);
int		is_operator(char *str, int *input_i);
int		is_whitespace(char c);
void	print_tokens(t_shell *shell);
int		token_loop(int i, char *str, t_shell *shell);

// token_vars.c
int		check_variable(char *str, int q_flag);
char	*set_vars(char *str, char *vars);
int		*set_int_vars(int *arr, char *str, char *vars);

// quotes.c
char	*check_qoutes(char *str, int *q_flag, t_shell *shell);
char	*rm_qoutes(char *str);
int		in_qoutes(char *str, int *input_i, t_shell *shell);
int		is_closed(char *str, int q_count, int start, t_shell *shell);
char	*create_string(char *str, char *re, int i, int k);

// expander_flags.c
void	char_var_list(t_shell *shell);
void	var_lists(t_shell *shell);
char	*cvl_if_quotes(char *vars, t_shell *shell, int *i);
int		check_end(char c);

// expander_flags_int.c
void	int_var_list(t_shell *shell);
void	ivl_loop(int *arr, t_shell *shell, int *i, int *j);

// heredoc.c
int		count_quotes(char *str, int q_count, int start);
char	*check_and_rm_quotes(char *str);
char	*heredoc_loop(char *delimiter);
void	is_heredoc(t_token *node, int q_flag);

// int		check_operators(char *arg);

#endif