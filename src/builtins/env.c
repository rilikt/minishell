/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:31:40 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/12 18:09:23 by timschmi         ###   ########.fr       */
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

void add_oldpwd(char ***envp)
{
	char *pwd[3];

	pwd[0] = "export";
	pwd[1] = "OLDPWD";
	pwd[2] = NULL;
	export(pwd, envp);
}

char **copy_env(char **envp)
{
	int len;
	char **re;
	int set;

	len = 0;
	set = 0;
	while(envp && envp[len])
		len++;
	re = (char **)malloc((len + 1) * sizeof(char *));
	error_check(re, "malloc in copy_env", ERR_MALLOC);
	len = 0;
	while (envp && envp[len])
	{
		if (!ft_strncmp("OLDPWD", envp[len], 6))
		{
			re[len] = ft_strdup("OLDPWD");
			set = 1;
		}
		else
			re[len] = ft_strdup(envp[len]);
		len++;
	}
	re[len] = NULL;
	if (!set)
		add_oldpwd(&re);
	return(re);
}
