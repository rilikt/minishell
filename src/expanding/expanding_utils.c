/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:31:51 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/16 15:20:27 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	ft_arr_len(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (i);
	while (arr[i])
		i++;
	return (i);
}

void	free_arg_vars(t_exp *utils, int arg_len)
{
	int	i;

	i = 0;
	while (i < arg_len && utils->arg_vars)
	{
		if (ft_strlen(utils->arg_vars[i].type) > 0)
		{
			free(utils->arg_vars[i].s_index);
			free(utils->arg_vars[i].e_index);
		}
		free(utils->arg_vars[i].type);
		i++;
	}
	free(utils->arg_vars);
}

void	setup_help_struct(t_cmd *cmd, t_exp *u, int arg_len, int vars_used)
{
	int	i[2];
	int	var_count;

	i[0] = -1;
	u->arg_vars = (t_avars *)malloc(sizeof(t_avars) * arg_len + 1);
	error_check(u->arg_vars, "1setup_exp_help_struct", ERR_MALLOC);
	while (++i[0] < arg_len)
	{
		var_count = count_vars_in_str(cmd->args[i[0]]);
		u->arg_vars[i[0]].type = ms_substr(cmd->char_vars, vars_used,
				var_count);
		if (ft_strlen(u->arg_vars[i[0]].type))
		{
			u->arg_vars[i[0]].s_index = (int *)malloc(sizeof(int)
					* ft_strlen(u->arg_vars[i[0]].type));
			error_check(u->arg_vars[i[0]].type, "2setup_exp_struct",
				ERR_MALLOC);
			u->arg_vars[i[0]].e_index = (int *)malloc(sizeof(int)
					* ft_strlen(u->arg_vars[i[0]].type));
			error_check(u->arg_vars[i[0]].type, "3setup_exp_struct",
				ERR_MALLOC);
			i[1] = -1;
			while (++i[1] < var_count)
			{
				u->arg_vars[i[0]].s_index[i[1]] = cmd->int_vars[vars_used
					+ i[1]];
				u->arg_vars[i[0]].e_index[i[1]] = 0;
			}
			vars_used += var_count;
		}
	}
}

int	count_vars_in_str(char *str)
{
	int	j;
	int	var_count;

	j = -1;
	var_count = 0;
	if (str)
	{
		while (str[++j])
		{
			if (str[j] == '$')
				var_count++;
		}
	}
	return (var_count);
}
