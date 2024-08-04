/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:31:51 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/04 17:28:11 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	check_char_behind(char **pos, char **str, int *tmp, t_exp_help *u)
{
	if (u->vars.c_vars[u->count] == '3')
	{
		ft_memmove(*pos, *pos + 1, ft_strlen(*pos + 1) + 1);
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
		else if (*(*pos + 1) == '$' && (u->vars.c_vars[u->count] == '1' || u->vars.c_vars[u->count] == '1'))
			ft_memmove(*pos, *pos + 1, ft_strlen(*pos + 1) + 1);
		else if (*(*pos + 1) == ' ' || *(*pos+ 1) == '/')
			(*tmp)++;
		else
			(*tmp)++;
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
	while (i_new-- && ++curr_pos)
		new_args[curr_pos] = arr[j++];
	while (k-- && ++curr_pos)
		new_args[curr_pos] = args[++i];
	free(args[i]);
	free(args);
	new_args[++curr_pos] = NULL;
	return (new_args);
}
