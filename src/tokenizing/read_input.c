/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:39:58 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/16 15:00:50 by timschmi         ###   ########.fr       */
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

char	*use_get_next(void)
{
	char	*tmp;
	char	*input;

	tmp = NULL;
	input = NULL;
	tmp = get_next_line(STDIN_FILENO);
	if (tmp)
		input = ms_substr(tmp, 0, ft_strlen(tmp) - 1);
	free(tmp);
	return (input);
}

char	*setup_prompt(void)
{
	char	*tmp;
	char	*rl_str;
	char	path[1024];

	tmp = NULL;
	rl_str = NULL;
	getcwd(path, sizeof(path));
	rl_str = ms_strjoin(path, " > ");
	tmp = ms_strdup((ft_strrchr(rl_str, '/') + 1));
	free(rl_str);
	rl_str = ms_strjoin("🐚 ", tmp);
	free(tmp);
	return (rl_str);
}

char	*read_input(int mode, t_shell *shell)
{
	char	*input;
	char	*rl_str;

	legit_variable(1, 42);
	input = NULL;
	rl_str = setup_prompt();
	if (mode == INTERACTIVE)
		input = readline(rl_str);
	else if (mode == NON_INTERACTIVE && !isatty(STDIN_FILENO))
		input = use_get_next();
	if (!input)
	{
		if (shell->mode == INTERACTIVE)
			tcsetattr(STDIN_FILENO, TCSANOW, &(shell->term[0]));
		exit(shell->exitstatus);
	}
	if (check_whitespace(input))
	{
		free(input);
		input = read_input(mode, shell);
	}
	free(rl_str);
	add_history(input);
	legit_variable(1, 0);
	return (input);
}
