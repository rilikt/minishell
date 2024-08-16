/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:04:03 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/16 16:22:50 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

char	*rm_plus(char *str)
{
	int		i;
	int		j;
	char	*re;
	int		flag;

	i = 0;
	j = 0;
	flag = 1;
	re = (char *)malloc(ft_strlen(str));
	while (str[i])
	{
		if (flag && str[i] == '+')
		{
			i++;
			flag = 0;
		}
		re[j] = str[i];
		i++;
		j++;
	}
	re[j] = '\0';
	return (re);
}

int	ex_append_loop(char ***envp, char *arg, int len)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (len == 0)
		return (0);
	while ((*envp)[i] && len != 0)
	{
		len = var_len(arg, (*envp)[i]);
		if (!ft_strncmp((*envp)[i], arg, len))
		{
			if (ft_strchr((*envp)[i], '='))
				tmp = ms_strjoin((*envp)[i], ft_strchr(arg, '=') + 1);
			else
				tmp = ms_strjoin((*envp)[i], ft_strchr(arg, '='));
			free((*envp)[i]);
			(*envp)[i] = tmp;
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_plus(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '+')
			return (1);
		i++;
	}
	return (0);
}

int	export_append(char **args, char ***envp, int *j)
{
	char	*str;
	int		len;
	int		set;

	set = 0;
	if (!check_plus(args[*j]))
		return (0);
	str = rm_plus(args[*j]);
	len = var_len(str, NULL);
	set = ex_append_loop(envp, str, len);
	if (set != 1)
		(*envp) = append_env(str, *envp);
	*j += 1;
	free(str);
	if (!args[*j])
		return (1);
	return (0);
}
