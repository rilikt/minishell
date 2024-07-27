/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:09:50 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/27 16:06:43 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

char	*rm_qoutes(char *str)
{
	int		i;
	int		len;
	char	*re;

	i = 0;
	if (str[i] != 34 && str[i] != 39)
		return (str);
	len = ft_strlen(str) - 2;
	re = (char *)malloc(len);
	re[len] = '\0';
	while (i < len)
	{
		re[i] = str[i + 1];
		i++;
	}
	free(str);
	return (re);
}

int	in_qoutes(char *str, int *input_i)
{
	int	i;
	int	start;

	i = *input_i;
	start = i;
	if (str[i] != 34 && str[i] != 39)
		return (0);
	i++;
	while (str[i] && (str[i] != str[start]))
		i++;
	if (str[i] != str[start])
		ft_error("qoutes not closed", ERR_SYNTAX);
	*input_i = i + 1;
	return (in_qoutes(str, input_i));
}

int is_closed(char *str, int i, int q_count, int start)
{
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			start = i;
			i++;
			while(str[i])
			{
				if (str[i] == str[start])
				{
					q_count += 2;
					break;
				}
				i++;
			}
			if (str[i] != str[start])
				ft_error("qoutes not closed", ERR_SYNTAX);
		}
		if (str[i])
			i++;
	}
	return(q_count);
}

char *create_string(char *str, char *re, int i, int k, int start)
{
	while (str[i])
	{
		if (str[i] != 34 && str[i] != 39)
		{
			re[k] = str[i];
			k++;
		}
		else
		{
			start = i;
			i++;
			while(str[i] && str[i] != str[start])
			{
				re[k] = str[i];
				k++;
				i++;
			}
		}
		if (str[i])
			i++;
	}
	re[k] = '\0';
	return (re);
}

char *check_qoutes(char *str, int *q_flag)
{
	int q_count;
	char *re;

	q_count = is_closed(str, 0, 0, 0);
	if (!q_count)
		return(str);

	re = (char *)malloc(ft_strlen(str) + 1 - q_count);
	if (!re)
		ft_error("allocation failed", ERR_MALLOC);
	*q_flag = 1;
	return(create_string(str, re, 0, 0, 0));
}
