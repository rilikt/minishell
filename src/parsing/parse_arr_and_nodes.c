/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_nodes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:22:48 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/19 11:23:47 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

char **create_array(t_token *start, t_token *end)
{
	t_token *temp_start = start;
	int str_count = 0;
	int i = 0;
	char **arr;

	while (temp_start != end)
	{
		str_count++;
		temp_start = temp_start->next;
	}
	arr = (char **)malloc((str_count+1) * (sizeof(char*)));
	if (!arr)
		ft_error("malloc error", ERR_MALLOC);
	while (i < str_count)
	{
		// copy_string(&arr[i], start->str);
		// arr[i] = strdup(start->str); 
		arr[i] = start->str;
		start = start->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char **append_array(char **arr, t_token *start, t_token *end)
{
	t_token *temp_start = start;
	int str_count = 0;
	int i = 0;
	int len = 0;
	char **re;

	if (start == end)
		return (arr);
	while (temp_start != end)
	{
		str_count++;
		temp_start = temp_start->next;
	}
	while (arr[len])
		len++;
	re = (char **)malloc((str_count+len+1) * (sizeof(char *)));
	if (!re)
		ft_error("malloc error", ERR_MALLOC);
	while (i < len)
	{
		re[i] = arr[i];
		i++;
	}
	while (start != end)
	{
		re[i] = start->str;
		i++;
		start = start->next;
	}
	re[i] = NULL;
	return (free(arr), re);
}

void append_cmd_node(t_cmd **head)
{
	t_cmd *new_node;
	t_cmd *temp;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
			ft_error("malloc error", ERR_MALLOC);
	new_node->next = NULL;
	new_node->reds = NULL;
	new_node->args = NULL;
	new_node->is_var = 0;
	new_node->var_in_redir = 0;
	if (*head == NULL)
	{
		*head = new_node;
		return;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

void store_in_cmd(t_cmd **head, char **arr, int is_var)
{
	t_cmd *temp = *head;
	while (temp->next)
		temp = temp->next;
	
	temp->args = arr;
	temp->is_var = is_var;
}