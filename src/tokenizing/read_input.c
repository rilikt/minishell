/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:39:58 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/01 12:03:27 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

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

char	*read_input(int mode)
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
	if (mode == INTERACTIVE)
		input = readline(rl_str);
	else
	{
		input = get_next_line(fileno(stdin));
		// input = ft_strtrim(tmp, "\n");
		// free(tmp);
	}
	if (!input)
	{
		exit(0);
	}
	if (check_whitespace(input))
	{
		free(input);
		input = read_input(mode);
	}
	free(rl_str);
	add_history(input);
	return (input);
}
