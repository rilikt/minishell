/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:39:56 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/14 16:03:44 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	skip_options(char **args, int *i, int *j, int *n)
{
	while (args[*i] && !ft_strncmp(args[*i], "-n", 2))
	{
		*j = 2;
		while (args[*i][*j] == 'n')
			*j += 1;
		if (args[*i][*j])
			break ;
		*n = 0;
		*i += 1;
	}
}

int	echo(char **args)
{
	int	i;
	int	n;
	int	j;

	i = 1;
	n = 1;
	j = 2;
	if (!args[1])
	{
		write(STDOUT_FILENO, "\n", 1);
		return (0);
	}
	skip_options(args, &i, &j, &n);
	while (args[i])
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
