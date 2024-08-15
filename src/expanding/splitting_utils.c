/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitting_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 10:44:15 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/15 23:56:41 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	check_if_must_split(char *arg, t_avars *arg_vars)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	len = ft_strlen(arg_vars->type);
	while (i < len)
	{
		if (arg_vars->type[i] == '1')
		{
			j = arg_vars->s_index[i];
			while (j <= arg_vars->e_index[i])
			{
				if (arg[j] == ' ')
					return (1);
				j++;
			}
		}
		i++;
	}
	return (0);
}

char	**split_arg(char **args, t_avars *arg_vars, int *i, int a)
{
	char	**new_args;
	char	**arg_arr;
	int		new_len;
	int		j;

	j = check_if_must_split(args[*i], &arg_vars[a]);
	if (j)
		arg_arr = divide_string_correctly(args[*i], arg_vars[a]);
	else
		return (args);
	new_len = ft_arr_len(args) - 1 + ft_arr_len(arg_arr);
	new_args = (char **)malloc(sizeof(char *) * (new_len + 1));
	error_check(new_args, "maloc in split_args", ERR_MALLOC);
	rejoin_args(args, new_args, arg_arr, i);
	free(args);
	return (new_args);
}

void	rejoin_args(char **args, char **new_args, char **arr, int *i)
{
	int	j;
	int	k;

	j = -1;
	while (++j < *i)
		new_args[j] = args[j];
	k = 0;
	while (k < ft_arr_len(arr))
		new_args[j++] = arr[k++];
	k = *i;
	free(args[k++]);
	*i = j - 1;
	while (args[k])
		new_args[j++] = args[k++];
	new_args[j] = NULL;
	free(arr);
}
