/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:01:47 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/14 17:25:29 by timschmi         ###   ########.fr       */
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
		if (str[i] && operator_check(&str[i + 1], &i))
			break ;
		if (is_whitespace(str[i]))
			break ;
		if (str[i])
			i++;
	}
	return (i);
}

void	tokenize(t_shell *shell)
{
	char	*token_str;
	t_token	*token;
	int		i;
	int		start;
	int		q_flag;

	token = NULL;
	i = 0;
	var_lists(shell);
	while (shell->input[i])
	{
		q_flag = 0;
		while (is_whitespace(shell->input[i]))
			i++;
		if (!shell->input[i])
			break ;
		start = i;
		i = token_loop(i, shell->input, shell);
		token_str = ms_substr(shell->input, start, i - start);
		token_str = check_qoutes(token_str, &q_flag, shell);
		append_node(&token, token_str, q_flag, shell);
	}
	shell->tokens = token;
}

int	operator_check(char *str, int *input_i)
{
	int		i;
	char	*operator;

	operator= "|<>";
	i = 0;
	if (!str)
		return (0);
	while (operator[i])
	{
		if (*str == operator[i])
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
	int		i;
	int		j;
	char	*operator;

	operator = "|<>";
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
	int		j;
	t_token	*temp;

	i = 1;
	temp = shell->tokens;
	while (temp)
	{
		printf("-token%d- str: %s, type: %d vars: %s\n", i, temp->str,
			temp->type, temp->char_vars);
		if (temp->char_vars)
		{
			j = 0;
			printf("int_vars:");
			while (j < ft_strlen(temp->char_vars))
			{
				printf("%d ", temp->int_vars[j]);
				j++;
			}
			printf("\n");
		}
		temp = temp->next;
		i++;
	}
}
