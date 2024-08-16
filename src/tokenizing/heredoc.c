/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:26:35 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/16 15:01:42 by timschmi         ###   ########.fr       */
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
	while (1 && legit_variable(0, 0) != 2)
	{
		if (isatty(STDIN_FILENO))
			line = readline("> ");
		else
			line = use_get_next();
		if (!line || legit_variable(0, 0) == 2)
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
	char	*input;
	char	*delimiter;
	int		fd;

	if (node->prev->type != IN_HEREDOC || node->type == PIPE || is_redir(node))
		return ;
	legit_variable(1, 666);
	delimiter = check_and_rm_quotes(node->str);
	input = heredoc_loop(delimiter);
	if (!q_flag)
		node->type = VARIABLE;
	else
		node->type = WORD;
	if (legit_variable(0, 0) == 2)
	{
		fd = open("/dev/tty", O_RDWR);
		if (fd < 0)
			ft_error(NULL, "open failed in heredoc", ERR_OPEN);
		ft_dup2(fd, STDIN_FILENO, "heredoc");
		if (input)
			free(input);
		input = NULL;
	}
	node->str = input;
	legit_variable(1, 0);
}
