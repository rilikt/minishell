/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:17:27 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/21 14:39:03 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

// void	signal_handle(int signal)
// {
	
// }

// void	check_mode_handle_signals(t_shell *shell)
// {
// 	if (isatty(STDIN_FILENO) && isatty(STDERR_FILENO))
// 		shell->mode = INTERACTIVE;
// 	else
// 		shell->mode = NON_INTERACTIVE;
// 	shell->signals.sa_handler = &signal_handler;
	
// }

void setup_shell(t_shell *shell, char **envp)
{
	shell->envp = envp;
	shell->input = NULL;
	shell->tokens = NULL;
	shell->commands = NULL;
	shell->cmd_nb = 0;
	shell->exitstatus = 0;
}
int main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	setup_shell(&shell, envp);
	// check_mode_handle_signals(&shell);
	go_home();
	while(1)
	{
		shell.input = read_input();
		tokenize(&shell);
		print_tokens(&shell);
		parse_tokens(&shell);
		print_commands(&shell);
		if (shell.cmd_nb == 1 && single_cmd_check(shell.commands, shell.exitstatus))
			check_and_exec_builtins(shell.commands, shell.envp);
		else
			execute_commandline(&shell);
		// clean_shell(&shell);
	}


	return (0);
}
