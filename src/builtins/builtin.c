/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:48:00 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/12 20:32:39 by pstrohal         ###   ########.fr       */
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
		return(0);
	else
	{
		if (shell->commands->reds)
		{
			shell->commands->stdout_fd = dup(STDOUT_FILENO);
			shell->commands->stdin_fd = dup(STDIN_FILENO);
		}
		redirect_accordingly(shell->commands->reds);
	}
	return(1);
}

int	check_and_exec_builtins(t_cmd *cmd, char ***envp, int *err, int exitstatus)
{
	int exit_re;

	exit_re = 0;
	set_last_arg(cmd, envp, 0);
	if (cmd->builtin_flag == FT_ECHO)
		exit_re = echo(cmd->args);
	else if (cmd->builtin_flag == CD)
		exit_re = cd(cmd->args, envp);
	else if (cmd->builtin_flag == PWD)
		exit_re = pwd(cmd->args);
	else if (cmd->builtin_flag == EXPORT)
		exit_re = export(cmd->args, envp);
	else if (cmd->builtin_flag == UNSET)
		exit_re = unset(cmd->args, envp);
	else if (cmd->builtin_flag == ENV)
		exit_re = env(cmd->args, *envp);
	else if (cmd->builtin_flag == EXIT)
		exit_re = ft_exit(cmd->args, err, exitstatus);
	if (cmd->stdout_fd > -1)
	{
		printf("%s: stdout_fd is %d\n", cmd->args[0], cmd->stdout_fd);
		ft_dup2(cmd->stdout_fd, STDOUT_FILENO, "dup2 in check_and_exec_builtins");
		ft_close(cmd->stdout_fd, "close1 in check_and_exec_builtins");
	}
	if (cmd->stdin_fd > -1)
	{
		printf("%s: stdin_fd is %d\n", cmd->args[0], cmd->stdout_fd);
		ft_dup2(cmd->stdin_fd, STDIN_FILENO, "dup2 in check_and_exec_builtins");
		ft_close(cmd->stdin_fd, "close2 in check_and_exec_builtins");
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
		if (cmd->args && cmd->args[0] && !ft_strncmp(cmd->args[0],
			arr[i], ft_strlen(arr[i]) + 1))
			cmd->builtin_flag = i;
		i++;
	}
	if (cmd->builtin_flag == NOT_SET)
		cmd->builtin_flag = EXTERN;
	return;
}
// $USER pstrohal text  ' text
// $USER pstrohal text  ' text