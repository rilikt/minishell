/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:22:38 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/16 16:53:50 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	expand_string(char **str, int type, t_exp *utils, int i)
{
	int		tmp;
	char	*pos;

	tmp = 0;
	utils->v_count = 0;
	utils->str = str;
	if (type != IN_HEREDOC)
	{
		while (str[0][tmp])
		{
			if (str[0][tmp] == '$')
			{
				pos = *str + tmp;
				handle_var(i, &pos, &tmp, utils);
				utils->v_count++;
			}
			else
				tmp++;
		}
	}
	else
		expand_heredoc(str, utils);
	return ;
}

int	expand_redirects(t_rdct *reds, t_exp *utils)
{
	t_rdct	*tmp;
	char	*f_name;

	tmp = reds;
	utils->arg_vars = (t_avars *)malloc(sizeof(t_avars) * 1);
	error_check(utils->arg_vars, "expand_redirects", ERR_MALLOC);
	f_name = ms_strdup(tmp->filename);
	while (tmp)
	{
		if (tmp->char_vars)
		{
			utils->arg_vars->type = tmp->char_vars;
			utils->arg_vars->s_index = tmp->int_vars;
			utils->arg_vars->e_index = tmp->int_vars;
			expand_string(&tmp->filename, tmp->type, utils, 0);
			if (ft_strchr(tmp->filename, ' ') && tmp->type != IN_HEREDOC)
				return (ft_error(f_name, "ambiguous redirect", 0),
					free(utils->arg_vars), free(f_name), 2);
		}
		tmp = tmp->next;
	}
	return (free(utils->arg_vars), free(f_name), 0);
}

void	check_removal(char **args, int i, char *type, int *a)
{
	int		len;

	if (!*args[i] && !ft_strchr(type, '2') && *type)
	{
		len = ft_arr_len(args);
		free(args[i]);
		while (i < len)
		{
			args[i] = args[i + 1];
			i++;
		}
		(*a)--;
	}
}

int	expand_cmd(t_cmd *cmd, int exitstatus, char **envp)
{
	int		i;
	int		a;
	int		arg_len;
	t_exp	utils;

	i = -1;
	a = -1;
	arg_len = ft_arr_len(cmd->args);
	utils.envp = envp;
	utils.exit = exitstatus;
	if (cmd->char_vars)
	{
		setup_help_struct(cmd, &utils, arg_len, 0);
		while (cmd->char_vars && cmd->args[++i] && ++a >= 0)
		{
			expand_string(&cmd->args[i], 0, &utils, a);
			check_removal(cmd->args, i, utils.arg_vars[a].type, &a);
			if (a >= 0 && ft_strchr(utils.arg_vars[a].type, '1'))
				cmd->args = split_arg(cmd->args, utils.arg_vars, &i, a);
		}
		free_arg_vars(&utils, arg_len);
	}
	if (cmd->reds)
		return (expand_redirects(cmd->reds, &utils));
	return (0);
}
