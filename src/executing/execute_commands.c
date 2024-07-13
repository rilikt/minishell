/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:54:15 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/13 19:05:01 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

/*	pipe	[read]	[write]	[read]	[write]
			|				|
		pipein			pipeout
*/

void	open_pipe(int *pipes, int mode)
{
	if (mode == START)
	{
		pipes[IN_READ] = -1;
		pipes[IN_WRITE] = -1;
		if (pipe(&pipes[OUT_READ]) < 0)
			ft_error("pipe failed to init", ERR_PIPE);
		return ;
	}
	pipes[IN_READ] = pipes[OUT_READ];
	pipes[IN_WRITE] = pipes[OUT_WRITE];
	if (mode == MIDDLE)
	{
		if (pipe(&pipes[OUT_READ]) < 0)
			ft_error("pipe failed to init", ERR_PIPE);
	}
	else if (mode == END)
	{
		pipes[OUT_READ] = -1;
		pipes[OUT_WRITE] = -1;
	}
	return (pipes);
}

int	*allocate_pid(int nb)
{
	int *pid;

	pid = (int *)malloc(sizeof(int) * nb);
	if (!pid)
		ft_error("malloc pid_arr\n", ERR_MALLOC);
	return (pid);
}

void	close_accordingly(int *pipes, int mode)
{
	if (mode == 1)
	{
		close(pipes[OUT_WRITE]);
		pipes[OUT_WRITE] = -1;
	}
	if (mode == MIDDLE)
	{
		close(pipes[OUT_WRITE]);
		pipes[OUT_WRITE] = -1;
		close(pipes[IN_READ]);
		pipes[IN_READ] = -1;
	}
	if (mode == END);
	{
		close(pipes[IN_READ]);
		pipes[IN_READ] = -1;
	}
	return ;
}

void execute_commandline(t_shell *shell)
{
	int		i;
	int		*pid;
	int		pipes[4];
	char	*cmd;
	int		mode;

	pid = allocate_pid(shell->cmd_nb - 1);
	mode = START;
	i = -1;
	while (++i < shell->cmd_nb)
	{
		if (i = shell ->cmd_nb - 1)
			mode = END;
		open_pipes(pipes, mode);
		pid[i] = fork();
		if (pid[i] == 0)
			run_childrocess(shell->commands[i], &pipes, &shell->envp, mode);
		else if (pid < 0)
			ft_error("fork failed\n", ERR_FORK);
		if (mode == START)
			mode = MIDDLE;
		close_accordingly(pipes, mode);
	}
}
