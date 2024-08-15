/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arr_and_nodes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:22:48 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/15 22:13:32 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

char	**create_array(t_token *start, t_token *end)
{
	t_token	*temp_start;
	int		str_count;
	int		i;
	char	**arr;

	temp_start = start;
	str_count = 0;
	i = 0;
	while (temp_start != end)
	{
		str_count++;
		temp_start = temp_start->next;
	}
	arr = (char **)malloc((str_count + 1) * (sizeof(char *)));
	error_check(arr, "create_array", ERR_MALLOC);
	while (i < str_count)
	{
		arr[i] = ms_strdup(start->str);
		start = start->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

int	size_to_allocate(char **arr, t_token *start, t_token *end)
{
	t_token	*temp_start;
	int		len;
	int		str_count;

	temp_start = start;
	len = 0;
	str_count = 0;
	while (temp_start != end)
	{
		str_count++;
		temp_start = temp_start->next;
	}
	while (arr[len])
		len++;
	return (str_count + len + 1);
}

char	**append_array(char **arr, t_token *start, t_token *end)
{
	int		i;
	char	**re;

	i = 0;
	if (start == end)
		return (arr);
	re = (char **)malloc(size_to_allocate(arr, start, end) * (sizeof(char *)));
	error_check(re, "append_array", ERR_MALLOC);
	while (arr[i])
	{
		re[i] = ms_strdup(arr[i]);
		i++;
	}
	while (start != end)
	{
		re[i] = ms_strdup(start->str);
		i++;
		start = start->next;
	}
	re[i] = NULL;
	free_string_array(arr);
	return (re);
}

void	append_cmd_node(t_cmd **head)
{
	t_cmd	*new_node;
	t_cmd	*temp;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	error_check(new_node, "append_cmd_node", ERR_MALLOC);
	new_node->next = NULL;
	new_node->reds = NULL;
	new_node->args = NULL;
	new_node->is_var = 0;
	new_node->char_vars = NULL;
	new_node->var_in_redir = 0;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

void	store_in_cmd(t_cmd **head, char **arr, char *vars, int *int_vars)
{
	t_cmd	*temp;

	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->args = arr;
	temp->int_vars = int_vars;
	temp->char_vars = vars;
}
