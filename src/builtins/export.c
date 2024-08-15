/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:42:47 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/15 17:28:32 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

char	**append_env(char *var, char **envp)
{
	int		len;
	char	**re;

	len = 0;
	while (envp[len])
	{
		if (!ft_strncmp(envp[len], var, var_len(envp[len], var) + 1))
			return (envp);
		len++;
	}
	re = (char **)malloc((len + 2) * sizeof(char *));
	error_check(re, "append_env", ERR_MALLOC);
	len = 0;
	while (envp[len])
	{
		re[len] = ms_strdup(envp[len]);
		len++;
	}
	re[len] = ms_strdup(var);
	re[len + 1] = NULL;
	free_string_array(envp);
	return (re);
}

int	var_len(char *str, char *str2)
{
	char	*var_name_end;
	int		len1;
	int		len2;

	if (!str2)
	{
		var_name_end = ft_strchr(str, '=');
		if (!var_name_end)
			return (0);
		return (var_name_end - str);
	}
	else
	{
		len1 = var_len(str, NULL);
		if (!len1)
			len1 = ft_strlen(str);
		len2 = var_len(str2, NULL);
		if (!len2)
			len2 = ft_strlen(str2);
		if (len1 < len2)
			len1 = len2;
		return (len1);
	}
}

int	export_loop(char ***envp, char *arg, int len)
{
	int	i;

	i = 0;
	if (len == 0)
		return (0);
	while ((*envp)[i] && len != 0)
	{
		len = var_len(arg, (*envp)[i]);
		if (!ft_strncmp((*envp)[i], arg, len))
		{
			free((*envp)[i]);
			(*envp)[i] = ms_strdup(arg);
			return (1);
		}
		i++;
	}
	return (0);
}

int	export(char **args, char ***envp)
{
	int	j;
	int	set;
	int	len;

	j = 1;
	if (!args[1])
		return (export_print(*envp), 0);
	if (check_input(args, envp, 1) == -1)
		return (1);
	while (args[j])
	{
		if (export_append(args, envp, &j))
			break ;
		len = var_len(args[j], NULL);
		set = export_loop(envp, args[j], len);
		if (set != 1)
			(*envp) = append_env(args[j], *envp);
		j++;
	}
	return (0);
}
