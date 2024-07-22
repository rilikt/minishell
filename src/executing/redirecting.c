/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:06:18 by pstrohal          #+#    #+#             */
/*   Updated: 2024/07/22 12:32:31 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	change_input_fd(t_rdct *reds)
{
	reds->in_fd = open(reds->filename, O_RDONLY);
	if (reds->in_fd < 0)
		ft_error("couldnt open file\n", ERR_OPEN);
	ft_dup2(reds->in_fd, STDIN_FILENO);
	ft_close(reds->in_fd);
	return ;
}

void	change_output_fd(t_rdct *reds, int mode)
{
	reds->out_fd = open(reds->filename, O_WRONLY | mode);
	if (reds->out_fd < 0)
		ft_error(strerror(errno), ERR_OPEN);
	ft_dup2(reds->out_fd, STDOUT_FILENO);
	ft_close(reds->out_fd);
	return ;
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
			;
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
