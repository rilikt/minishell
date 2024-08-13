/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:14:56 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/13 13:50:16 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

char	*put_input(int argc, char **argv)
{
	int		i;
	char	*input;
	char	*tmp;
	char	*tmp2;

	i = 1;
	input = NULL;
	tmp = NULL;
	tmp2 = NULL;
	if (argc > 1)
	{
		while (i < argc)
		{
			tmp2 = ft_strjoin(tmp, argv[i++]);
			if (tmp)
				free(tmp);
			tmp = ft_strjoin(tmp2, " ");
			free(tmp2);
			input = tmp;
		}
		printf("%s\n", input);
	}
	return (input);
}

void	change_shlvl(t_shell *shell, char **envp)
{
	char	*shlvl[3];
	char	*tmp;
	int		nb;

	nb = 0;
	shlvl[0] = "export";
	shlvl[2] = NULL;
	shlvl[1] = ft_getenv("SHLVL", envp);
	if (shlvl[1])
		nb = ft_atoi(shlvl[1]);
	nb += 1;
	tmp = ft_itoa(nb);
	shlvl[1] = ft_strjoin("SHLVL=", tmp);
	free(tmp);
	export(shlvl, &shell->envp);
	free(shlvl[1]);
}

void	setup_shell(t_shell *shell, char **envp, int argc, char **argv)
{
	shell->envp = copy_env(envp);
	shell->input = put_input(argc, argv);
	shell->tokens = NULL;
	shell->char_vars = NULL;
	shell->int_vars = NULL;
	shell->commands = NULL;
	shell->cmd_nb = 0;
	shell->exitstatus = 0;
	shell->err = 0;
	change_shlvl(shell, envp);
}
