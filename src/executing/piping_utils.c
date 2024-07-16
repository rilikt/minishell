/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:42:29 by pstrohal          #+#    #+#             */
/*   Updated: 2024/07/16 11:21:40 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	close_accordingly(t_pipe *pipes, int *mode)
{
	if (*mode == START)
	{
		if (close(pipes->pipe[WRITE]) < 0);
			ft_error("oh shit!", ERR_CLOSE);
		pipes->last_pipe = pipes->pipe[READ];
		*mode = MIDDLE;
	}
	if (*mode == MIDDLE)
	{
		if (close(pipes->last_pipe) < 0)
			ft_error("oh shit!", ERR_CLOSE);
		if (close(pipes->pipe[WRITE]) < 0);
			ft_error("oh shit!", ERR_CLOSE);
		pipes->last_pipe = pipes->pipe[READ];
	}
	if (*mode == END)
	{
		if (close(pipes->last_pipe) < 0)
			ft_error("oh shit!", ERR_CLOSE);
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
int	*wait_for_children(int  *pid, int nb)
{
	int	i;
	int	*t;

	t = (int *)malloc(sizeof(int) * nb);
	if (!t)
		ft_error("malloc failed", ERR_MALLOC);
	i = -1;
	while (++i < nb)
	{
		waitpid(pid[i], &t[i], 0);
	}
	free(pid);
	pid = NULL;
	return ;
}

void	change_std_fd(t_pipe *pipes, int mode)
{
	if (mode == START)
	{
		if (close(pipes->pipe[READ]) < 0)
			ft_error("oh shit!", ERR_CLOSE);
		dup2(pipes->pipe[WRITE], STDOUT_FILENO);
		if (close(pipes->pipe[WRITE]) < 0)
			ft_error("oh shit!", ERR_CLOSE);
	}
	else if (mode == MIDDLE)
	{
		if (close(pipes->pipe[READ]) < 0)
			ft_error("oh shit!", ERR_CLOSE);
		dup2(pipes->last_pipe, STDIN_FILENO);
		if (close(pipes->last_pipe) < 0)
			ft_error("oh shit!", ERR_CLOSE);
		dup2(pipes->pipe[WRITE], STDOUT_FILENO);
		if (close(pipes->pipe[WRITE]) < 0)
			ft_error("oh shit!", ERR_CLOSE);
	}
	else if (mode == END)
	{
		dup2(pipes->last_pipe, STDIN_FILENO);
		if (close(pipes->last_pipe) < 0)
			ft_error("oh shit!", ERR_CLOSE);
	}
}
