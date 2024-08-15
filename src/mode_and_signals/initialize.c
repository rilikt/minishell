/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 17:14:56 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/14 18:51:05 by timschmi         ###   ########.fr       */
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
			tmp2 = ms_strjoin(tmp, argv[i++]);
			input = ms_strjoin(tmp2, " ");
			free(tmp2);
			if (i != argc - 1)
				free(tmp);
			input = tmp;
		}
	}
	return (input);
}

void	initial_export(t_shell *shell)
{
	char	*var[3];
	char	path[1024];
	char	*tmp;
	int		nb;

	nb = 0;
	var[0] = "export";
	var[1] = getcwd(path, sizeof(path));
	var[1] = ms_strjoin("PWD=", var[1]);
	var[2] = NULL;
	export(var, &shell->envp);
	free(var[1]);
	var[1] = ft_getenv("SHLVL", shell->envp);
	if (var[1])
		nb = ft_atoi(var[1]);
	nb += 1;
	tmp = ft_itoa(nb);
	var[1] = ms_strjoin("SHLVL=", tmp);
	free(tmp);
	export(var, &shell->envp);
	free(var[1]);
}

void	setup_shell(t_shell *shell, char **envp, int argc, char **argv)
{
	int	i;

	i = 0;
	shell->envp = copy_env(envp);
	shell->input = put_input(argc, argv);
	shell->tokens = NULL;
	shell->char_vars = NULL;
	shell->int_vars = NULL;
	shell->commands = NULL;
	shell->cmd_nb = 0;
	shell->exitstatus = 0;
	shell->err = 0;
	initial_export(shell);
}
