/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:31:51 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/04 16:27:44 by timschmi         ###   ########.fr       */
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
	while (*pos && (*(*pos + 1) == '\0' || *(*pos + 1) == '$' || *(*pos+ 1) == ' '))
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
		else if (*(*pos + 1) == ' ')
			(*tmp)++;
		else
			(*tmp)++;
		u->count++;
		*pos = ft_strchr(&str[0][*tmp], '$');
	}
	return ;
}

char	**split_and_arrange_cmd(char **args, int u)
{
	char	**arr;
	char	**new_args;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = -1;
	arr = ft_split(args[u], ' ');
	error_check(arr, "split failed", ERR_SPLIT);
	while (arr[i])
		i++;
	while (args[j])
		j++;
	new_args = (char **)malloc(sizeof(char *) * (i++ + j));
	error_check(new_args, "malloc failed", ERR_MALLOC);
	while (--i > 0 && ++k >= 0)
		new_args[k] = arr[k];
	while (i < j)
		new_args[++k] = args[++i];
	free(args[0]);
	free(args);
	new_args[k] = NULL;
	return (new_args);
}
