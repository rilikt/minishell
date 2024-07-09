/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:48:13 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/09 17:01:29 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

char **tokenize(char *str)
{
	char **re = NULL;

	re = ft_split(str, ' ');  // ft_split should split by all whitespace chars
	free (str);
	
	return (re);
}

int check_operators(char *arg)
{
	char operators[] = "|";  // have an array of viable operators maybe already ordered in priority
	int i;

	i = 0;
	while (operators[i])
	{
		if (arg[0] == operators[i]) // have a compare that iterates through the entire string
			return (1);
		i++;
	}
	return (0);
}

void parse_input(char **arg)
{
	t_cmd *cmd = NULL;
	int i = 0;
	int j = 0;

	while(arg[i])
	{
		if (check_operators(arg[i])) // if no operator found should handle storing the command differently
			append_node(cmd, arg, i);
		i++;
	}
}
