/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:39:56 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/02 19:26:52 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	echo(char **args)
{
	int i = 1;
	int n = 1;

	if (!args[1])
		return ;
	if (!ft_strncmp(args[i], "-n", 3))
	{
		n = 0;
		i++;
	}
	while(args[i])
	{
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		if (args[i + 1])
			write(STDIN_FILENO, " ", 1);
		i++;
	}
	if (n)
		write(STDOUT_FILENO, "\n", 1);
	return ;
}
