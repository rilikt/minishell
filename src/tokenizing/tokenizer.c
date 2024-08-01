/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:01:47 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/01 11:50:46 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	token_loop(int i, char *str, t_shell *shell)
{
	while (str[i] && !is_whitespace(str[i]))
	{
		if (in_qoutes(str, &i, shell))
			break ;
		if (is_operator(str, &i))
			break ;
		else if (operator_check(&str[i + 1], &i))
			break ;
		if (is_whitespace(str[i]))
			break ;
		i++;
	}
	return (i);
}

void	tokenize(t_shell *shell)
{
	char	*str;
	char	*token_str;
	t_token	*token;
	int		i;
	int		start;
	int		q_flag;

	str = shell->input;
	token = NULL;
	i = 0;
	create_var_list(shell);
	while (str[i])
	{
		q_flag = 0;
		while (is_whitespace(str[i]))
			i++;
		if (!str[i])
			break ;
		start = i;
		i = token_loop(i, str, shell);
		token_str = ft_substr(str, start, i - start);
		token_str = check_qoutes(token_str, &q_flag, shell);
		append_node(&token, token_str, q_flag, shell);
	}
	shell->tokens = token;
}

int	operator_check(char *str, int *input_i)
{
	int	i;

	char *operator= "|<>";
	i = 0;
	while (operator[i])
	{
		if (str[0] == operator[i])
		{
			*input_i += 1;
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_operator(char *str, int *input_i)
{
	int	i;
	int	j;

	char *operator= "|<>";
	i = *input_i;
	j = 0;
	while (operator[j])
	{
		if (str[i] == operator[j])
		{
			if ((str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i
					+ 1] == '>'))
				i++;
			*input_i = i + 1;
			return (1);
		}
		j++;
	}
	return (0);
}

int	is_whitespace(char c)
{
	char	*whitespace;
	int		i;

	whitespace = " \t\n\v\f\r";
	i = 0;
	while (whitespace[i])
	{
		if (c == whitespace[i])
			return (1);
		i++;
	}
	return (0);
}

void	print_tokens(t_shell *shell)
{
	int		i;
	t_token	*temp;

	i = 1;
	temp = shell->tokens;
	while (temp)
	{
		printf("-token%d- str: %s, type: %d vars: %s\n", i, temp->str, temp->type, temp->vars);
		temp = temp->next;
		i++;
	}
}
