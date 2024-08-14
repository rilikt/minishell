/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:24:19 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/14 18:24:23 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

char	*ft_getenv(char *find, char **env) // check for empty env
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