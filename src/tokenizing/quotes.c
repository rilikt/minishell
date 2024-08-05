/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:09:50 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/05 13:02:46 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"


int	in_qoutes(char *str, int *input_i, t_shell *shell)
{
	int	i;
	int	start;
	int j;

	i = *input_i;
	start = i;
	if (is_whitespace(str[i]))
			return(1) ;
	if (str[i] != 34 && str[i] != 39)
		return (0);
	i++;
	while (str[i] && (str[i] != str[start]))
		i++;
	if (str[i] != str[start])
		shell->err = ERR_SYNTAX;
	*input_i = i + 1;
	j = i + 1;
	if (is_operator(str, &j))
		return(1);
	*input_i = i +1;
	return (in_qoutes(str, input_i, shell));
}

int is_closed(char *str, int q_count, int start, t_shell *shell)
{
	int	i;

	i = 0;
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
				shell->err = ERR_SYNTAX;
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

char *check_qoutes(char *str, int *q_flag, t_shell *shell)
{
	int q_count;
	char *re;

	q_count = is_closed(str, 0, 0, shell);
	if (!q_count)
		return(str);

	re = (char *)malloc(ft_strlen(str) + 1 - q_count);
	error_check(re, "check_quotes", ERR_MALLOC);
	*q_flag = 1;
	return(create_string(str, re, 0, 0, 0));
}
