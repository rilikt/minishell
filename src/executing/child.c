/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:37:42 by pstrohal          #+#    #+#             */
/*   Updated: 2024/07/16 16:27:12 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"



void	run_childprocess(t_cmd *cmd, t_pipe *pipes, t_shell *shell, int mode)
{
	char *path_to_cmd;

	change_std_fd(pipes, mode);
	expand_cmd(cmd, shell->envp, shell->exitstatus);
	check_builtins(cmd, shell->envp);
	get_path(&path_to_cmd, shell->envp, cmd->args[0]);
	redirect_accordingly(cmd->reds);
	execve(path_to_cmd, cmd->args, shell->envp);
	perror(cmd->args[0]);
	return (close(STDIN_FILENO), close(STDOUT_FILENO), exit(0));
}
