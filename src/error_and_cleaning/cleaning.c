/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:19:54 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/14 17:50:07 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	free_tokens(t_shell *shell)
{
	t_token	*temp_tkn;
	t_shell	*temp;


	temp = shell;
	while (temp->tokens)
	{
		temp_tkn = temp->tokens;
		temp->tokens = temp->tokens->next;
		if (temp_tkn->str)
			free(temp_tkn->str);
		if (temp_tkn->char_vars)
		{
			free(temp_tkn->char_vars);
			free(temp_tkn->int_vars);
		}
		free(temp_tkn);
	}
}

void	free_struct(t_shell *shell)
{
	t_shell	*temp;
	t_cmd	*temp_cmd;
	t_rdct	*temp_redir;

	temp = shell;
	while (temp->commands)
	{
		temp_cmd = temp->commands;
		temp->commands = temp->commands->next;
		while (temp_cmd->reds)
		{
			temp_redir = temp_cmd->reds;
			temp_cmd->reds = temp_cmd->reds->next;
			if (temp_redir->filename)
				free(temp_redir->filename);
			if (temp_redir->char_vars)
			{
				free(temp_redir->char_vars);
				free(temp_redir->int_vars);
			}
			free(temp_redir);
		}
		if (temp_cmd->args)
			free_string_array(temp_cmd->args);
		if (temp_cmd->char_vars)
		{
			free(temp_cmd->char_vars);
			free(temp_cmd->int_vars);
		}
		free(temp_cmd);
	}
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	free(shell->char_vars);
	free(shell->int_vars);
}

void	free_string_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		// printf("%s\n", str[i]);
		if (str[i])
			free(str[i]);
		i++;
	}
	free(str);
}

// void print_list(t_cmd *head)
// {
// 	t_cmd *temp = head;

// 	while (temp)
// 	{
// 		printf("operator: %s, command1: %s, argument1: %s, command2: %s,
			// argument2: %s\n", temp->op, temp->cmd1, temp->arg1, temp->cmd2,
			// temp->arg2);
// 		temp = temp->next;
// 	}
// }

// int find_type(char *str)
// {
// 	char *operator = "|<>";

// 	int i = 0;
// 	int j = 0;
// 	int len = ft_strlen(str);

// 	while (operator[i])
// 	{
// 		if (str[j] == operator[i])
// 		{
// 			if (str[j] == '|')
// 				return (PIPE);
// 			else if (str[j] == '<' && len == 1)
// 				return (IN_REDIRECT);
// 			else if (str[j] == '>' && len == 1)
// 				return (OUT_REDIRECT);
// 			else if (str[j] == '<')
// 				return (IN_HEREDOC);
// 			else if (str[j] == '>')
// 				return (OUT_RED_APPEND);
// 		}
// 		i++;
// 	}
// 	return(WORD);
// }

// t_token *create_node(char *str)
// {
// 	t_token *new_node;

// 	new_node = (t_token *)malloc(sizeof(t_token));
// 	// if (!new_node)
// 	// 	exit_error();

// 	new_node->next = NULL;
// 	new_node->prev = NULL;
// 	new_node->str = str;
// 	new_node->type = find_type(str);

// 	return (new_node);
// }

// void append_node(t_token **head, char *str)
// {
// 	t_token *new_node;
// 	t_token *temp;

// 	new_node = create_node(str);
// 	if (*head == NULL)
// 	{
// 		*head = new_node;
// 		return ;
// 	}
// 	temp = *head;
// 	while (temp->next)
// 		temp = temp->next;
// 	temp->next = new_node;
// 	new_node->prev = temp;
// 	return ;
// }
