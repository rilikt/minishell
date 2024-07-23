/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:42:47 by pstrohal          #+#    #+#             */
/*   Updated: 2024/07/23 17:47:24 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

char	**append_env(char *var, char **envp)
{
	int		len;
	char	**re;

	len = 0;
	while (envp[len])
		len++;
	re = (char **)malloc((len + 2) * sizeof(char *));
	len = 0;
	while (envp[len])
	{
		re[len] = envp[len];
		len++;
	}
	re[len] = var;
	len++;
	re[len] = NULL;
	free(envp);
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
		len2 = var_len(str2, NULL);
		if (len1 > len2)
			len1 = len2;
		return (len1);
	}
}

void	add_qoutes(char **envp)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (envp[i])
	{
		j = 0;
		len = var_len(envp[i], NULL);
		printf("declare -x ");
		while (j <= len)
		{
			printf("%c", envp[i][j]);
			j++;
		}
		printf("\"%s\"\n", envp[i] + len + 1);
		i++;
	}
	free(envp);
}

int	copy_envp(char ***local_envp, char **envp)
{
	int	len;

	len = 0;
	while (envp[len])
		len++;
	(*local_envp) = (char **)malloc(len + 1 * sizeof(char *));
	len = 0;
	while (envp[len])
	{
		(*local_envp)[len] = envp[len];
		len++;
	}
	(*local_envp)[len] = NULL;
	return (len);
}

void	export_print(char **envp)
{
	char	*temp;
	int		j;
	int		len;
	char	**local_envp;
	int		len_var;

	len = copy_envp(&local_envp, envp);
	while (len - 1)
	{
		j = 0;
		while (j < len - 1)
		{
			len_var = var_len(local_envp[j], local_envp[j + 1]);
			if (ft_strncmp(local_envp[j], local_envp[j + 1], len_var + 1) > 0)
			{
				temp = local_envp[j];
				local_envp[j] = local_envp[j + 1];
				local_envp[j + 1] = temp;
			}
			j++;
		}
		len--;
	}
	add_qoutes(local_envp);
}

int	check_and_print(char **args, char ***envp)
{
	int	j;

	j = 0;
	if (!(*envp))
		ft_error("envp error", ERR_EXPORT);
	if (!args[1])
	{
		export_print(*envp);
		return (0);
	}
	while (args[j])
	{
		if (ft_isdigit(args[j][0]))
			ft_error("starting with digit", ERR_EXPORT);
		j++;
	}
	return (1);
}

void	export(char **args, char ***envp) // maybe rework qoutes for this
{
	int i;
	int j;
	int set;
	int len;

	if (!(j = check_and_print(args, envp)))
		return ;
	while (args[j])
	{
		len = var_len(args[j], NULL);
		i = 0;
		set = 0;
		while ((*envp)[i] && len != 0 && set != 1)
		{
			if (!ft_strncmp((*envp)[i], args[j], len + 1))
			{
				(*envp)[i] = ft_strdup(args[j]);
				set = 1;
			}
			i++;
		}
		if (set != 1 && len != 0)
			*envp = append_env(args[j], *envp);
		j++;
	}
}
