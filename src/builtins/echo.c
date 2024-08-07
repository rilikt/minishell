/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:39:56 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/07 12:55:28 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	echo(char **args)
{
	int i = 1;
	int n = 1;
	int	j = 2;

	if (!args[1])
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	while(args[i] && !ft_strncmp(args[i], "-n", 2))
	{
		j = 2;
		while (args[i][j] == 'n')// || args[i][j] == ' ')
			j++;
		if  (args[i][j])
			break ;
		n = 0;
		i++;
	}
	while(args[i])
	{
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (n)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
