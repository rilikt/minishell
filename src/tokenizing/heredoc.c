/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:26:35 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/15 23:41:35 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

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

	count = 0;
	count = count_quotes(str, 0, 0);
	if (count == -1)
		return ("\0");
	else if (count == 0)
		return (str);
	re = (char *)malloc(ft_strlen(str) + 1 - count);
	error_check(re, "check_and_rm_quotes", ERR_MALLOC);
	return (create_string(str, re, 0, 0));
}

char	*heredoc_loop(char *delimiter)
{
	char	*line;
	char	*input;

	line = NULL;
	input = NULL;
	while (1 && g_sig != 2)
	{
		if (isatty(STDIN_FILENO))
			line = readline("> ");
		else
			line = use_get_next();
		if (!line || g_sig == 2)
			break ;
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter) + 1)
			&& delimiter[0] != '\0')
			break ;
		line = ms_freejoin(line, "\n");
		input = ms_freejoin(input, line);
		free(line);
		line = NULL;
	}
	if (line)
		free(line);
	free(delimiter);
	return (input);
}

void	is_heredoc(t_token *node, int q_flag)
{
	char	*line;
	char	*input;
	char	*delimiter;
	int		fd;

	if (node->prev->type != IN_HEREDOC || node->type == PIPE || is_redir(node))
		return ;
	g_sig = 666;
	line = NULL;
	input = NULL;
	delimiter = check_and_rm_quotes(node->str);
	input = heredoc_loop(delimiter);
	if (!q_flag)
		node->type = VARIABLE;
	else
		node->type = WORD;
	if (g_sig == 2)
	{
		fd = open("/dev/tty", O_RDWR);
		dup2(fd, STDIN_FILENO);
		input = NULL;
	}
	node->str = input;
	g_sig = 0;
}
