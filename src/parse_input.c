/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:48:13 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/10 12:43:54 by timschmi         ###   ########.fr       */
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
	char *operators[1][5] = {"|", "<", ">", "<<", ">>"};  // have an array of viable operators maybe already ordered in priority
	int i;
	int j;

	i = 0;
	j = 0;
	if (arg[0] == '$') //env variable
		return (0); //return for now env variables will be handled in the execution
	if (ft_strlen(arg) > 2) // no operators that a larger than 2 chars 
		return (0);

	while (i < 5)
	{
		if (!ft_strncmp(arg, operators[0][i], ft_strlen(arg)))
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
		if (check_operators(arg[i]))	// if no operator found it has to be a single command 
			append_node(&cmd, arg, i);	// maybe iterate trough it muliple times changing operator based on priority
			
		i++;
	}
	print_list(cmd);
}
