/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:42:47 by pstrohal          #+#    #+#             */
/*   Updated: 2024/07/23 16:47:34 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

char **append_env(char *var, char **envp)
{
	int len = 0;
	char **re;

	while (envp[len])
		len++;
	re = (char **)malloc((len + 2) * sizeof(char *));
	len  = 0;
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

int var_len(char *str)
{
	char	*var_name_end;

	var_name_end = ft_strchr(str, '=');
	if (!var_name_end)
		return(0);

	return (var_name_end - str);
}

void add_qoutes(char **envp)
{
	int i = 0;
	int j;
	int len;

	while (envp[i])
	{
		j = 0;
		len = var_len(envp[i]);
		printf("declare -x ");
		while(j <= len)
		{
			printf("%c", envp[i][j]);
			j++;
		}
		printf("\"%s\"\n", envp[i]+len+1);
		i++;
	}
}


void export_print(char **envp)
{
	char *temp;
	int i = 0;
	int j;
	int len = 0;
	char **local_envp;
	int len_var;
	int len_var2;
	
	while(envp[len])
		len++;

	local_envp = (char **)malloc(len+1 * sizeof(char *));
	len=0;
	while(envp[len])
	{
		local_envp[len] = envp[len];
		len++;
	}
	local_envp[len] = NULL;
	while (i < len -1)
	{
		j = 0;
		while (j < len - i -1)
		{	
			if((len_var = var_len(local_envp[j])) > (len_var2 = var_len(local_envp[j+1])))
				len_var = len_var2;
			if (ft_strncmp(local_envp[j], local_envp[j+1], len_var+1) > 0)
			{
				temp = local_envp[j];
				local_envp[j] = local_envp[j+1];
				local_envp[j+1] = temp;
			}
			j++;
		}
		i++;
	}
	add_qoutes(local_envp);
	// print_arr(envp);
}

void	export(char **args, char ***envp) //maybe rework qoutes for this
{
	int		i;
	int		j;
	int		set;
	int		len;
	char	*var_name;
	char	*var_value;

	i = 0;
	j = 1;
	if (!(*envp))
		ft_error("envp error", ERR_EXPORT);
	if (!args[1])
	{
		export_print(*envp);
		return;
	}
	
	while(args[j])
	{
		if (ft_isdigit(args[j][0]))
			ft_error("starting with digit", ERR_EXPORT);
		j++;
	}
	j = 1;
	while(args[j])
	{
		len = var_len(args[j]);
		i = 0;
		set = 0;
		while ((*envp)[i] && len != 0 && set != 1)
		{
			if (!ft_strncmp((*envp)[i], args[j], len+1))
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
