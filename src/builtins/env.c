/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:31:40 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/07 12:55:53 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int env(char **arg, char **envp) // prints out env from extern char **environ we might have to create our own env don't know
{
	int i;
	int len;

	i = 0;
	if (arg[1])
	{
		write(2, "minishell: env: too many arguments!\n", 37);
		return (1);
	}
	while(envp[i])
	{
		if (var_len(envp[i], NULL))
			printf("%s\n", envp[i]);
		i++;
	}
	return (0);
}

char **copy_env(char **envp)
{
	int len = 0;
	char **re;

	while(envp[len])
		len++;
	re = (char **)malloc((len + 1) * sizeof(char *));
	error_check(re, "mlloc in copy_env", ERR_MALLOC);
	len = 0;
	while (envp && envp[len])
	{
		if (!ft_strncmp("OLDPWD", envp[len], 6))
			re[len] = ft_strdup("OLDPWD");
		else
			re[len] = ft_strdup(envp[len]);
		// printf("%s\n", envp[len]);
		len++;
	}
	re[len] = NULL;
	return(re);
}
