/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 10:42:29 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/13 13:44:35 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	close_accordingly(t_pipe *pipes, int *mode)
{
	if (*mode == START)
	{
		ft_close(pipes->pipe[WRITE], "close_accordingly");
		pipes->last_pipe = pipes->pipe[READ];
		*mode = MIDDLE;
	}
	else if (*mode == MIDDLE)
	{
		ft_close(pipes->last_pipe, "close_accordingly");
		ft_close(pipes->pipe[WRITE], "close_accordingly");
		pipes->last_pipe = pipes->pipe[READ];
	}
	else if (*mode == END)
	{
		ft_close(pipes->last_pipe, "close_accordingly");
	}
	return ;
}

int	*allocate_pid(int nb)
{
	int	*pid;

	pid = (int *)malloc(sizeof(int) * nb);
	if (!pid)
		ft_error(NULL, "malloc pid_arr", ERR_MALLOC);
	return (pid);
}

void	ft_close(int fd, char *msg)
{
	if (fd >= 0)
	{
		if (close(fd) < 0)
			ft_error(NULL, msg, ERR_CLOSE);
	}
}

void	ft_dup2(int new, int old, char *msg)
{
	if (new >= 0)
	{
		if (dup2(new, old) < 0)
			ft_error(NULL, msg, ERR_DUP2);
	}
}

void	change_std_fd(t_pipe *pipes, int mode)
{
	if (mode == START)
	{
		ft_close(pipes->pipe[READ], "close in change_std_fd");
		ft_dup2(pipes->pipe[WRITE], STDOUT_FILENO, "dup2 in change_std_fd");
		ft_close(pipes->pipe[WRITE], "close in change_std_fd");
	}
	else if (mode == MIDDLE)
	{
		ft_close(pipes->pipe[READ], "close in change_std_fd");
		ft_dup2(pipes->last_pipe, STDIN_FILENO, "dup2 in change_std_fd");
		ft_close(pipes->last_pipe, "close in change_std_fd");
		ft_dup2(pipes->pipe[WRITE], STDOUT_FILENO, "dup2 in change_std_fd");
		ft_close(pipes->pipe[WRITE], "close in change_std_fd");
	}
	else if (mode == END)
	{
		ft_dup2(pipes->last_pipe, STDIN_FILENO, "dup2 in change_std_fd");
		ft_close(pipes->last_pipe, "close in change_std_fd");
	}
}
