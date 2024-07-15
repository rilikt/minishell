/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:37:42 by pstrohal          #+#    #+#             */
/*   Updated: 2024/07/15 18:40:55 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	change_std_fd(t_pipe *pipes, int mode)
{
	if (mode == START)
	{
		close(pipes->pipe[READ]);
		dup2(pipes->pipe[WRITE], STDOUT_FILENO);
		close(pipes->pipe[WRITE]);
	}
	else if (mode == MIDDLE)
	{
		close(pipes->pipe[READ]);
		dup2(pipes->last_pipe, STDIN_FILENO);
		close(pipes->last_pipe);
		dup2(pipes->pipe[WRITE], STDOUT_FILENO);
		close(pipes->pipe[WRITE]);	
	}
	else if (mode == END)
	{
		dup2(pipes->last_pipe, STDIN_FILENO);
		close(pipes->last_pipe);
	}
}

void	run_childprocess(t_cmd *cmd, t_pipe *pipes, char **envp, int mode)
{
	change_std_fd(pipes, mode);
	cmd = NULL;
	envp = NULL;
	char buffer[200];
	int	bts_read = 0;
	if (mode == START)
	{
		int fd = open("hallo.txt", O_RDONLY);
		bts_read = read(fd, &buffer, 199);
		buffer[bts_read] = '\0';
		close(fd);
	}
	if (mode != START)
	{
		bts_read = read(STDIN_FILENO, &buffer, 199);
		buffer[199] = '\0';
	}
	// fprintf(stderr,"here is %d buffer contains:%s\n", getpid(), buffer);
	printf("%s", buffer);
	fflush(stdout);
	// write(STDOUT_FILENO, &buffer, bts_read);
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
