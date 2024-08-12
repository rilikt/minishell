/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:37:42 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/12 11:46:58 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

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
		err = expand_cmd(cmd, shell->exitstatus, shell->envp);
		check_builtins(cmd);
	}
	redirect_accordingly(cmd->reds);
	if (cmd->builtin_flag == EXTERN && cmd->args)
	{
		if (!access(cmd->args[0], F_OK) && !access(cmd->args[0], X_OK))
		{
			path_to_cmd = ft_strdup(cmd->args[0]);
			cmd->args[0] = ft_strdup(ft_strrchr(cmd->args[0], '/'));
			error_check(cmd->args[0], "strdup in run_childprocess", ERR_MALLOC);
		}
		else
		{
			if (ft_strchr(cmd->args[0], '/'))
				error_check(NULL, cmd->args[0], ERR_FILE);
			path_to_cmd = get_path(ft_strjoin("/", cmd->args[0]), shell->envp);
			error_check(path_to_cmd, cmd->args[0], ERR_PATH);
		}
	}
	if (cmd->builtin_flag != EXTERN)
		exit(check_and_exec_builtins(cmd, &shell->envp, &shell->err, shell->exitstatus));
	if (!cmd->args || !cmd->args[0])
		exit(0);
	set_last_arg(cmd, &shell->envp, 0);
	execve(path_to_cmd, cmd->args, shell->envp);
	exit(1);
}

char *get_path(char *cmd, char **envp)
{
	int		i;
	char	**path;
	char	*path_string;
	char	*tmp;
	char	*tmp2;

	i = 0;
	error_check(cmd, "ft_strjoin", ERR_MALLOC);
	path_string = ft_getenv("PATH", envp);
	error_check(path_string, "PATH not valid env variable", ERR_PATH);
	path = ft_split(path_string, ':');
	error_check(path, "ft_split", ERR_MALLOC);
	while(path[i])
	{
		tmp = ft_strjoin(path[i], cmd);
		error_check(tmp, "ft_strjoin", ERR_MALLOC);
		if (access(tmp, X_OK) == 0)
		{
			free_string_array(path);
			return(tmp);
		}
		free(tmp);
		i++;
	}
	free(cmd);
	free_string_array(path);
	return (NULL);
}
	// printf("hallo\n");
