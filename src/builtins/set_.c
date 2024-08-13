/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:25:13 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/13 13:05:44 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void set_last_arg(t_cmd *cmd, char ***envp, int mode)
{
	int i;
	char *ex[3];

	if (mode)
	{
		while(cmd->next)
			cmd = cmd->next;
	}
	ex[0] = "export";
	i = 0;
	while(cmd->args[i])
		i++;
	i--;
	ex[1] = ft_strjoin("_=", cmd->args[i]);
	ex[2] = NULL;
	export(ex, envp);
}