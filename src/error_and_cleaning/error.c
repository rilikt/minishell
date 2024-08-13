/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 15:54:29 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/13 18:58:52 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	ft_error(char *arg, char *msg, int error_code)
{
	char	*err_msg;

	err_msg = NULL;
	if (error_code == 127)
		err_msg = "command not found";
	else if (errno != 0)
		err_msg = strerror(errno);
	else
		err_msg = strerror(error_code);
	write(STDERR_FILENO, "minishell: ", 12);
	if (arg)
		write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, msg, ft_strlen(msg) + 1);
	write(STDERR_FILENO, ": ", 2);
	if (err_msg)
	{
		write(STDERR_FILENO, err_msg,
			ft_strlen(err_msg));
	}
	write(STDERR_FILENO, "\n", 1);
	return ;
}

void	ft_sytax_error(int *err, t_token *tkn)
{
	*err = ERR_SYNTAX;
	write(STDERR_FILENO, "minishell: syntax error near unexpected token ", 47);
	if (!tkn)
		write(STDERR_FILENO, "'newline'", 10);
	else
		write(STDERR_FILENO, tkn->str, ft_strlen(tkn->str));
	write(STDERR_FILENO, "\n", 1);
	return ;
}

void quotes_err(int *err)
{
	write(2, "syntax error: unclosed quotes\n", 31);
	*err = ERR_SYNTAX;
}

void	error_check(void *ptr, const char *msg, int error_code)
{
	char	*err_msg;

	if (!ptr)
	{
		if (error_code == 127)
			err_msg = "command not found";
		else if (errno != 0)
			err_msg = strerror(errno);
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
