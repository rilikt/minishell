/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:37:42 by pstrohal          #+#    #+#             */
/*   Updated: 2024/07/13 19:05:55 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	change_std_fd(int *pipes, int mode)
{
	if (mode == START)
	{
		if (dup2(STDOUT_FILENO, pipes[OUT_WRITE]) < 0)
			ft_error("dup2 failed\n", ERR_DUP2);
		close(pipes[OUT_READ]);
	}
	else if (mode == MIDDLE)
	{
		if (dup2(STDIN_FILENO, pipes[IN_READ]) < 0)
			ft_error("dup2 failed\n", ERR_DUP2);
		if (dup2(STDOUT_FILENO, pipes[OUT_WRITE]) < 0)
			ft_error("dup2 failed\n", ERR_DUP2);
		close(pipes[IN_WRITE]);
		close(pipes[OUT_READ]);
	}
	
}

void	run_childprocess(t_cmd *cmd, int *pipes, char **envp, int mode)
{
	change_std_fd(pipes, mode);
}
