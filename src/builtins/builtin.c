/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 12:48:00 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/05 18:42:43 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	single_cmd_check(t_cmd *cmd, int exitstatus, char **envp)
{
	cmd->stdout_fd = -1;
	cmd->stdin_fd = -1;
	expand_cmd(cmd, exitstatus, envp);
	check_builtins(cmd);
	if (cmd->builtin_flag == EXTERN)
		return(0);
	else
	{
		if (cmd->reds)
		{
			cmd->stdout_fd = dup(STDOUT_FILENO);
			cmd->stdin_fd = dup(STDIN_FILENO);
		}
		redirect_accordingly(cmd->reds);
	}
	return(1);
}

int	check_and_exec_builtins(t_cmd *cmd, char ***envp, int *err)
{
	if (cmd->builtin_flag == FT_ECHO)
		echo(cmd->args);
	else if (cmd->builtin_flag == CD)
		cd(cmd->args, envp);
	else if (cmd->builtin_flag == PWD)
		pwd(cmd->args);
	else if (cmd->builtin_flag == EXPORT)
		export(cmd->args, envp);
	else if (cmd->builtin_flag == UNSET)
		unset(cmd->args, envp);
	else if (cmd->builtin_flag == ENV)
		env(cmd->args, *envp);
	else if (cmd->builtin_flag == EXIT)
		*err = ERR_EXIT;
	if (cmd->stdout_fd > -1)
	{
		ft_dup2(cmd->stdout_fd, STDOUT_FILENO, "dup2 in check_and_exec_builtins");
		ft_close(cmd->stdout_fd, "close1 in check_and_exec_builtins");
	}
	if (cmd->stdin_fd)
	{
		ft_dup2(cmd->stdin_fd, STDIN_FILENO, "dup2 in check_and_exec_builtins");
		ft_close(cmd->stdin_fd, "close2 in check_and_exec_builtins");
	}
	return (0);
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