/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:39:58 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/06 15:42:44 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	check_whitespace(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != '\n')
	{
		if (input[i] > 32)
			return (0);
		i++;
	}
	return (1);
}

char	*read_input(int mode, t_shell *shell)
{
	char	*input;
	char	path[1024];
	char	*rl_str;
	char	*tmp;

	input = NULL;
	getcwd(path, sizeof(path));
	rl_str = ft_strjoin(path, " > ");
	error_check(rl_str, "strjoin in read_inut", ERR_MALLOC);
	tmp = ft_strdup((ft_strrchr(rl_str, '/') + 1));
	error_check(tmp, "strdup in read_inut", ERR_MALLOC);
	free(rl_str);
	rl_str = ft_strjoin("🐚 ", tmp);
	free(tmp);
	error_check(rl_str, "strjoin in read_inut", ERR_MALLOC);
	if (mode == INTERACTIVE)
	{
		if (sig == 0)
		{	write(STDIN_FILENO, rl_str, ft_strlen(rl_str));
			input = get_next_line(STDIN_FILENO);}
		else
			rl_replace_line("", 1);
			write(STDIN_FILENO, "\n", 1);
			rl_on_new_line();
			rl_redisplay();
	}
	else if (mode == NON_INTERACTIVE && !isatty(STDIN_FILENO))
	{
		tmp = get_next_line(STDIN_FILENO);
		if (tmp)
			input = ft_substr(tmp, 0, ft_strlen(tmp) - 1);
		free(tmp);
	}
	if (!input)
	{
		if (shell->mode == INTERACTIVE)
			tcsetattr(STDIN_FILENO, TCSANOW, &(shell->term[0]));
		free_string_array(shell->envp);
		free_struct(shell);
		free(rl_str);
		exit(shell->exitstatus);
	}
	if (check_whitespace(input))
	{
		free(input);
		input = read_input(mode, shell);
	}
	free(rl_str);
	rl_str = NULL;
	add_history(input);
	return (input);
}
