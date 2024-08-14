/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide_argument.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 11:17:07 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/14 11:48:31 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

char	**make_arr_from_list(t_list **new_arg)
{
	char	**new_arr;
	t_list	*tmp;
	int		i;

	i = ft_lstsize(*new_arg) + 1;
	new_arr = (char **)malloc(sizeof(char *) * i);
	error_check(new_arr, "malloc in make_array_from_list", ERR_MALLOC);
	tmp = *new_arg;
	i = 0;
	while (tmp && tmp->content)
	{
		new_arr[i] = ms_strdup((char *)tmp->content);
		tmp = tmp->next;
		i++;
	}
	new_arr[i] = NULL;
	ft_lstclear(new_arg, &free);
	return (new_arr);
}

void	fill_node(t_list **new_arg, char *str)
{
	t_list	*t;

	t = ft_lstnew(str);
	error_check(t, "lstnew in fill_node", ERR_MALLOC);
	ft_lstadd_back(new_arg, t);
	return ;
}

void	setup_for_splitting(int *i, int *prev, t_list **new_arg)
{
	*new_arg = NULL;
	*i = -1;
	*prev = 0;
	return ;
}

void	iterate_index_area(char *str, t_list **new_arg, int *index, int *prev)
{
	int	j;

	j = index[0];
	while (j <= index[1])
	{
		if (str[j] == ' ')
		{
			if (j != *prev)
				fill_node(new_arg, ms_substr(str, *prev, j - *prev));
			while (str[j] == ' ' && j <= index[1])
			{
				j++;
				if (str[j] != ' ' || j > index[1])
					*prev = j;
			}
		}
		j++;
	}
	return ;
}

char	**divide_string_correctly(char *str, t_avars arg_vars)
{
	t_list	*new_arg;
	char	*s;
	int		i;
	int		prev;
	int		index[2];

	setup_for_splitting(&i, &prev, &new_arg);
	while (++i < (int)ft_strlen(arg_vars.type))
	{
		if (arg_vars.type[i] == '1')
		{
			index[0] = arg_vars.s_index[i];
			index[1] = arg_vars.e_index[i];
			iterate_index_area(str, &new_arg, index, &prev);
		}
	}
	s = ms_strdup(&str[prev]);
	if (*s)
		fill_node(&new_arg, s);
	else
		free(s);
	return (make_arr_from_list(&new_arg));
}
