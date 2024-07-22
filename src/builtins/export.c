/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:42:47 by pstrohal          #+#    #+#             */
/*   Updated: 2024/07/22 16:43:40 by timschmi         ###   ########.fr       */
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
	// if(envp)
	free(envp);
	return (re);
}

void	export(char *args, char ***envp) //maybe rework qoutes for this
{
	int		i;
	char	*var_name;
	char	*var_name_end;
	char	*var_value;

	i = 0;
	if (!(*envp))
		ft_error("envp error", ERR_EXPORT);
	if (!args)
		ft_error("no arguments", ERR_EXPORT);
	if (ft_isdigit(args[0]))
		ft_error("export error, empty value", ERR_EXPORT);
	var_name_end = ft_strchr(args, '=');
	if (!var_name_end)
		ft_error("export error, empty value", ERR_EXPORT);

	int len = var_name_end - args;
	
	while ((*envp)[i])
	{
		if (!ft_strncmp((*envp)[i], args, len))
		{
			(*envp)[i] = ft_strdup(args);
			return;
		}
		i++;
	}
	// return(append_env(args, *envp));
	*envp = append_env(args, *envp);
	// print_arr(*envp);
}
