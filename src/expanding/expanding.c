/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:22:38 by pstrohal          #+#    #+#             */
/*   Updated: 2024/07/16 18:15:18 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"
char	*get_var(char *pos, char **envp)
{
	char	*tmp;

	tmp = pos + 1;
	while (tmp && tmp != '')
}

void	insert_var(char *str, char *pos, char *var_value)
{
	int	i;

	i = 0;
}

void	expand_string(char *str, char **envp, int exitstatus)
{
	char	*tmp;
	char	*var_value;

	tmp = ft_strchr(str, '$');
	while (tmp)
	{
		if ((tmp + 1) == '?')
			var_value = ft_itoa(exitstatus);
		else
			var_value = get_var(tmp, envp);
		insert_var(str, tmp, var_value);
		tmp = ft_strchr(str, '$');
	}
}

void	expand_args(char **args, char **envp, int exitstatus, int count)
{
	int		i;
	char	*tmp;

	i = 0;
	while (args[i])
	{
		expand_string(args[i], envp, exitstatus);
		if (i == 0 && ft_strchr(args[0], ' '))
			split_and_arrange(args[0]);
		i++;
	}
	return ;
}

void	expand_red(t_rdct *reds, char **envp, int exitstatus, int count)
{
	while (reds)
	{
		expand_string(reds->filename, envp, exitstatus);
		reds = reds->next;
	}
}

void	expand_cmd(t_cmd *cmd, char **envp, int exitstatus)
{
	
	if (cmd->is_var > 0)
		expand_arg(cmd->args, envp, exitstatus, cmd->is_var);
	if (cmd->var_in_redir > 0)
		expand_red(cmd->reds, envp, exitstatus, cmd->var_in_redir);
	return ;
}
