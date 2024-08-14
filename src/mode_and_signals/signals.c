/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:56:00 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/14 11:49:49 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	signal_handler(int signal)
{
	if (g_sig == 0)
	{
		write(STDIN_FILENO, "\n", 1);
		return ;
	}
	if (g_sig == 42)
	{
		write(STDIN_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
	if (g_sig == 666)
	{
		write(STDIN_FILENO, "\n", 1);
		close(STDIN_FILENO);
		g_sig = signal;
		return ;
	}
}

void	check_mode_handle_signals(t_shell *shell)
{
	int fd[2];

	fd[0] = isatty(STDIN_FILENO);
	fd[1] = isatty(STDERR_FILENO);
	if (fd[0] && fd[1] && !shell->input)
		shell->mode = INTERACTIVE;
	else
		shell->mode = NON_INTERACTIVE;
	tcgetattr(STDIN_FILENO, &shell->term[0]);
	shell->term[1] = shell->term[0];
	if (shell->mode == INTERACTIVE)
	{
		shell->term[1].c_lflag &= ~ECHOCTL;
		tcsetattr(STDIN_FILENO, TCSANOW, &shell->term[1]);
		shell->signals.sa_handler = SIG_IGN;
		sigemptyset(&shell->signals.sa_mask);
		shell->signals.sa_flags = 0;
		sigaction(SIGQUIT, &shell->signals, NULL);
	}
	signal(SIGINT, signal_handler);
	return ;
}
