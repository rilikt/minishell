/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:17:27 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/26 15:59:31 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	sig = 0;

void setup_shell(t_shell *shell, char **envp)
{
	char	*shlvl;
	int		nb;

	sig = 0;
	shell->envp = copy_env(envp);
	shell->input = NULL;
	shell->tokens = NULL;
	shell->commands = NULL;
	shell->cmd_nb = 0;
	shell->exitstatus = 0;
	shell->err = 0;
	shlvl = getenv("SHLVL");
	if (shlvl)
	{
			nb = ft_atoi(shlvl);
			nb += 1;
			ft_itoa(nb);
	}
}
int main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	setup_shell(&shell, envp);
	check_mode_handle_signals(&shell);
	while(shell.err != ERR_EXIT)
	{
		shell.input = read_input();
		if (!shell.err)
			tokenize(&shell);
		if (!shell.err)
			parse_tokens(&shell);
		// print_commands(&shell);
		if (!shell.err && shell.cmd_nb == 1 &&
			single_cmd_check(shell.commands, shell.exitstatus))
			check_and_exec_builtins(shell.commands, &shell.envp, &shell.err);	
		else if (!shell.err)
			execute_commandline(&shell);
		// clean_shell(&shell);
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &shell.term[0]);
	return (0);
}
