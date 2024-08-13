/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitting_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 10:44:15 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/13 13:40:08 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	is_quoted(int i, t_avars arg_vars)
{
	int	j;
	int	l;
	int	p;

	j = -1;
	while (arg_vars.type[++j])
	{
		l = arg_vars.s_index[j];
		p = arg_vars.e_index[j];
		if (arg_vars.type[j] == '2')
		{
			if (i >= arg_vars.s_index[j] && i <= arg_vars.e_index[j])
				return (1);
		}
	}
	return (0);
}

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
		new_arr[i] = ft_strdup((char *)tmp->content);
		error_check(new_arr, "strdup in make_array_from_list", ERR_MALLOC);
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

	error_check(str, "strdup in fill_node", ERR_MALLOC);
	t = ft_lstnew(str);
	error_check(t, "lstnew in fill_node", ERR_MALLOC);
	ft_lstadd_back(new_arg, t);
	return ;
}

int	check_space(int *i, int *prev, char *str, t_avars arg_vars)
{
	if (str[i[0] + 1] == ' ' && !is_quoted(i[1] + 1, arg_vars))
	{
		ft_memmove(&str[i[0]], &str[i[0] + 1], ft_strlen(&str[i[0] + 1]) + 1);
		i[0]--;
		return (0);
	}
	else
		return (1);
}

void	setup_for_splitting(int *i, int *prev, t_list **new_arg)
{
	*new_arg = NULL;
	*i = -1;
	*prev = 0;
	return ;
}

void	iterate_index_area(char *str, t_list **new_arg, int index[2], int *prev)
{
	int	j;

	j = index[0];
	while (j <= index[1])
	{
		if (str[j] == ' ')
		{
			if (j != *prev)
				fill_node(new_arg, ft_substr(str, *prev, j - *prev));
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
	while (++i < ft_strlen(arg_vars.type))
	{
		if (arg_vars.type[i] == '1')
		{
			index[0] = arg_vars.s_index[i];
			index[1] = arg_vars.e_index[i];
			iterate_index_area(str, &new_arg, index, &prev);
		}
	}
	s = ft_strdup(&str[prev]);
	error_check(s, "strdup in divide_string", ERR_MALLOC);
	if (*s)
		fill_node(&new_arg, s);
	else
		free(s);
	return (make_arr_from_list(&new_arg));
}

void	put_args_back_together(char **args, char **new_args, char **arr, int *i)
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
}

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
	int		k;

	j = check_if_must_split(args[*i], &arg_vars[a]);
	if (j)
		arg_arr = divide_string_correctly(args[*i], arg_vars[a]);
	else
		return (args);
	new_len = ft_arr_len(args) - 1 + ft_arr_len(arg_arr);
	new_args = (char **)malloc(sizeof(char *) * (new_len + 1));
	error_check(new_args, "maloc in split_args", ERR_MALLOC);
	put_args_back_together(args, new_args, arg_arr, i);
	return (new_args);
}
