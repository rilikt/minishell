/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:06:18 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/05 17:09:42 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	change_input_fd(t_rdct *reds)
{
	reds->in_fd = open(reds->filename, O_RDONLY);
	if (reds->in_fd < 0)
		ft_error(reds->filename, "couldnt open file\n", ERR_EXIT);
	ft_dup2(reds->in_fd, STDIN_FILENO, "dup2 in change_input_fd");
	ft_close(reds->in_fd, "close in change_input_fd");
	return ;
}

void	change_output_fd(t_rdct *reds, int mode)
{
	reds->out_fd = open(reds->filename, O_WRONLY | mode);
	if (reds->out_fd < 0)
		ft_error(reds->filename, strerror(errno), ERR_EXIT);
	ft_dup2(reds->out_fd, STDOUT_FILENO, "dup2 in change_output_fd");
	ft_close(reds->out_fd, " close in change_output_fd");
	return ;
}

void	pipe_heredoc(t_rdct *reds)
{
	int	fd[2];

	if (pipe(fd) < 0)
		error_check(NULL, "dup2 in herdoc", ERR_DUP2);
	if (write(fd[1], reds->filename, ft_strlen(reds->filename) + 1) < 0)
		ft_error(NULL, "write in heredoc", ERR_WRITE);
	ft_close(fd[1], "close in pipe_heredoc");
	ft_dup2(fd[0], STDIN_FILENO, "dup2 in pipe_heredoc");
	ft_close(fd[0], "close in pipe_heredoc");
}

void	redirect_accordingly(t_rdct *reds)
{
	if (!reds)
		return ;
	reds->in_fd = -1;
	reds->out_fd = -1;
	if (!reds)
		return ;
	while (reds)
	{
		if (reds->type == IN_REDIRECT && !access(reds->filename, R_OK))
			change_input_fd(reds);
		else if (reds->type == IN_HEREDOC)
			pipe_heredoc(reds);
		else if (reds->type == OUT_REDIRECT && access(reds->filename, F_OK))
			change_output_fd(reds, O_CREAT);
		else if (reds->type == OUT_RED_APPEND && access(reds->filename, F_OK))
			change_output_fd(reds, O_CREAT);
		else if (reds->type == OUT_REDIRECT && !access(reds->filename, W_OK))
			change_output_fd(reds, O_TRUNC);
		else if (reds->type == OUT_RED_APPEND && !access(reds->filename, W_OK))
			change_output_fd(reds, O_APPEND);
		else
			error_check(NULL, NULL, 0);
		reds = reds->next;
	}
	return ;
}
// /bin/echo hi >./outfiles/outfile01 | /bin/echo bye
// >> "$H"OM"E"
// cat OME
// /bin/rm -f OME
