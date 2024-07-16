/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 18:37:42 by pstrohal          #+#    #+#             */
/*   Updated: 2024/07/16 11:19:43 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"



void	run_childprocess(t_cmd *cmd, t_pipe *pipes, char **envp, int mode)
{
	change_std_fd(pipes, mode);
	
	

	return (close(STDIN_FILENO), close(STDOUT_FILENO), exit(0));
}
