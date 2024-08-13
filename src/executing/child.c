/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:37:42 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/13 16:38:22 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

char	*path_check(t_cmd *cmd, t_shell *shell)
{
	char	*path_to_cmd;

	if (!access(cmd->args[0], F_OK) && !access(cmd->args[0], X_OK))
	{
		path_to_cmd = ms_strdup(cmd->args[0]);
		cmd->args[0] = ms_strdup(ft_strrchr(cmd->args[0], '/'));
	}
	else
	{
		if (ft_strchr(cmd->args[0], '/'))
			ft_error(NULL, cmd->args[0], ERR_FILE);
		path_to_cmd = get_path(ft_strjoin("/", cmd->args[0]), shell);
		if (!path_to_cmd)
		{
			ft_error(path_to_cmd, cmd->args[0], ERR_PATH);
			shell->err = ERR_PATH;
		}
	}
	return (path_to_cmd);
}

void	run_childprocess(t_cmd *cmd, t_pipe *pipes, t_shell *shell, int mode)
{
	char	*path_to_cmd;
	int		err;

	path_to_cmd = NULL;
	err = 0;
	signal(SIGINT, &exit);
	change_std_fd(pipes, mode);
	if (shell->cmd_nb > 1)
	{
		cmd->stdout_fd = -1;
		cmd->stdin_fd = -1;
		err = expand_cmd(cmd, shell->exitstatus, shell->envp);
		check_builtins(cmd);
	}
	redirect_accordingly(cmd->reds);
	if (cmd->builtin_flag == EXTERN && cmd->args)
		path_to_cmd = path_check(cmd, shell);
	if (cmd->builtin_flag != EXTERN)
		exit(check_and_exec_builtins(cmd, &shell->envp, &shell->err,
				shell->exitstatus));
	if (!cmd->args || !cmd->args[0])
		exit(0);
	set_last_arg(cmd, &shell->envp, 0);
	if (path_to_cmd)
		execve(path_to_cmd, cmd->args, shell->envp);
	exit(shell->err);
}

char	*get_path(char *cmd, t_shell *shell)
{
	int		i;
	char	**path;
	char	*path_string;
	char	*tmp;
	char	*tmp2;

	i = -1;
	path_string = ft_getenv("PATH", shell->envp);
	if (path_string)
		return (free(cmd), NULL);
	path = ms_split(path_string, ':');
	while (path[++i])
	{
		tmp = ms_strjoin(path[i], cmd);
		if (access(tmp, X_OK) == 0)
		{
			free_string_array(path);
			return (tmp);
		}
		free(tmp);
	}
	free(cmd);
	free_string_array(path);
	return (NULL);
}
