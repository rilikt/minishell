/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:01:47 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/16 17:35:40 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

char *rm_qoutes(char *str)
{
	int i = 0;

	if (str[i] != 34 && str[i] != 39)
		return (str);
	int len = ft_strlen(str) - 2;
	char *re = (char *)malloc(len);
	re[len] = '\0';
	while (i < len)
	{
		re[i] = str[i+1];
		i++;
	}
	free (str);
	return (re);
}

void tokenize(t_shell *shell)
{
	char *str = shell->input;
	char *token_str;
	t_token *token = NULL;

	int i = 0;
	int start = 0;
	while (str[i])
	{
		while (is_whitespace(str[i]))
			i++;
		if (!str[i])
			break;
		start = i;
		while (str[i] && !is_whitespace(str[i]))
		{
			if (in_qoutes(str, &i))
				break;
			else if (is_operator(str, &i))
				break;
			else if (operator_check(&str[i+1], &i))
				break;
			i++;
		}
		token_str = ft_substr(str, start, i - start);
		token_str = rm_qoutes(token_str);
		append_node(&token, token_str);
	}
	shell->tokens = token;
}

int operator_check(char *str, int *input_i)
{
	char *operator = "|<>";
	int i = 0;

	while (operator[i])
	{
		if (str[0] == operator[i])
		{
			if (operator[i] == '$')
			{
				if (!is_whitespace(str[1]))
				{
					*input_i += 1;
					return(1);
				}
				else
					return (0);
			}
			*input_i += 1;
			return(1);
		}
		i++;
	}
	return(0);
}

int is_operator(char *str, int *input_i)
{
	char *operator = "|<>";
	int i = *input_i;
	int j = 0;

	while (operator[j])
	{
		if (str[i] == operator[j])
		{
			if ((str[i] == '<' && str[i+1] == '<') || (str[i] == '>' && str[i+1] == '>')) // how do we handle <| |> <>
				i++;
			*input_i = i + 1;
			return(1);
		}
		j++;
	}
	return(0);
}

int in_qoutes(char *str, int *input_i)
{
	int i = *input_i;
	int start = i;
	if (str[i] != 34 && str[i] != 39)
		return (0);
	i++;
	while(str[i] && (str[i] != str[start]))
		i++;
	if (str[i] != str[start]) // need to check with which quotes it started to know which ones have to close
		ft_error("qoutes not closed", ERR_SYNTAX); // error handle, exit shell
	*input_i = i + 1; // to move behind the quote
	return (1);
}

int is_whitespace(char c)
{
	char *whitespace = " \t\n\v\f\r";
	int i;

	i = 0;
	while (whitespace[i])
	{
		if (c == whitespace[i])
			return(1);
		i++;
	}
	return(0);
}

void print_tokens(t_shell *shell)
{
	int i = 1;
	t_token *temp= shell->tokens;
	while (temp)
	{
		printf("-token%d- str: %s, type: %d\n", i, temp->str, temp->type);
		temp = temp->next;
		i++;
	}
}
