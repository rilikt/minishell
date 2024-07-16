/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:54:15 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/16 11:43:23 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void execute_commandline(t_shell *shell)
{
	int		i;
	int		*pid;
	t_pipe	pipes;
	int		mode;
	
	pid = allocate_pid(shell->cmd_nb - 1);
	mode = START;
	i = -1;
	while (++i < shell->cmd_nb)
	{
		if (i == shell ->cmd_nb - 1)
			mode = END;
		if (mode != END && pipe(pipes.pipe) < 0)
			ft_error("pipe filed", ERR_PIPE);
		pid[i] = fork();
		if (pid[i] == 0)
			run_childprocess(&shell->commands, &pipes, shell->envp, mode);
		else if (pid[i] < 0)
			ft_error("fork failed", ERR_FORK);
		if (shell->commands->next)
			
		close_accordingly(&pipes, &mode);
	}
	shell->exitstatus = wait_for_children(pid, shell->cmd_nb);
	return ;
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
