/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:01:47 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/26 14:59:29 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

char	*rm_qoutes(char *str)
{
	int		i;
	int		len;
	char	*re;

	i = 0;
	if (str[i] != 34 && str[i] != 39)
		return (str);
	len = ft_strlen(str) - 2;
	re = (char *)malloc(len);
	re[len] = '\0';
	while (i < len)
	{
		re[i] = str[i + 1];
		i++;
	}
	free(str);
	return (re);
}


char *check_qoutes(char *str, int *q_flag)
{
	int	i;
	int k;
	int start;
	int q_count;
	char *re;
	i = 0;
	q_count = 0;
	
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			start = i;
			i++;
			while(str[i])
			{
				if (str[i] == str[start])
				{
					q_count += 2;
					break;
				}
				i++;
			}
			if (str[i] != str[start])
				ft_error("qoutes not closed", ERR_SYNTAX);
		}
		if (str[i])
			i++;
	}
	if (!q_count)
		return(str);

	re = (char *)malloc(ft_strlen(str) + 1 - q_count);
	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] != 34 && str[i] != 39)
		{
			re[k] = str[i];
			k++;
		}
		else
		{
			start = i;
			i++;
			while(str[i] && str[i] != str[start])
			{
				re[k] = str[i];
				k++;
				i++;
			}
		}
		if (str[i])
			i++;
	}
	re[k] = '\0';
	*q_flag = 1;
	// printf("%d\n", *q_flag);
	// printf("%s\n", re);
	return(re);
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
	start = 0;
	while (str[i])
	{	
		q_flag = 0;
		while (is_whitespace(str[i]))
			i++;
		if (!str[i])
			break ;
		start = i;
		while (str[i] && !is_whitespace(str[i]))
		{
			if (in_qoutes(str, &i))
				break ;
			if (is_operator(str, &i))
				break ;
			else if (operator_check(&str[i + 1], &i))
				break ;
			i++;
		}
		token_str = ft_substr(str, start, i - start);
		token_str = check_qoutes(token_str, &q_flag);
		// token_str = rm_qoutes(token_str);
		append_node(&token, token_str, q_flag);
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
			// if (operator[i] == '$')
			// {
			// 	if (!is_whitespace(str[1]))
			// 	{
			// 		*input_i += 1;
			// 		return(1);
			// 	}
			// 	else
			// 		return (0);
			// }
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
					+ 1] == '>')) // how do we handle <| |> <>
				i++;
			*input_i = i + 1;
			return (1);
		}
		j++;
	}
	return (0);
}

int	in_qoutes(char *str, int *input_i)
{
	int	i;
	int	start;

	i = *input_i;
	start = i;
	if (str[i] != 34 && str[i] != 39)
		return (0);
	i++;
	while (str[i] && (str[i] != str[start]))
		i++;
	if (str[i] != str[start])
		// need to check with which quotes it started to know which ones have to close
		ft_error("qoutes not closed", ERR_SYNTAX); // error handle, exit shell
	*input_i = i + 1;                              // to move behind the quote
	return (in_qoutes(str, input_i));
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
		printf("-token%d- str: %s, type: %d\n", i, temp->str, temp->type);
		temp = temp->next;
		i++;
	}
}
