/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:42:29 by pstrohal          #+#    #+#             */
/*   Updated: 2024/07/16 11:42:59 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	close_accordingly(t_pipe *pipes, int *mode)
{
	if (*mode == START)
	{
		ft_close(pipes->pipe[WRITE]);
		pipes->last_pipe = pipes->pipe[READ];
		*mode = MIDDLE;
	}
	if (*mode == MIDDLE)
	{
		ft_close(pipes->last_pipe);
		ft_close(pipes->pipe[WRITE]);

		pipes->last_pipe = pipes->pipe[READ];
	}
	if (*mode == END)
	{
		ft_close(pipes->last_pipe);
	}
	return ;
}
int	*allocate_pid(int nb)
{
	int *pid;

	pid = (int *)malloc(sizeof(int) * nb);
	if (!pid)
		ft_error("malloc pid_arr", ERR_MALLOC);
	return (pid);
}

void ft_close(int fd)
{
	if (close(fd) < 0)
		ft_error("oh shit close failed!", ERR_CLOSE);
}
void ft_dup2(int new, int old)
{
	if (dup2(new, old) < 0)
		ft_error("oh shit, dup2 failed!", ERR_DUP2);
}

void	change_std_fd(t_pipe *pipes, int mode)
{
	if (mode == START)
	{
		ft_close(pipes->pipe[READ]);
		ft_dup2(pipes->pipe[WRITE], STDOUT_FILENO);
		ft_close(pipes->pipe[WRITE]);
	}
	else if (mode == MIDDLE)
	{
		ft_close(pipes->pipe[READ]);
		ft_dup2(pipes->last_pipe, STDIN_FILENO);
		ft_close(pipes->last_pipe);
		ft_dup2(pipes->pipe[WRITE], STDOUT_FILENO);
		ft_close(pipes->pipe[WRITE]);

	}
	else if (mode == END)
	{
		dup2(pipes->last_pipe, STDIN_FILENO);
		ft_close(pipes->last_pipe);
	}
}
