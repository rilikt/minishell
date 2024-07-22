/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 17:10:53 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/22 17:26:17 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"


int compare_to_envp(char **args, char *envp)
{
	int i = 1;
	while(args[i])
	{
		if (!ft_strncmp(args[i], envp, ft_strlen(args[i]+1)))
			return(0);
		i++;
	}
	return(1);
}

void unset(char **args, char ***envp) //needs to accept multiple argumens
{
	int len = 0;
	int i = 1;
	char **re;

	if (!args[1])
		return;
	while((*envp)[len])
		len++;
	while (args[i])
		i++;
	re = (char **)malloc((len + i) * sizeof(char *));
	len = 0;
	i=0;
	while((*envp)[len])
	{
		if (compare_to_envp(args, (*envp)[len]))
		{
			re[i] = (*envp)[len];
			i++;
		}
		len++;
	}
	re[i]=NULL;
	*envp=re;
}
