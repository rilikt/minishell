/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:07:13 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/05 12:40:38 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	check_variable(char *str, int q_flag)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && (!is_whitespace(str[i + 1]) && str[i + 1]))
			return (VARIABLE);
		i++;
	}
	if (q_flag)
	{
		return (IN_QUOTES);
	}
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

char	*set_vars(char *str, char *vars)
{
	static int	i = 0;
	int			j;
	int			count;
	char		*re;

	j = 0;
	count = 0;
	while (str[j])
	{
		if (str[j] == '$')
			count++;
		j++;
	}
	if (count == 0)
		return (NULL);
	re = ft_substr(vars, i, count);
	error_check(re, "set_vars", ERR_MALLOC);
	i += count;
	if (!vars[i])
		i = 0;
	return (re);
}

int	*set_int_vars(int *arr, char *str, char *vars)
{
	static int	i = 0;
	int			len;
	int			*re;
	int			j;

	j = 0;
	len = ft_strlen(str);
	re = (int *)malloc(len * sizeof(int));
	error_check(re, "set_int_vars", ERR_MALLOC);
	len += i;
	while (i < len)
	{
		re[j] = arr[i];
		j++;
		i++;
	}
	if (!vars[i])
		i = 0;
	return (re);
}

t_token	*create_node(char *str, int q_flag, t_shell *shell)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token));
	error_check(new_node, "token node allocation", ERR_MALLOC);
	new_node->next = NULL;
	new_node->prev = NULL;
	if (!q_flag && !ft_strncmp(str, "~", 2))
	{
		free(str);
		new_node->str = ft_strdup(getenv("HOME"));
	}
	else
		new_node->str = str;
	new_node->type = find_type(str, q_flag);
	new_node->char_vars = set_vars(str, shell->char_vars);
	if (new_node->char_vars)
		new_node->int_vars = set_int_vars(shell->int_vars, new_node->char_vars,
				shell->char_vars);
	return (new_node);
}

int	count_quotes(char *str, int q_count, int start)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			start = i;
			i++;
			while (str[i])
			{
				if (str[i] == str[start])
				{
					q_count += 2;
					break ;
				}
				i++;
			}
			if (str[i] != str[start])
				return (-1);
		}
		if (str[i])
			i++;
	}
	return (q_count);
}

char	*check_and_rm_quotes(char *str)
{
	char	*re;
	int		count;

	count = count_quotes(str, 0, 0);
	if (count == -1)
		return ("\0");
	re = (char *)malloc(ft_strlen(str) + 1 - count);
	error_check(re, "check_and_rm_quotes", ERR_MALLOC);
	return (create_string(str, re, 0, 0, 0));
}

void	is_heredoc(t_token *node)
{
	char	*line;
	char	*input;
	char	*delimiter;

	if (node->prev->type != IN_HEREDOC || node->type  == PIPE || is_redir(node))
		return ;
	line = NULL;
	input = NULL;
	delimiter = check_and_rm_quotes(node->str);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter))
			&& delimiter[0] != '\0')
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

void	append_node(t_token **head, char *str, int q_flag, t_shell *shell)
{
	t_token	*new_node;
	t_token	*temp;

	// if (!str || !str[0]) // removes empty strings
	// {
	// 	if (str)
	// 		free(str);
	// 	return ;
	// }
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
	is_heredoc(new_node);
}
