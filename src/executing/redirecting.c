/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:06:18 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/14 16:45:11 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	change_input_fd(t_rdct *reds, int *err)
{
	if (access(reds->filename, F_OK))
	{
		ft_error(NULL, reds->filename, ERR_FILE);
		*err = ERR_EXIT;
	}
	else if (access(reds->filename, R_OK))
	{
		ft_error(NULL, reds->filename, ERR_PERMISSION);
		*err = ERR_EXIT;
	}
	else
	{
		reds->in_fd = open(reds->filename, O_RDONLY);
		if (reds->in_fd < 0)
		{
			ft_error(reds->filename, "couldnt open file\n", ERR_OPEN);
			*err = 1;
		}
		ft_dup2(reds->in_fd, STDIN_FILENO, "dup2 in change_input_fd");
		ft_close(reds->in_fd, "close in change_input_fd");
	}
	return ;
}

void	change_output_fd(t_rdct *reds, int mode, int *err)
{
	if (mode == O_CREAT)
		reds->out_fd = open(reds->filename, O_CREAT | O_WRONLY, 0666);
	else
		reds->out_fd = open(reds->filename, O_RDONLY);
	if (reds->out_fd < 0)
	{
		ft_error(NULL, reds->filename, ERR_OPEN);
		*err = ERR_EXIT;
	}
	ft_dup2(reds->out_fd, STDOUT_FILENO, "dup2 in change_output_fd");
	ft_close(reds->out_fd, "close in change_output_fd");
	return ;
}

void	pipe_heredoc(t_rdct *reds, int *err)
{
	int	fd[2];

	if (pipe(fd) < 0)
	{
		ft_error(NULL, "pipe in herdoc", ERR_DUP2);
		*err = ERR_EXIT;
	}
	if (write(fd[1], reds->filename, ft_strlen(reds->filename)) < 0)
		error_check(NULL, "write in heredoc", ERR_WRITE);
	ft_close(fd[1], "close in pipe_heredoc");
	ft_dup2(fd[0], STDIN_FILENO, "dup2 in pipe_heredoc");
	ft_close(fd[0], "close in pipe_heredoc");
}

void	redirect_accordingly(t_rdct *reds, int *err)
{
	if (!reds)
		return ;
	reds->in_fd = -1;
	reds->out_fd = -1;
	while (reds && !*err)
	{
		if (reds->type == IN_REDIRECT)
			change_input_fd(reds, err);
		else if (reds->type == IN_HEREDOC)
			pipe_heredoc(reds, err);
		else if (reds->type == OUT_REDIRECT && access(reds->filename, F_OK))
			change_output_fd(reds, O_CREAT, err);
		else if (reds->type == OUT_RED_APPEND && access(reds->filename, F_OK))
			change_output_fd(reds, O_CREAT, err);
		else if (reds->type == OUT_REDIRECT && !access(reds->filename, W_OK))
			change_output_fd(reds, O_TRUNC, err);
		else if (reds->type == OUT_RED_APPEND && !access(reds->filename, W_OK))
			change_output_fd(reds, O_APPEND, err);
		else
		{
			ft_error(NULL, reds->filename, ERR_PERMISSION);
			*err = ERR_EXIT;
		}
		reds = reds->next;
	}
}
