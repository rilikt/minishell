/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:10:19 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/04 15:10:00 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void print_int_arr(int *arr, int len)
{
	int i = 0;
	while(i < len)
	{
		printf("%d ", arr[i]);
		i++;
	}
	printf("\n");
}

int check_end(char c)
{
	char *set = "$\"'/\\| ";
	int i;

	i = 0;
	while(set[i])
	{
		if (c == set[i])
			return (0);
		i++;
	}
	return(1);
}

void int_var_list(t_shell *shell)
{
	int	*arr;
	int i;
	int j;
	int count;

	i = 0;
	j = 0;
	arr = (int *)malloc(ft_strlen(shell->char_vars) * sizeof(int));
	error_check(arr, "int_var_list", ERR_MALLOC);
	while(shell->input[j])
	{
		if (shell->input[j] == '$')
		{
			count = 0;
			j++;
			if (ft_isdigit(shell->input[j]))
				count = 1;
			else if (shell->char_vars[i] == '1' || shell->char_vars[i] == '2')
			{
				while (shell->input[j] && check_end(shell->input[j]))
				{
					count++;
					j++;
				}
			}
			arr[i] = count;
			i++;
		}
		if (shell->input[j] && shell->input[j] != '$')
			j++;
	}
	shell->int_vars = arr;
}


void var_lists(t_shell *shell)
{
	char_var_list(shell);
	int_var_list(shell);
	// printf("%s\n", shell->char_vars);
	// print_int_arr(shell->int_vars, ft_strlen(shell->char_vars));
}

void	char_var_list(t_shell *shell)
{
	char	*vars;
	int		i;
	int		start;
	char	*flag;

	vars = NULL;
	i = 0;
	while (shell->input[i])
	{
		if (shell->input[i] == 39 || shell->input[i] == 34)
		{
			start = i;
			if (shell->input[i] == 39)
				flag = "0";
			else
				flag = "2";
			i++;
			while (shell->input[i] && (shell->input[i] != shell->input[start]))
			{
				if (shell->input[i] == '$') // myb check for whitespace after and set flag accordingly
					vars = ft_strjoin(vars, flag);
				i++;
			}
		}
		if (shell->input[i] == '$')
		{
			if ((shell->input[i+1] == 39 || shell->input[i+1] == 34))
				vars = ft_strjoin(vars, "3");
			else
				vars = ft_strjoin(vars, "1");
		}
		
		i++;
	}
	shell->char_vars = vars;
}