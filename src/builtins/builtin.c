/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:48:00 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/14 12:22:48 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	single_cmd_check(t_shell *shell)
{
	shell->commands->stdout_fd = -1;
	shell->commands->stdin_fd = -1;
	shell->err = expand_cmd(shell->commands, shell->exitstatus, shell->envp);
	check_builtins(shell->commands);
	if (shell->commands->builtin_flag == EXTERN)
		return (0);
	else
	{
		if (shell->commands->reds)
		{
			shell->commands->stdout_fd = dup(STDOUT_FILENO);
			shell->commands->stdin_fd = dup(STDIN_FILENO);
		}
		redirect_accordingly(shell->commands->reds, &shell->err);
	}
	return (1);
}

int	check_and_exec_builtins(t_shell *shell)
{
	int	exit_re;

	exit_re = 0;
	set_last_arg(shell->commands, &shell->envp, 0);
	if (shell->commands->builtin_flag == FT_ECHO)
		exit_re = echo(shell->commands->args);
	else if (shell->commands->builtin_flag == CD)
		exit_re = cd(shell->commands->args, &shell->envp);
	else if (shell->commands->builtin_flag == PWD)
		exit_re = pwd(shell->commands->args);
	else if (shell->commands->builtin_flag == EXPORT)
		exit_re = export(shell->commands->args, &shell->envp);
	else if (shell->commands->builtin_flag == UNSET)
		exit_re = unset(shell->commands->args, &shell->envp);
	else if (shell->commands->builtin_flag == ENV)
		exit_re = env(shell->commands->args, shell->envp);
	else if (shell->commands->builtin_flag == EXIT)
		exit_re = ft_exit(shell->commands->args, &shell->err, shell->exitstatus);
	if (shell->commands->stdout_fd > -1)
	{
		ft_dup2(shell->commands->stdout_fd, STDOUT_FILENO, "dup21");
		ft_close(shell->commands->stdout_fd, "close1");
	}
	if (shell->commands->stdin_fd > -1)
	{
		ft_dup2(shell->commands->stdin_fd, STDIN_FILENO, "dup22");
		ft_close(shell->commands->stdin_fd, "close2");
	}
	return (exit_re);
}

void	check_builtins(t_cmd *cmd)
{
	char	*arr[8];
	int		i;

	i = 0;
	cmd->builtin_flag = NOT_SET;
	arr[0] = "echo";
	arr[1] = "cd";
	arr[2] = "pwd";
	arr[3] = "export";
	arr[4] = "unset";
	arr[5] = "env";
	arr[6] = "exit";
	arr[7] = NULL;
	while (i < 7)
	{
		if (!cmd->args)
			cmd->builtin_flag = NO_CMD;
		if (cmd->args && cmd->args[0] && !ft_strncmp(cmd->args[0], arr[i],
				ft_strlen(arr[i]) + 1))
			cmd->builtin_flag = i;
		i++;
	}
	if (cmd->builtin_flag == NOT_SET)
		cmd->builtin_flag = EXTERN;
	return ;
}
// $USER pstrohal text  ' text
// $USER pstrohal text  ' text