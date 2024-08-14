/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_vars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:33:18 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/14 18:06:51 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

char	*set_vars(char *str, char *vars)
{
	static int	i = 0;
	int			j;
	int			count;
	char		*re;

	j = 0;
	count = 0;
	if (!str)
		return (NULL);
	while (str[j])
	{
		if (str[j] == '$')
			count++;
		j++;
	}
	if (count == 0)
		return (NULL);
	re = ms_substr(vars, i, count);
	i += count;
	if (!vars[i])
		i = 0;
	return (re);
}

int	*set_int_vars(int *arr, char *str, char *vars)
{
	static int	i = 0;
	int			len;
	int			*re;
	int			j;

	j = 0;
	len = ft_strlen(str);
	re = (int *)malloc(len * sizeof(int));
	error_check(re, "set_int_vars", ERR_MALLOC);
	len += i;
	while (i < len)
	{
		re[j] = arr[i];
		j++;
		i++;
	}
	if (!vars[i])
		i = 0;
	return (re);
}

int	check_variable(char *str, int q_flag)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (!is_whitespace(str[i + 1]) && str[i + 1]))
			return (VARIABLE);
		i++;
	}
	if (q_flag)
	{
		return (IN_QUOTES);
	}
	return (WORD);
}
