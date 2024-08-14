/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_flags.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:10:19 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/14 14:45:40 by timschmi         ###   ########.fr       */
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

	set = "$\"'/\\|. ";
	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (0);
		i++;
	}
	return (1);
}

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
			while (shell->input[*j] && check_end(shell->input[*j]))
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
	int	count;

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

void	var_lists(t_shell *shell)
{
	char_var_list(shell);
	int_var_list(shell);
	// printf("%s\n", shell->char_vars);
	// print_int_arr(shell->int_vars, ft_strlen(shell->char_vars));
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
	int		start;
	char	*flag;

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
