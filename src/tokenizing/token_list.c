/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:07:13 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/16 14:16:08 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	find_type(char *str, int q_flag)
{
	int		i;
	char	*operator;

	operator = "|<>$";
	i = 0;
	while (operator[i] && !q_flag)
	{
		if (str[0] == operator[i])
		{
			if (str[0] == '|')
				return (PIPE);
			else if (str[0] == '$')
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

t_token	*create_node(char *str, int q_flag, t_shell *shell)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	error_check(new_node, "token node allocation", ERR_MALLOC);
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->type = find_type(str, q_flag);
	if (!q_flag && (!ft_strncmp(str, "~", 2) || !ft_strncmp(str, "~/", 2)) && ft_getenv("HOME", shell->envp))
	{
		if (!ft_strncmp(str, "~", 2))
			new_node->str = ms_strdup(ft_getenv("HOME", shell->envp));
		else
			new_node->str = ms_strjoin(ft_getenv("HOME", shell->envp),
					ft_strchr(str, '/'));
		free(str);
		str = NULL;
	}
	else
		new_node->str = str;
	new_node->char_vars = set_vars(str, shell->char_vars);
	if (new_node->char_vars)
		new_node->int_vars = set_int_vars(shell->int_vars, new_node->char_vars,
				shell->char_vars);
	return (new_node);
}

void	append_node(t_token **head, char *str, int q_flag, t_shell *shell)
{
	t_token	*new_node;
	t_token	*temp;

	new_node = create_node(str, q_flag, shell);
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
	is_heredoc(new_node, q_flag);
}
