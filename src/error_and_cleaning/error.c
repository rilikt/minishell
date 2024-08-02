/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 15:54:29 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/02 12:36:04 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	ft_error(char *arg, char *msg, int errorcode)
{
	if (msg)
	{	write(STDERR_FILENO, "minishell: ", 12);
		if (arg)
		{
			write(STDERR_FILENO, arg, ft_strlen(arg));
			write(STDERR_FILENO, " ", 1);
		}
		write(STDERR_FILENO, msg, ft_strlen(msg) + 1);
		write(STDERR_FILENO, "\n", 1);
	}	
	exit (errorcode);
}

// ft_non_fatal_error();

void	error_check(void *ptr, char *msg, int error_code)
{
	char	*err_msg;

	if (!ptr)
	{
		// printf("------------error input----------\n");
		// printf("%s\nerror code: %d\n\n-------------\n", msg, error_code);
		if (error_code == 127)
			err_msg = "command not found";
		else if (errno != 0)
		{
			error_code = errno;
			err_msg = strerror(errno);
		}
		else
			err_msg = strerror(error_code);
		write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
		if (msg)
		{
			write(STDERR_FILENO, msg, ft_strlen(msg));
			write(STDERR_FILENO, ": ", 2);
		}
			
		if (err_msg)
			{
				write(STDERR_FILENO, err_msg, ft_strlen(err_msg));
				write(STDERR_FILENO, "\n", 1);
			}
		exit(error_code);
	}
	return ;
}
