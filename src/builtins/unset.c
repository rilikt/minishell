/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:10:53 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/14 18:19:13 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	unset(char **args, char ***envp)
{
	int		len;
	int		i;
	char	**re;

	len = 0;
	i = 1;
	if (!args[1])
		return (0);
	while ((*envp)[len])
		len++;
	i = check_input(args, envp, 2);
	if (i == -1)
		return (1);
	re = (char **)malloc((len + 1) * sizeof(char *));
	error_check(re, "unset", ERR_MALLOC);
	*envp = unset_loop(re, envp, args);
	return (0);
}

char	**unset_loop(char **re, char ***envp, char **args)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while ((*envp)[len])
	{
		if (compare_to_envp(args, (*envp)[len]))
		{
			re[i] = ms_strdup((*envp)[len]);
			i++;
		}
		len++;
	}
	re[i] = NULL;
	free_string_array(*envp);
	return (re);
}

int	compare_to_envp(char **args, char *envp)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!ft_strncmp(args[i], envp, var_len(args[i], envp)))
			return (0);
		i++;
	}
	return (1);
}
