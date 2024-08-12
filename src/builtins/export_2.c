/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 15:04:03 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/12 18:05:50 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

char	*ft_getenv(char *find, char **env)
{
	int	i;
	int	len_find;
	int	len_var;

	len_find = ft_strlen(find);
	i = 0;
	if (!find || !*find)
		return (NULL);
	while (env[i])
	{
		len_var = var_len(env[i], NULL);
		if ((len_var == len_find) && !ft_strncmp(find, env[i], len_find))
			// Is the first condition tested before the second? Otherwise myb segfault
			return (env[i] + len_var + 1);
		i++;
	}
	return (NULL);
}
