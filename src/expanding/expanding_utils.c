/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:31:51 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/05 13:15:53 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	check_char_behind(char **pos, char **str, int *tmp, t_exp_help *u)
{
	if (u->vars.c_vars[u->count] == '3')
	{
		ft_memmove(*pos, *pos + 1, ft_strlen(*pos + 1) + 1);
		u->arg_vars.i_vars[ u->count] = (pos + 1) - str;
		u->count++;
		*pos = ft_strchr(&str[0][*tmp], '$');
	}
	if (u->vars.c_vars[u->count] == '0')
	{
		(*tmp)++;
		
		u->count++;
		*pos = ft_strchr(&str[0][*tmp], '$');
	}
	while (*pos && (*(*pos + 1) == '\0' || *(*pos + 1) == '$' || *(*pos+ 1) == ' '
			|| *(*pos+ 1) == '/'))
	{
		if (*(*pos + 1) == '\0')
		{
			(*tmp)++;
			u->count++;
			*pos = NULL;
			return ;
		}
		else if (*(*pos + 1) == '$' && (u->vars.c_vars[u->count] == '1' || u->vars.c_vars[u->count] == '2'))
			ft_memmove(*pos, *pos + 1, ft_strlen(*pos + 1) + 1);
		else if (*(*pos + 1) == ' ' || *(*pos+ 1) == '/')
			(*tmp)++;
		else
			(*tmp)++;
		*(u->arg_vars.i_vars) = *tmp;
		u->count++;
		*pos = ft_strchr(&str[0][*tmp], '$');
	}
	return ;
}

int	ft_arr_len(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (i);
	while  (arr[i])
		i++;
	return (i);
}

char	**check_and_insert_first_index(char **args, t_exp_help *utils)
{
	int		i;
	int		j;
	char	*tmp;
	char	*tmp2;
	char	*pos_space;
	char	**new_arr;
	
	i = 0;
	j = ft_arr_len(args);
	new_arr = args;
	if (!ft_strlen(utils->arg_vars.c_vars))
		return (args);
	if (!(utils->arg_vars.c_vars[i] == '2'))
	{
		if (ft_strchr(args[0], ' '))
			new_arr = split_and_arrange_cmd(args, i, j, NULL);
	}
	else if (ft_strlen(utils->arg_vars.c_vars) > 1)
	{
		pos_space = ft_strchr(&args[0][*utils->arg_vars.i_vars], ' ');
		if (pos_space)
		{
			tmp = ft_substr(args[0], 0, pos_space - args[0]);
			error_check(new_arr, "substr in check_first_index", ERR_MALLOC);
			tmp2 = ft_strdup(pos_space);
			error_check(new_arr, "substr in check_first_index", ERR_MALLOC);
			free(args[0]);
			new_arr = (char **)malloc(sizeof(char *) * j + 2);
			error_check(new_arr, "malloc in check_first_index", ERR_MALLOC);
			new_arr[i++] = tmp;
			new_arr[i++] = tmp2;
			j = 0;
			while (args[++j])
				new_arr[i++] = args[j];
			new_arr[j] = NULL;
		}
	}
	return (new_arr);
}

char	**split_and_arrange_cmd(char **args, int i, int arg_len, char **new_args)
{
	char	**arr;
	int		i_new;
	int		j;
	int		k;
	int		curr_pos;

	arr = ft_split(args[i], ' ');
	error_check(arr, "split failed", ERR_SPLIT);
	i_new = ft_arr_len(arr);
	j = i;
	k = arg_len - i - 1;
	curr_pos = -1;
	new_args = (char **)malloc(sizeof(char *) * (i_new++ + j));
	error_check(new_args, "malloc failed", ERR_MALLOC);
	while(j-- && ++curr_pos >= 0)
		new_args[curr_pos] = args[curr_pos];
	j = 0;
	while (i_new-- && ++curr_pos >= 0)
		new_args[curr_pos] = arr[j++];
	while (k-- && ++curr_pos)
		new_args[curr_pos] = args[++i];
	free(args[i]);
	free(args);
	new_args[++curr_pos] = NULL;
	return (new_args);
}
