/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:08:42 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/07 18:46:57 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void exit_msg(char *str)
{
	write(2, "minishell: exit: ", 18);
	write(2, str, ft_strlen(str));
	write(2, ": numeric argument required\n", 28);
}


int num_check(char *str)
{
	int i;

	i = 1;
	if (ft_isalpha(str[0]))
		return(1);
	if (str[0] == '-' && !ft_isdigit(str[1]))
		return(1);
	else if (str[0] == '+' && !ft_isdigit(str[1]))
		return(1);
	while(str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}


int	ft_exit(char **args, int *err, int exitstatus)
{
	int re;
	int i;

	i = 0;
	if (!args[1])
		return(*err = 1, exitstatus);
	if (args[1][0] == '\0' || num_check(args[1]))
		return (*err = 1, exit_msg(args[1]), 255);
	if (args[2])
	{
		write (2, "minishell: exit: too many arguments\n", 37);
		return (1);
	}
	while(args[1][i])
	{
		if (ft_isalpha(args[1][i]))
			return (*err = 1, exit_msg(args[1]), 255);
		i++;
	}
	re = ft_atoi(args[1]);
	if (re > 255)
		re = 255;
	
	return (*err = 1, re);
}