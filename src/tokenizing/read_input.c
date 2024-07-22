/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:39:58 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/22 19:01:24 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

// checks if the string only contains whitespace
int	check_whitespace(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != '\n')
	{
		if (input[i] > 32)
			return (0);
		i++;
	}
	return (1);
}

char	*read_input(void)
{
	char	*input;
	char	path[1024];
	char	*rl_str;
	char	*tmp;

	input = NULL;
	getcwd(path, sizeof(path));
	rl_str = ft_strjoin(path, " > ");
	tmp = ft_strdup((ft_strrchr(rl_str, '/') + 1));
	free(rl_str);
	rl_str = ft_strjoin("🐚 ", tmp);
	free(tmp);
	input = readline(rl_str);
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
	free (rl_str);
	add_history(input);
	return (input);
}
