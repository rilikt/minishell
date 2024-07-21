/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 15:54:29 by pstrohal          #+#    #+#             */
/*   Updated: 2024/07/21 16:34:50 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	ft_error(char *msg, int errorcode)
{
	if (msg)
		write(STDERR_FILENO, msg, ft_strlen(msg) + 1);
	exit (errorcode);
}

// ft_non_fatal_error();

void	error_check(void *ptr, char *msg, int error_code)
{
	char	*err_msg;

	if (!ptr)
	{
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
