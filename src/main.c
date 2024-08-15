/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:17:27 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/15 18:40:26 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int	g_sig = 0;

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	setup_shell(&shell, envp, argc, argv);
	check_mode_handle_signals(&shell);
	while (shell.err != ERR_EXIT)
	{
		shell.err = 0;
		if (!shell.input)
			shell.input = read_input(shell.mode, &shell);
		if (!shell.err)
			tokenize(&shell);
		// print_tokens(&shell);
		if (!shell.err)
			parse_tokens(&shell);
		// print_commands(&shell);
		if (!shell.err && shell.cmd_nb == 1
			&& single_cmd_check(&shell))
			shell.exitstatus = check_and_exec_builtins(shell.commands, &shell);
		else if (!shell.err)
			execute_commandline(&shell);
		free_tokens(&shell);
		free_struct(&shell);
		free(shell.input);
		shell.input = NULL;
	}
	free_string_array(shell.envp);
	if (shell.mode == INTERACTIVE)
		tcsetattr(STDIN_FILENO, TCSANOW, &(shell.term[0]));
	return (shell.exitstatus);
}
