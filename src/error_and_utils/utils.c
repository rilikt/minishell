/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:19:54 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/19 11:58:10 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	free_struct(t_shell *shell)
{
	t_shell	*temp;
	t_token	*temp_tkn;
	t_cmd	*temp_cmd;
	t_rdct	*temp_redir;
	int		cmd_i;
	int		redir_i;
	int		i;

	temp = shell;
	cmd_i = 1;
	redir_i = 0;
	i = 0;
	while (temp->tokens)
	{
		temp_tkn = temp->tokens;
		temp->tokens = temp->tokens->next;
		free(temp_tkn->str);
		free(temp_tkn);
	}
	while (temp->commands)
	{
		temp_cmd = temp->commands;
		temp->commands = temp->commands->next;
		if (temp_cmd->reds)
		{
			while (temp_cmd->reds)
			{
				temp_redir = temp_cmd->reds;
				temp_cmd->reds = temp_cmd->reds->next;
				free(temp_redir);
			}
		}
		free(temp_cmd->args);
		free(temp_cmd);
	}
}

// void clean_shell(char **str)
// {
// 	int i;

// 	i = 0;
// 	while(str[i])
// 	{
// 		free(str[i]);
// 		i++;
// 	}
// 	free(str);
// }

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
