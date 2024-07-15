/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:54:15 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/15 16:59:30 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

/*	pipe	[read]	[write]	[read]	[write]
			|				|
		pipein			pipeout
*/

void	open_pipes(t_pipe *pipes, int mode)
{
	if (mode == START)
	{
		pipes->in[READ] = -1;
		pipes->in[WRITE] = -2;
		if (pipe(pipes->out) < 0)
			ft_error("pipe failed to init", ERR_PIPE);
		return ;
	}
	pipes->in[READ] = pipes->out[READ];
	pipes->in[WRITE] = pipes->out[WRITE];
	if (mode == MIDDLE)
	{
		if (pipe(pipes->out) < 0)
			ft_error("pipe failed to init", ERR_PIPE);
	}
	else if (mode == END)
	{
		pipes->out[READ] = -3;
		pipes->out[WRITE] = -4;
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

void	close_accordingly(t_pipe *pipes, int mode)
{
	if (mode == START)
	{
		if (close(pipes->out[WRITE]) < 0)
			printf("closing %d failed!!!\n", pipes->out[WRITE]);
		pipes->out[WRITE] = -4;
	}
	if (mode == MIDDLE)
	{
		if (close(pipes->out[WRITE]) < 0)
			printf("closing %d failed!!!\n", pipes->out[WRITE]);
		pipes->out[WRITE] = -4;
		if  (close(pipes->in[READ]) < 0)
			printf("closing %d failed!!!\n", pipes->in[READ]);
		pipes->in[READ] = -1;
	}
	if (mode == END)
	{
		if (close(pipes->in[READ]) < 0)
			printf("closing %d failed!!!\n", pipes->in[READ]);
		pipes->in[READ] = -1;
	}
	return ;
}

void print_pipes(t_pipe *pipes)
{
	printf ("in [%d][%d] out [%d][%d]\n\n", pipes->in[READ], pipes->in[WRITE], pipes->out[READ], pipes->out[WRITE]);
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
		open_pipes(&pipes, mode);
		pid[i] = fork();
		if (pid[i] == 0)
			run_childprocess(&shell->commands[i], &pipes, shell->envp, mode);
		else if (pid < 0)
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