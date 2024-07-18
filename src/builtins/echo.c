/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:39:56 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/17 12:45:27 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void ft_echo(char **args)
{
	int i = 1;
	int n = 1;

	if (!ft_strncmp(args[i], "-n", 3))
	{
		n = 0;
		i++;
	}
	while(args[i])
	{
		printf("%s", args[i]); // use printf or write?
		i++;
	}
	if (n)
		printf("\n");
}