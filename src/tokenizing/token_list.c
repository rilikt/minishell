/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:07:13 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/30 14:30:33 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	check_variable(char *str, int q_flag)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39)
			return (IN_QUOTES);
		if (str[i] == '$' && (!is_whitespace(str[i + 1]) && str[i + 1]))
			return (VARIABLE);
		i++;
	}
	if (q_flag)
		return (IN_QUOTES);
	return (WORD);
}

int	find_type(char *str, int q_flag)
{
	int	i;

	char *operator= "|<>$";
	i = 0;
	while (operator[i] && !q_flag)
	{
		if (str[0] == operator[i])
		{
			if (str[0] == '|')
				return (PIPE);
			else if (str[0] == '$' && str[1])
				return (VARIABLE);
			else if (str[0] == '<' && !str[1])
				return (IN_REDIRECT);
			else if (str[0] == '>' && !str[1])
				return (OUT_REDIRECT);
			else if (str[0] == '<')
				return (IN_HEREDOC);
			else if (str[0] == '>')
				return (OUT_RED_APPEND);
		}
		i++;
	}
	return (check_variable(str, q_flag));
}

t_token	*create_node(char *str, int q_flag)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	error_check(new_node, "token node allocation", ERR_MALLOC);
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->str = str;
	new_node->type = find_type(str, q_flag);
	return (new_node);
}

void	is_heredoc(t_token *node)
{
	char	*line;
	char	*input;
	char	*delimiter;

	if (node->prev->type != IN_HEREDOC)
		return ;
	line = NULL;
	input = NULL;
	delimiter = node->str;
	while (1)
	{
		line = readline("> ");
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter)))
			break ;
		line = ft_strjoin(line, "\n");
		error_check(line, "ft_strjoin", ERR_MALLOC);
		input = ft_strjoin(input, line);
		error_check(input, "ft_strjoin", ERR_MALLOC);
	}
	node->str = input;
	if (input)
		node->type = check_variable(input, 0);
}

void	append_node(t_token **head, char *str, int q_flag)
{
	t_token	*new_node;
	t_token	*temp;

	new_node = create_node(str, q_flag);
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
	new_node->prev = temp;
	is_heredoc(new_node);
}
