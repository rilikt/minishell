/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:37:42 by pstrohal          #+#    #+#             */
/*   Updated: 2024/07/19 18:10:38 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	check_and_exec_builtins(t_cmd *cmd, char **envp)
{
	if (cmd->builtin_flag == ECHO)
		echo(cmd->args);
	else if (cmd->builtin_flag == CD)
		cd(cmd);
	else if (cmd->builtin_flag == PWD)
		pwd(cmd);
	else if (cmd->builtin_flag == EXPORT)
		cd(cmd);
	else if (cmd->builtin_flag == UNSET)
		cd(cmd);
	else if (cmd->builtin_flag == ENV)
		cd(cmd);
	else if (cmd->builtin_flag == EXIT)
		cd(cmd);
}

void	run_childprocess(t_cmd *cmd, t_pipe *pipes, t_shell *shell, int mode)
{
	char	*path_to_cmd;

	change_std_fd(pipes, mode);
	expand_cmd(cmd, shell->exitstatus);
	check_builtins(cmd, shell->envp);
	if (cmd->builtin_flag == EXTERN)
		path_to_cmd = get_path(cmd->args[0]);
	if (!path_to_cmd)
		error_return("");
	redirect_accordingly(cmd->reds);
	check_and_exec_builtins(cmd, shell->envp);
	execve(path_to_cmd, cmd->args, shell->envp);
	error_return();
	return (close(STDIN_FILENO), close(STDOUT_FILENO), exit(0));
}

void	check_builtins(t_cmd *cmd, char **envp)
{
	char	arr[8];
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
		if (!ft_strncmp(cmd->args[0], arr[i], ft_strlen(arr[i]) + 1))
			cmd->builtin_flag = i;
	}
	if (cmd->builtin_flag == NOT_SET)
		cmd->builtin_flag = EXTERN;
	return;
}

char *get_path(char *cmd)
{
	int		i;
	char	**path;
	char	*tmp;

	i = 0;
	*path = getenv("PATH");
	if (!*path)
		error_return();
	path = ft_split(*path, ":");
	while(path[i])
	{
		tmp = ft_strjoin(path[i], cmd);
		if (access(tmp, X_OK))
		{
			free(tmp);
			return(NULL);
		}
		i++;
	}
	return (tmp);
} 
