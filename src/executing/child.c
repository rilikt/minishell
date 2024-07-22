/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:37:42 by pstrohal          #+#    #+#             */
/*   Updated: 2024/07/22 18:55:59 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	run_childprocess(t_cmd *cmd, t_pipe *pipes, t_shell *shell, int mode)
{
	char	*path_to_cmd;

	path_to_cmd = NULL;
	// printf("[0]:%d, [1]:%d, last:%d\n", pipes->pipe[0], pipes->pipe[1], pipes->last_pipe);
	change_std_fd(pipes, mode);
	expand_cmd(cmd, shell->exitstatus);
	check_builtins(cmd);
	if (cmd->builtin_flag == EXTERN)
	{
		path_to_cmd = get_path(ft_strjoin("/", cmd->args[0]));
		error_check(path_to_cmd, cmd->args[0], ERR_PATH);
	}
	redirect_accordingly(cmd->reds);
	if (cmd->builtin_flag != EXTERN)
		check_and_exec_builtins(cmd, shell->envp, &shell->err);
	execve(path_to_cmd, cmd->args, shell->envp);
	// error_check
	return (close(STDIN_FILENO), close(STDOUT_FILENO), exit(1));
}

char *get_path(char *cmd)
{
	int		i;
	char	**path;
	char	*path_string;
	char	*tmp;
	char	*tmp2;

	i = 0;
	error_check(cmd, "ft_strjoin", ERR_MALLOC);
	path_string = getenv("PATH");
	error_check(path, "PATH not valid env variable", ERR_PATH);
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
