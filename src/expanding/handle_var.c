/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 11:04:44 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/14 17:29:44 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

char	*get_var(char *pos, char **var_name, int var_len, t_exp *utils)
{
	char	*tmp;
	char	*var_value;

	var_value = NULL;
	tmp = pos + 1;
	if (*tmp == '?')
		var_value = ft_itoa(utils->exit);
	*var_name = ms_substr(pos, 1, var_len);
	if (!var_value)
		var_value = ft_getenv(*var_name, utils->envp);
	return (var_value);
}

int	insert_var(char **str, char *pos, char *var_value, char *var_name)
{
	char	*new_str;
	int		new_len;
	char	*var_end;
	int		index_var_end;

	var_end = pos + ft_strlen(var_name) + 1;
	new_len = ft_strlen(*str) - (ft_strlen(var_name) + 1)
		+ ft_strlen(var_value);
	new_str = (char *)malloc(sizeof(char) * new_len + 1);
	error_check(new_str, "malloc in insert_var", ERR_MALLOC);
	ft_strlcpy(new_str, *str, pos - *str + 1);
	ft_strlcpy(&(new_str[ft_strlen(new_str)]), var_value, ft_strlen(var_value)
		+ 1);
	index_var_end = ft_strlen(new_str);
	ft_strlcpy(&(new_str[ft_strlen(new_str)]), var_end, ft_strlen(var_end) + 1);
	free(*str);
	free(var_name);
	*str = new_str;
	return (index_var_end);
}

void	handle_case_one_two(int i, char **pos, int *tmp, t_exp *utils)
{
	char	*var_name;
	char	*var_value;
	int		var_len;

	var_value = NULL;
	var_name = NULL;
	var_len = utils->arg_vars[i].s_index[utils->v_count];
	utils->arg_vars[i].s_index[utils->v_count] = *tmp;
	if (var_len)
	{
		var_value = get_var(*pos, &var_name, var_len, utils);
		if (!var_value)
			ft_memmove(*pos, *pos + var_len + 1, ft_strlen(*pos + var_len
					+ 1) + 1);
		else
			*tmp = insert_var(utils->str, *pos, var_value, var_name);
	}
	else
		*tmp += 1;
	utils->arg_vars[i].e_index[utils->v_count] = *tmp - 1;
	
	return ;
}

void	handle_var(int i, char **pos, int *tmp, t_exp *utils)
{
	if (utils->arg_vars[i].type[utils->v_count] == '0')
	{
		*tmp += 1;
		utils->arg_vars[i].e_index[utils->v_count] = *tmp - 1;
	}
	else if (utils->arg_vars[i].type[utils->v_count] == '1'
		|| utils->arg_vars[i].type[utils->v_count] == '2')
	{
		handle_case_one_two(i, pos, tmp, utils);
	}
	else if (utils->arg_vars[i].type[utils->v_count] == '3')
	{
		ft_memmove(*pos, *pos + 1, ft_strlen(*pos + 1) + 1);
		*tmp = *pos - *(utils->str);
	}
}
