/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:37:42 by pstrohal          #+#    #+#             */
/*   Updated: 2024/07/15 17:00:56 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	change_std_fd(t_pipe *pipes, int mode)
{
	int	pid = getpid();
	if (mode == START)
	{
		if (dup2(pipes->out[WRITE], STDOUT_FILENO) < 0)
			ft_error("dup2 failed\n", ERR_DUP2);
		if (close(pipes->out[WRITE]) < 0)
			printf("%dclosing %d failed!!!\n", pid, pipes->out[WRITE]);
		if (close(pipes->out[READ]) < 0)
			printf("%dclosing %d failed!!!\n", pid, pipes->out[READ]);
	}
	else if (mode == MIDDLE)
	{

		if (dup2( pipes->in[READ], STDIN_FILENO) < 0)
			ft_error("dup2 failed\n", ERR_DUP2);

		if (dup2(pipes->out[WRITE], STDOUT_FILENO) < 0)
			ft_error("dup2 failed\n", ERR_DUP2);
		
		if (close(pipes->in[READ]) < 0)
			printf("%dclosing %d failed!!!\n", pid, pipes->in[READ]);
			
		if (close(pipes->out[WRITE]) < 0)
			printf("%dclosing %d failed!!!\n", pid, pipes->out[WRITE]);
			
		if (close(pipes->in[WRITE]) < 0)
			printf("%dclosing %d failed!!!\n", pid, pipes->in[WRITE]);

		if (close(pipes->out[READ]) < 0)
			printf("%dclosing %d failed!!!\n", pid, pipes->out[READ]);
	}
	else if (mode == END)
	{		
		if (dup2(pipes->in[READ], STDIN_FILENO) < 0)
			ft_error("dup2 failed\n", ERR_DUP2);
		
		if (close(pipes->in[READ]) < 0)
			printf("%dclosing %d failed!!!\n", pid, pipes->in[READ]);
	}
}

void	run_childprocess(t_cmd *cmd, t_pipe *pipes, char **envp, int mode)
{
	change_std_fd(pipes, mode);
	cmd = NULL;
	envp = NULL;
	char buffer[200];
	int	i = 0;
	int	bts_read = 0;
	if (mode == START)
	{
		int fd = open("hallo.txt", O_RDONLY);
		bts_read = read(fd, &buffer[i], 1);
		i++;
		while (bts_read > 0)
			bts_read = read(fd, &buffer[i++], 1);
		close(fd);
	}
	if (mode != START)
		while (bts_read > 0)
			bts_read = read(STDIN_FILENO, &buffer[i++], 1);
	fprintf(stderr,"here is %d buffer contains:%s\n", getpid(), buffer);
	printf("%s", buffer);
	if (mode == START)
		close(STDOUT_FILENO);
	else if (mode == MIDDLE)
	{	close(STDOUT_FILENO);
		close(STDIN_FILENO);
	}
	else if (mode == END)
		close(STDIN_FILENO);
	exit(0);
}
