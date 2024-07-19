/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:48:13 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/19 11:11:14 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void print_arr(char **arr)
{
	int i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}
void print_commands(t_shell *shell)
{
	// t_shell *temp = shell;
	t_cmd *temp = shell->commands;
	t_rdct *temp_redir;

	int cmd_i = 1;
	int redir_i = 0;
	int i = 0;

	while(temp)
	{
		redir_i = 1;
		i = 0;
		printf("-command%d- :", cmd_i);
		while (temp->args[i])
		{
			printf("%s ", temp->args[i]);
			i++;
		}
		printf("is var: %d var in redir:%d ", temp->is_var, temp->var_in_redir);
		if (temp->reds)
		{
			printf("redirections: ");
			temp_redir = temp->reds;
			while(temp_redir)
			{
				printf("nr:%d type: %d filename: %s ", redir_i, temp->reds->type, temp->reds->filename);
				temp_redir = temp_redir->next;
				redir_i++;
			}
		}
		printf("\n");
		temp = temp->next;
		cmd_i++;
	}
}

// void copy_string(char **des, char *src)
// {
// 	int len = ft_strlen(src) +1;
// 	*des = (char *)malloc(len);
// 	int i = 0;
// 	while(src[i])
// 	{
// 		(*des)[i] = src[i];
// 		i++;
// 	}
// 	(*des)[i] = '\0';
// 	// printf("%s\n", *des);

// }

char **create_array(t_token *start, t_token *end)
{
	t_token *temp_start = start;
	int str_count = 0;
	int i = 0;
	char **arr;

	// if (start == end)
	// 	return (NULL);
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
		arr[i] = strdup(start->str); 
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

void while_not_op(t_token **temp, int *is_var, t_token *start)
{
	while((*temp) && ((*temp)->type != PIPE && !is_redir((*temp))))
	{
		if ((*temp)->type == VARIABLE)
			(*is_var)++;
		(*temp) = (*temp)->next;
	}
	if ((*temp) && (*temp)->type == PIPE)
	{
		if (!(*temp)->next)
			ft_error("pipe syntax error", ERR_SYNTAX);
		else if((*temp)->next->type == PIPE)
			ft_error("pipe syntax error", ERR_SYNTAX);
		else if ((*temp) == start)
			ft_error("pipe syntax error", ERR_SYNTAX);
	}
}

void parse_tokens(t_shell *shell)
{
	t_token *temp = shell->tokens;
	t_token *start;
	t_cmd *command = NULL;
	int is_var;
	char **arr;

	while(temp)
	{
		is_var = 0;
		start = temp;
		append_cmd_node(&command);
		while_not_op(&temp, &is_var, shell->tokens);
		arr = create_array(start, temp);
		if (is_redir(temp))
		{
			temp = check_redir(&command, temp); // move to current / latest command / look for redir and append node if needed
			start = temp;
			while_not_op(&temp, &is_var, shell->tokens);
			arr = append_array(arr, start, temp);
		}
		store_in_cmd(&command, arr, is_var);
		if (temp)
			temp = temp->next;
	}
	shell->commands = command;
}
