/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:32:16 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/14 12:55:12 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	update_env(char ***envp)
{
	char	*old[3];
	char	*new[3];
	char	path[1024];

	getcwd(path, sizeof(path));
	old[0] = "export";
	new[0] = "export";
	old[1] = ms_strjoin("OLDPWD=", ft_getenv("PWD", *envp));
	new[1] = ms_strjoin("PWD=", path);
	old[2] = NULL;
	new[2] = NULL;
	export(old, envp);
	export(new, envp);
	free(old[1]);
	free(new[1]);
}

int	get_home(char **arg, char **move_to, char **envp)
{
	if (arg[1])
		return (0);
	*move_to = ft_getenv("HOME", envp);
	if (!(*move_to))
	{
		write(2, "minishell: cd: HOME not set\n", 29);
		return (1);
	}
	return (0);
}

int	cd(char **arg, char ***envp)
{
	char	*move_to;

	move_to = arg[1];
	if (get_home(arg, &move_to, *envp))
		return (1);
	if (arg[1] && !ft_strncmp(arg[1], "-", 2))
	{
		move_to = ft_getenv("OLDPWD", *envp);
		if (move_to)
			printf("%s\n", move_to);
		else
		{
			write(2, "minishell: cd: OLDPWD not set\n", 31);
			return (1);
		}
	}
	if (chdir(move_to) == -1)
	{
		ft_error("cd: ", move_to, ERR_FILE);
		return (1);
	}
	update_env(envp);
	return (0);
}

int	pwd(char **arg)
{
	char	path[1024];

	printf("%s\n", getcwd(path, sizeof(path)));
	arg = NULL;
	return (0);
}
