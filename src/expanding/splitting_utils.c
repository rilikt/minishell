/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   splitting_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 10:44:15 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/12 11:40:02 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	is_quoted(int i, t_avars arg_vars)
{
	int j;

	j = -1;

	while (arg_vars.type[++j])
	{
		int l = arg_vars.s_index[j];
		int p = arg_vars.e_index[j];
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
	return(new_arr);
}

void	fill_node(t_list **new_arg, char *str, int *i, int *prev)
{
	static int	start = 0;
	char		*tmp;
	t_list		*t;

	tmp = ft_substr(str, *prev, i[0] - *prev);
	error_check(tmp, "strdup in fill_node", ERR_MALLOC);
	if (!*tmp)
	{
		free(tmp);
		tmp = NULL;
	}
	if (start == 0)
	{
		free((*new_arg)->content);
		(*new_arg)->content = tmp;
		start = 1;
		*prev = i[0] + 1;
		return ;
	}
	t = ft_lstnew(tmp);
	error_check(t, "lstnew in fill_node", ERR_MALLOC);
	ft_lstadd_back(new_arg, t);
	*prev = i[0] + 1;
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

t_list	*setup_for_splitting(int *i, int *prev, char *str)
{
	t_list	*new;
	char	*s;

	s = ft_strdup(str);
	error_check(s, "strdup in setup_for_splitting", ERR_MALLOC);
	new = ft_lstnew(s);
	error_check(new, "lstnew in divide_str", ERR_MALLOC);
	i[0] = -1;
	i[1] = -1;
	*prev = 0;
	return (new);
	
}
char	**divide_string_correctly(char *str, t_avars arg_vars)
{
	t_list	*new_arg;
	int		prev;
	int		i[2];
	
	if (!str || !*str)
		return (NULL);
	new_arg = setup_for_splitting(i, &prev, str);
	while(++i[0] >= 0 && ++i[1] >= 0)
	{
		char c = str[i[0]];
		if (!str[i[0]])
		{
			if (i[0] != 0)
				fill_node(&new_arg, str, i, &prev);
			break;
		}
		if ((str[i[0]] == ' ' && !is_quoted(i[1], arg_vars)))
		{
			if (check_space(i, &prev, str, arg_vars))
				fill_node(&new_arg, str, i, &prev);
		}	
	}
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

char	**split_arg(char **args, t_avars *arg_vars, int *i, int a)
{
	char	**new_args;
	char	**arg_arr;
	int		new_len;
	int		j;
	int		k;

	if (ft_strchr(args[*i], ' ') && ft_strchr(arg_vars[a].type, '2'))
		arg_arr = divide_string_correctly(args[*i], arg_vars[a]);
	else
	{
		arg_arr = ft_split(args[*i], ' ');
		error_check(arg_arr, "ft_split in split_args", ERR_MALLOC);
	}
	new_len = ft_arr_len(args) - 1 + ft_arr_len(arg_arr);
	new_args = (char **)malloc(sizeof(char *) * (new_len + 1));
	error_check(new_args, "maloc in split_args", ERR_MALLOC);
	put_args_back_together(args, new_args, arg_arr, i);
	return (new_args);
}

// int	divide_string_at_var_index(char *str, t_avars arg_vars)
// {
// 	char	**str_arr;
// 	int		len;
// 	int		i;

// 	i = -1;
// 	len = ft_strlen(arg_vars.type);
// 	str_arr = (char **)malloc(sizeof(char *) * len + 1);
// 	error_check(str_arr, "malloc in divide string", ERR_MALLOC);
// 	while (++i <= len)
// 	{
// 		if (i = 0)
// 			str_arr[i] = ft_substr(str, 0, arg_vars.index[i] - 1);
// 		else if (i == len)
// 			str_arr[i] = ft_substr(str, arg_vars.index[i], ft_strlen(str[arg_vars.index[i]]));
// 		else
// 			str_arr[i] = ft_substr(str, arg_vars.index[i], arg_vars.index[i + 1] - arg_vars.index[i]);
// 	}
// 	str_arr[len + 1] = NULL;
// 	return(str_arr);
// }
/*
export T=" A   B   C   "

echo $T$T"$T" "$T" haaaaallo "$T"$T$T

*/
// char	**divide_string_correctly(char *str, t_avars arg_vars)
// {
// 	char	**str_arr;
// 	char	**tmp_arr;
// 	char	***split_part;
// 	int		i;
// 	int		j;

// 	i = -1;
// 	j = 0;
// 	split_part = (char **)malloc(sizeof(char **) * (ft_strlen(arg_vars.type) + 1));
// 	error_check(split_part, "malloc split part in divide_correctly", ERR_MALLOC);
// 	tmp_arr = divide_string_at_var_index(str, arg_vars);
// 	while (str_arr[i])
// 	{
// 		if (arg_vars.type[i] != '2')
// 		{
// 			split_part[i] = ft_split(str_arr[i], ' ');
// 			error_check(split_part, "split in divide_string_corr", ERR_MALLOC);
// 		}
		
// 	}
	
// }

// char **split_string(char **args, int *i, t_avars arg_vars, int arr_len)
// {
// 	char	**new_arr;
// 	int		new_len;
// 	char	***str_arr;
// 	int		j;
// 	int		k;

// 	j = -1;
// 	if (ft_strchr(arg_vars.type, '2'))
// 		str_arr = divide_string_correctly(args[*i], arg_vars);
// 	else
// 		str_arr = ft_split(args[*i], ' ');
// 	new_len = arr_len - 1 + ft_arr_len(str_arr);
// 	new_arr = (char **)malloc(sizeof(char *) * (new_len + 1));
// 	error_check(new_arr, "malloc in split_string", ERR_MALLOC);
// 	while (++j <= i)
// 		new_arr[j] = args[j];
// 	k = -1;
// 	while (++k <= ft_arr_len(str_arr))
// 		new_arr[j++] = str_arr[k];
// 	*i = j;
// 	k = *i;
// 	while (j <= arr_len)
// 		new_arr[j++] = args[++k];
// 	new_arr[new_len + 1] = NULL;
// 	return(new_arr);
// }

// char	**split_args(char **args, t_avars *arg_vars)
// {
// 	char	**new_args;
// 	int		i;
// 	int		f;
// 	i = 0;
// 	new_args = args;
// 	while (new_args[i])
// 	{
// 		if (strchr(args[i], ' '))
// 		{
// 			f = i;
// 			new_args = split_string(new_args, &i, arg_vars[i], ft_arr_len(args));
// 			free(args[f]);
// 		}
// 		i++;
// 	}
// 	return (new_args);
// }


// char	**split_and_arrange_cmd(char **args)
// {
// 	char	**arr;
// 	char	**new_args;
// 	int		i;
// 	int		j;
// 	int		k;

// 	i = 0;
// 	j = 0;
// 	k = -1;
// 	arr = ft_split(args[0], ' ');
// 	error_check(arr, "split failed", ERR_SPLIT);
// 	while (arr[i])
// 		i++;
// 	while (args[j])
// 		j++;
// 	new_args = (char **)malloc(sizeof(char *) * (i++ + j));
// 	error_check(new_args, "malloc failed", ERR_MALLOC);
// 	while (--i > 0 && ++k >= 0)
// 		new_args[k] = arr[k];
// 	while (i < j)
// 		new_args[++k] = args[++i];
// 	free(args[0]);
// 	free(args);
// 	new_args[k] = NULL;
// 	return (new_args);
// }

// char	**split_and_arrange_arg(char **args, int i, int arg_len, char **new_args)
// {
// 	char	**arr;
// 	int		i_new;
// 	int		j;
// 	int		k;
// 	int		curr_pos;

// 	arr = ft_split(args[i], ' ');
// 	error_check(arr, "split failed", ERR_SPLIT);
// 	i_new = ft_arr_len(arr);
// 	j = i;
// 	k = arg_len - i - 1;
// 	curr_pos = -1;
// 	new_args = (char **)malloc(sizeof(char *) * (i_new++ + j));
// 	error_check(new_args, "malloc failed", ERR_MALLOC);
// 	while(j-- && ++curr_pos >= 0)
// 		new_args[curr_pos] = args[curr_pos];
// 	j = 0;
// 	while (i_new-- && ++curr_pos >= 0)
// 		new_args[curr_pos] = arr[j++];
// 	while (k-- && ++curr_pos)
// 		new_args[curr_pos] = args[++i];
// 	free(args[i]);
// 	free(args);
// 	new_args[++curr_pos] = NULL;
// 	return (new_args);
// }

// char	**check_and_insert_first_index(char **args, t_exp *utils)
// {
// 	int		i;
// 	int		j;
// 	char	*tmp;
// 	char	*tmp2;
// 	char	*pos_space;
// 	char	**new_arr;
	
// 	i = 0;
// 	j = ft_arr_len(args);
// 	new_arr = args;
// 	if (!ft_strlen(utils->arg_vars.c_vars))
// 		return (args);
// 	if (!(utils->arg_vars.c_vars[i] == '2'))
// 	{
// 		if (ft_strchr(args[0], ' '))
// 			new_arr = split_and_arrange_cmd(args);
// 	}
// 	else if (ft_strlen(utils->arg_vars.c_vars) > 1)
// 	{
// 		pos_space = ft_strchr(&args[0][*utils->arg_vars.i_vars], ' ');
// 		if (pos_space)
// 		{
// 			tmp = ft_substr(args[0], 0, pos_space - args[0]);
// 			error_check(new_arr, "substr in check_first_index", ERR_MALLOC);
// 			tmp2 = ft_strdup(pos_space);
// 			error_check(new_arr, "substr in check_first_index", ERR_MALLOC);
// 			free(args[0]);
// 			new_arr = (char **)malloc(sizeof(char *) * j + 2);
// 			error_check(new_arr, "malloc in check_first_index", ERR_MALLOC);
// 			new_arr[i++] = tmp;
// 			new_arr[i++] = tmp2;
// 			j = 0;
// 			while (args[++j])
// 				new_arr[i++] = args[j];
// 			new_arr[j] = NULL;
// 		}
// 	}
// 	return (new_arr);
// }