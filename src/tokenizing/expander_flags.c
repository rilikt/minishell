/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:10:19 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/16 16:34:29 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	print_int_arr(int *arr, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		printf("%d ", arr[i]);
		i++;
	}
	printf("\n");
}

int	check_end(char c)
{
	char	*set;
	int		i;

	set = "$\"'/\\|. ?";
	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (0);
		i++;
	}
	return (1);
}

void	var_lists(t_shell *shell)
{
	char_var_list(shell);
	int_var_list(shell);
}

char	*cvl_if_quotes(char *vars, t_shell *shell, int *i)
{
	int		start;
	char	*flag;

	start = 0;
	flag = "1";
	if (shell->input[*i] == 39 || shell->input[*i] == 34)
	{
		start = *i;
		if (shell->input[*i] == 39)
			flag = "0";
		else
			flag = "2";
		*i += 1;
		while (shell->input[*i] && (shell->input[*i] != shell->input[start]))
		{
			if (shell->input[*i] == '$')
				vars = ms_freejoin(vars, flag);
			*i += 1;
		}
	}
	else
		return (vars);
	return (vars);
}

void	char_var_list(t_shell *shell)
{
	char	*vars;
	int		i;

	vars = NULL;
	i = 0;
	while (shell->input[i])
	{
		vars = cvl_if_quotes(vars, shell, &i);
		if (shell->input[i] == '$')
		{
			if ((shell->input[i + 1] == 39 || shell->input[i + 1] == 34))
				vars = ms_freejoin(vars, "3");
			else
				vars = ms_freejoin(vars, "1");
		}
		if (shell->input[i])
			i++;
	}
	shell->char_vars = vars;
}
