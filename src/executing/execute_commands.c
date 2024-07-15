/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:54:15 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/15 18:30:18 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

/*	pipe	[read]	[write]	[read]	[write]
			|				|
		pipein			pipeout
*/

// void	open_pipes(t_pipe *pipes, int mode)
// {
// 	if (mode == START)
// 	{
// 		pipes->in[READ] = -1;
// 		pipes->in[WRITE] = -2;
// 		if (pipe(pipes->out) < 0)
// 			ft_error("pipe failed to init", ERR_PIPE);
// 		return ;
// 	}
// 	pipes->in[READ] = pipes->out[READ];
// 	pipes->in[WRITE] = pipes->out[WRITE];
// 	if (mode == MIDDLE)
// 	{
// 		if (pipe(pipes->out) < 0)
// 			ft_error("pipe failed to init", ERR_PIPE);
// 	}
// 	else if (mode == END)
// 	{
// 		pipes->out[READ] = -3;
// 		pipes->out[WRITE] = -4;
// 	}
// 	return ;
// }

void	close_accordingly(t_pipe *pipes, int mode)
{
	if (mode == START)
	{
		close(pipes->pipe[WRITE]);
		pipes->last_pipe = pipes->pipe[READ];
	}
	if (mode == MIDDLE)
	{
		close(pipes->last_pipe);
		close(pipes->pipe[WRITE]);
		pipes->last_pipe = pipes->pipe[READ];
	}
	if (mode == END)
	{
		close(pipes->last_pipe);
	}
	return ;
}
int	*allocate_pid(int nb)
{
	int *pid;

	pid = (int *)malloc(sizeof(int) * nb);
	if (!pid)
		ft_error("malloc pid_arr\n", ERR_MALLOC);
	return (pid);
}


void execute_commandline(t_shell *shell)
{
	int		i;
	int		*pid;
	t_pipe	pipes;
	int		mode;
	int		t[100];

	pid = allocate_pid(shell->cmd_nb - 1);
	mode = START;
	i = -1;
	while (++i < shell->cmd_nb)
	{
		if (i == shell ->cmd_nb - 1)
			mode = END;
		if (mode != END && pipe(pipes.pipe) < 0)
			ft_error("pipe filed\n", ERR_PIPE);
		pid[i] = fork();
		if (pid[i] == 0)
			run_childprocess(&shell->commands[i], &pipes, shell->envp, mode);
		else if (pid[i] < 0)
			ft_error("fork failed\n", ERR_FORK);
		close_accordingly(&pipes, mode);
		if (mode == START)
			mode = MIDDLE;
	}
	i = -1;
	while (++i < shell->cmd_nb)
	{
		waitpid(pid[i], &t[i], 0);
	}
	free(pid);
}

int main (int argc, char **argv, char **envp)
{
	t_shell shell;
	argc = 5;
	argv = NULL;
	
	shell.cmd_nb = 10;
	shell.envp = envp;
	execute_commandline(&shell);
	exit (0);
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <sys/wait.h>
// #include <string.h>

// #define START 0
// #define MIDDLE 1
// #define END 2

// typedef struct s_pipe {
//     int pipe[2];
//     int last_pipe;
// } t_pipe;

// typedef struct s_cmd {
//     // command structure here
// } t_cmd;

// typedef struct s_shell {
//     int cmd_nb;
//     t_cmd *commands;
//     char **envp;
// } t_shell;

// void ft_error(const char *msg, int err_code) {
//     perror(msg);
//     exit(err_code);
// }

// void change_std_fd(t_pipe *pipes, int mode) {
//     if (mode == START) {
//         close(pipes->pipe[0]); // close read end of current pipe
//         if (dup2(pipes->pipe[1], STDOUT_FILENO) == -1) {
//             ft_error("dup2 failed", 1);
//         }
//         close(pipes->pipe[1]); // close write end of current pipe
//     } else if (mode == MIDDLE) {
//         if (dup2(pipes->last_pipe, STDIN_FILENO) == -1) {
//             ft_error("dup2 failed", 1);
//         }
//         close(pipes->last_pipe); // close last pipe after duplicating
//         close(pipes->pipe[0]); // close read end of current pipe
//         if (dup2(pipes->pipe[1], STDOUT_FILENO) == -1) {
//             ft_error("dup2 failed", 1);
//         }
//         close(pipes->pipe[1]); // close write end of current pipe
//     } else if (mode == END) {
//         if (dup2(pipes->last_pipe, STDIN_FILENO) == -1) {
//             ft_error("dup2 failed", 1);
//         }
//         close(pipes->last_pipe); // close last pipe after duplicating
//     }
// }

// void run_childprocess(t_cmd *cmd, t_pipe *pipes, char **envp, int mode) {
//     change_std_fd(pipes, mode);
//     cmd = NULL;  // You should probably do something with cmd
//     envp = NULL; // You should probably do something with envp

//     char buffer[200];
//     int bts_read;

//     if (mode == START) {
//         int fd = open("hallo.txt", O_RDONLY);
//         if (fd == -1) {
//             ft_error("open failed", 1);
//         }
//         while ((bts_read = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
//             buffer[bts_read] = '\0';
//             write(STDOUT_FILENO, buffer, bts_read);
//         }
//         if (bts_read == -1) {
//             close(fd);
//             ft_error("read failed", 1);
//         }
//         close(fd);
//     } else {
//         while ((bts_read = read(STDIN_FILENO, buffer, sizeof(buffer) - 1)) > 0) {
//             buffer[bts_read] = '\0';
//             write(STDOUT_FILENO, buffer, bts_read);
//         }
//         if (bts_read == -1) {
//             ft_error("read failed", 1);
//         }
//     }

//     // Close the pipes if necessary
//     if (mode == START || mode == MIDDLE) {
//         close(STDOUT_FILENO);
//     }
//     if (mode == MIDDLE || mode == END) {
//         close(STDIN_FILENO);
//     }
//     exit(0);
// }

// void close_accordingly(t_pipe *pipes, int mode) {
//     if (mode == START) {
//         close(pipes->pipe[1]);
//         pipes->last_pipe = pipes->pipe[0];
//     } else if (mode == MIDDLE) {
//         close(pipes->last_pipe);
//         close(pipes->pipe[1]);
//         pipes->last_pipe = pipes->pipe[0];
//     } else if (mode == END) {
//         close(pipes->last_pipe);
//     }
// }

// int *allocate_pid(int nb) {
//     int *pid = (int *)malloc(sizeof(int) * nb);
//     if (!pid) {
//         ft_error("malloc pid_arr", 1);
//     }
//     return pid;
// }

// void execute_commandline(t_shell *shell) {
//     int i;
//     int *pid;
//     t_pipe pipes;
//     int mode;
//     int t[100];

//     pid = allocate_pid(shell->cmd_nb);
//     mode = START;
//     i = -1;
//     while (++i < shell->cmd_nb) {
//         if (i == shell->cmd_nb - 1)
//             mode = END;
//         if (mode != END && pipe(pipes.pipe) < 0) {
//             ft_error("pipe failed", 1);
//         }
//         pid[i] = fork();
//         if (pid[i] == 0) {
//             run_childprocess(&shell->commands[i], &pipes, shell->envp, mode);
//         } else if (pid[i] < 0) {
//             ft_error("fork failed", 1);
//         }
//         close_accordingly(&pipes, mode);
//         if (mode == START)
//             mode = MIDDLE;
//     }
//     i = -1;
//     while (++i < shell->cmd_nb) {
//         waitpid(pid[i], &t[i], 0);
//     }
//     free(pid);
// }

// int main(int argc, char **argv, char **envp) {
//     t_shell shell;
//     argc = 5;
//     argv = NULL;

//     shell.cmd_nb = 10;
//     shell.envp = envp;
//     // Initialize shell.commands here
//     execute_commandline(&shell);
//     exit(0);
// }
