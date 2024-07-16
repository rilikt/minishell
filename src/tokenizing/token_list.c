/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:07:13 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/16 11:33:45 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int check_variable(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] == '$' && !is_whitespace(str[i+1]))
			return(VARIABLE);
		i++;
	}
	return(WORD);
}

int find_type(char *str)
{
	char *operator = "|<>$";
	int i = 0;
	int len = ft_strlen(str);
	while (operator[i])
	{
		if (str[0] == operator[i])
		{
			if (str[0] == '|')
				return (PIPE);
			else if (str[0] == '$')
				return(VARIABLE);
			else if (str[0] == '<' && len == 1)
				return (IN_REDIRECT);
			else if (str[0] == '>' && len == 1)
				return (OUT_REDIRECT);
			else if (str[0] == '<')
				return (IN_HEREDOC); // maybe set a flag and dont check everytime
			else if (str[0] == '>')
				return (OUT_RED_APPEND);
		}
		i++;
	}
	if (str[0] == 34)
		return (check_variable(str));
	return(WORD);
}

t_token *create_node(char *str)
{
	t_token *new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	if (!new_node)
		ft_error("malloc error", ERR_MALLOC);

	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->str = str;
	new_node->type = find_type(str);

	return (new_node);
}

void is_heredoc(t_token *node)
{
	if (node->prev->type != IN_HEREDOC)
		return;
	
	char *line = NULL;
	char *input = NULL;
	char *delimiter = node->str;
	while(1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter)))
			break;
		line = ft_strjoin(line, "\n");
		input = ft_strjoin(input, line);
	}
	node->str = input;
	if (input)
		node->type = check_variable(input);
}

void append_node(t_token **head, char *str)
{
	t_token *new_node;
	t_token *temp;

	new_node = create_node(str);
	if (*head == NULL)
	{
		*head = new_node;
		return;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
	new_node->prev = temp;
	is_heredoc(new_node);
	return ;
}
