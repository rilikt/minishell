/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_flags_int.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:08:53 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/17 15:27:16 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	ivl_loop(int *arr, t_shell *shell, int *i, int *j)
{
	int	count;

	if (shell->input[*j] == '$')
	{
		count = 0;
		*j += 1;
		if (ft_isdigit(shell->input[*j]) || shell->input[*j] == '?')
			count = 1;
		else if (shell->char_vars[*i] == '1' || shell->char_vars[*i] == '2')
		{
			while (shell->input[*j] && (ft_isalnum(shell->input[*j])
					|| shell->input[*j] == '_'))
			{
				count++;
				*j += 1;
			}
		}
		arr[*i] = count;
		*i += 1;
	}
}

void	int_var_list(t_shell *shell)
{
	int	*arr;
	int	i;
	int	j;

	i = 0;
	j = 0;
	arr = (int *)malloc(ft_strlen(shell->char_vars) * sizeof(int));
	error_check(arr, "int_var_list", ERR_MALLOC);
	while (shell->input[j])
	{
		ivl_loop(arr, shell, &i, &j);
		if (shell->input[j] && shell->input[j] != '$')
			j++;
	}
	shell->int_vars = arr;
}
