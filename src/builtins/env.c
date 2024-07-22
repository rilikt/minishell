/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:31:40 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/22 16:15:27 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void env(char **arg, char **envp) // prints out env from extern char **environ we might have to create our own env don't know
{
	if (arg[1])
	{
		write(2, "env : too many arguments\n", 25);
		return;
	}
	print_arr(envp);

	return ;
}


char **copy_env(char **envp)
{
	int len = 0;
	char **re;

	while(envp[len])
		len++;
	re = (char **)malloc((len + 1) * sizeof(char *));
	len = 0;
	while (envp[len])
	{
		re[len] = ft_strdup(envp[len]);
		len++;
	}
	re[len] = NULL;
	return(re);
}