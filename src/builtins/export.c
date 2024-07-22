/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:42:47 by pstrohal          #+#    #+#             */
/*   Updated: 2024/07/22 11:53:52 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	export(char **args, char **envp)
{
	int		i;
	char	*var_name;
	char	*var_name_end;
	char	*var_value;

	i = 0;
	if (!args || !envp || !args[1])
		return (ERR_EXPORT);
	var_name_end = ft_strchr(args[1], '=');
	if (!var_name_end)
		return (ERR_EXPORT);
	var_name = 
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], args[]))
	}
}