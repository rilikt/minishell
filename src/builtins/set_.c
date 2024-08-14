/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 15:25:13 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/14 11:48:10 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	set_last_arg(t_cmd *cmd, char ***envp, int mode)
{
	int i;
	char *ex[3];

	if (mode)
	{
		while (cmd->next)
			cmd = cmd->next;
	}
	ex[0] = "export";
	i = 0;
	if (cmd->args && cmd->args[i])
	{
		while (cmd->args[i])
		{
			i++;
		}
		i--;
		ex[1] = ft_strjoin("_=", cmd->args[i]);
	}
	else
		ex[1] = ft_strjoin("_=", "");
	ex[2] = NULL;
	export(ex, envp);
}