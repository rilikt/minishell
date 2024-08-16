/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:54:15 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/16 15:00:43 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	pipe_mode_check(t_pipe *pipes, int *mode, int i, int cmd_nb)
{
	if (i == 0)
	{
		pipes->pipe[0] = -1;
		pipes->pipe[1] = -1;
		pipes->last_pipe = -1;
	}
	if (i == cmd_nb - 1)
		*mode = END;
	if (*mode != END && pipe(pipes->pipe) < 0)
		ft_error(NULL, "pipe filed", ERR_PIPE);
	return ;
}

int	wait_for_children(int *pid, int nb)
{
	int	i;
	int	t;

	i = -1;
	legit_variable(1, 15);
	while (++i < nb)
	{
		waitpid(pid[i], &t, 0);
		t = WEXITSTATUS(t);
	}
	legit_variable(1, 0);
	free(pid);
	pid = NULL;
	return (t);
}

void	execute_commandline(t_shell *shell)
{
	int		i;
	int		*pid;
	t_pipe	pipes;
	int		mode;
	t_cmd	*tmp;

	tmp = shell->commands;
	pid = allocate_pid(shell->cmd_nb);
	mode = START;
	i = -1;
	while (++i < shell->cmd_nb)
	{
		pipe_mode_check(&pipes, &mode, i, shell->cmd_nb);
		pid[i] = fork();
		if (pid[i] == 0)
			run_childprocess(tmp, &pipes, shell, mode);
		else if (pid[i] < 0)
			ft_error(NULL, "fork failed", ERR_FORK);
		if (tmp->next)
			tmp = tmp->next;
		close_accordingly(&pipes, &mode);
	}
	shell->exitstatus = wait_for_children(pid, shell->cmd_nb);
	set_last_arg(shell->commands, &shell->envp, 1);
	return ;
}
