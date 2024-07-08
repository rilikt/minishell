/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:39:58 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/08 12:09:23 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int check_whitespace(char *input) // checks if the string only contains whitespace
{
	int i;

	i = 0;

	while (input[i] && input[i] != '\n')
	{
		if (input[i] > 32) // ascii values below 32
			return (0);
		i++;
	}
	return (1);
}

char *read_input(void)
{
	char *input = NULL;
	char path[1024];
	char *rl_str;

	getcwd(path, sizeof(path));
	rl_str = ft_strjoin(path, " > ");
	input = readline(rl_str); // readline returns 0 on EOF
	if (!input)
	{
		free(input);
		exit(EXIT_FAILURE);
	}
	if (check_whitespace(input))
	{
		free(input);
		input = read_input();
	}
	
	add_history(input);
	
	return (input);
}
