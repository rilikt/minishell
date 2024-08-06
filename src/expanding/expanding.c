/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:22:38 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/06 09:40:19 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

char	*get_var(char *pos, char **var_name, t_exp_help *utils)
{
	char	*tmp;
	char	*var_value;

	var_value = NULL;
	if (!pos)
		return (NULL);
	tmp = pos + 1;
	if (*tmp == '?')
		var_value = ft_itoa(utils->exit);
	*var_name = ft_substr(pos, 1, utils->vars.i_vars[utils->count]);
	tmp++;
	if (!var_value)
		var_value = ft_getenv(*var_name, utils->envp);
	utils->count++;
	return (var_value);
}

void	insert_var(char **str, char *pos, char *var_value, char *var_name)
{
	char	*new_str;
	int		new_len;
	char	*var_end;

	var_end = pos + ft_strlen(var_name) + 1;
	new_len = ft_strlen(*str) - (ft_strlen(var_name) + 1)
		+ ft_strlen(var_value);
	new_str = (char *)malloc(sizeof(char) * new_len + 1);
	int k = pos - *str + 1;
	ft_strlcpy(new_str, *str, pos - *str + 1);
	ft_strlcpy(&(new_str[ft_strlen(new_str)]), var_value,
		ft_strlen(var_value) + 1);
	ft_strlcpy(&(new_str[ft_strlen(new_str)]), var_end, ft_strlen(var_end) + 1);
	free(var_name);
	free(*str);
	*str = new_str;
	return ;
}

void	expand_string(char **str, t_exp_help *utils, int i)
{
	int		tmp;
	char	*pos;
	char	*value;
	char	*name;

	tmp = 0;
	pos = ft_strchr(&(*str[tmp]), '$');
	while (pos)
	{
		tmp = pos - *str;
		check_char_behind(&pos, str, &tmp, utils);
		value = get_var(pos, &name, utils);
		if (pos && utils->vars.c_vars)
		{
			if (!value)
				ft_memmove(pos, pos + ft_strlen(name) + 1, ft_strlen(pos + ft_strlen(name)) + 1);
			else
				insert_var(str, pos, value, name);
			tmp += ft_strlen(value);
		}
		else if (pos)
			tmp += ft_strlen(name);
		if (pos)
			pos = ft_strchr(&str[0][tmp], '$');
		if (utils->vars.c_vars[utils->count - 1] == '2')
			*utils->arg_vars.i_vars = tmp;
	}
	if (i == 0)
		utils->arg_vars.c_vars[utils->count] = '\0';
}
void	expand_cmd(t_cmd *cmd, int exitstatus, char **envp)
{
	int				i;
	t_rdct			*tmp;
	t_exp_help	utils;

	i = -1;
	utils.count = 0;
	utils.envp = envp;
	utils.vars.c_vars = cmd->char_vars;
	utils.vars.i_vars = cmd->int_vars;
	utils.arg_vars.c_vars = ft_strdup(cmd->char_vars);
	error_check(utils.arg_vars.c_vars, "ft_strdup in expand_cmd", ERR_MALLOC);
	utils.arg_vars.i_vars = (int *)malloc(ft_strlen(cmd->char_vars) * sizeof(int));
	error_check(utils.arg_vars.i_vars, "ft_malloc in expand_cmd", ERR_MALLOC);
	while (cmd->char_vars && cmd->char_vars[++i])
		utils.vars.i_vars[i] = cmd->int_vars[i];
	i = 0;
	utils.exit = exitstatus;
	while (cmd->char_vars && cmd->args[i])
	{
		expand_string(&cmd->args[i], &utils, i);
		if (i == 0 && ft_strchr(cmd->args[0], ' '))
			cmd->args = check_and_insert_first_index(cmd->args, &utils);
		i++;
	}
	tmp = cmd->reds;
	while (tmp)
	{
		if (tmp->char_vars)
		{
			utils.vars.c_vars = tmp->char_vars;
			utils.vars.i_vars = tmp->int_vars;
			utils.count = 0;
			expand_string(&tmp->filename, &utils, i);
		}
		tmp = tmp->next;
	}
	free(utils.arg_vars.c_vars);
	free(utils.arg_vars.i_vars);
	return ;
}
