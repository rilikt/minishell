/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:07:13 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/12 16:32:39 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int find_type(char *str)
{
	char *operator = "|<>$";

	int i = 0;
	int j = 0;
	int len = ft_strlen(str);
	while (operator[i])
	{
		if (str[j] == operator[i])
		{
			if (str[j] == '|')
				return (PIPE);
			else if (str[j] == '$')
				return(VARIABLE);
			else if (str[j] == '<' && len == 1)
				return (IN_REDIRECT);
			else if (str[j] == '>' && len == 1)
				return (OUT_REDIRECT);
			else if (str[j] == '<')
				return (IN_HEREDOC);
			else if (str[j] == '>')
				return (OUT_RED_APPEND);
		}
		i++;
	}
	return(WORD);
}

t_token *create_node(char *str)
{
	t_token *new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	// if (!new_node)
	// 	exit_error();

	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->str = str;
	new_node->type = find_type(str);

	return (new_node);
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
	return ;
}