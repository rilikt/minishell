/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:22:38 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/12 20:52:15 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

char	*get_var(char *pos, char **var_name, int var_len, t_exp *utils)
{
	char	*tmp;
	char	*var_value;

	var_value = NULL;
	tmp = pos + 1;
	if (*tmp == '?')
		var_value = ft_itoa(utils->exit);
	*var_name = ft_substr(pos, 1, var_len);
	if (!var_value)
		var_value = ft_getenv(*var_name, utils->envp);
	return (var_value);
}

int	insert_var(char **str, char *pos, char *var_value, char *var_name)
{
	char	*new_str;
	int		new_len;
	char	*var_end;
	int		index_var_end;

	var_end = pos + ft_strlen(var_name) + 1;
	new_len = ft_strlen(*str) - (ft_strlen(var_name) + 1)
		+ ft_strlen(var_value);
	new_str = (char *)malloc(sizeof(char) * new_len + 1);
	error_check(new_str, "malloc in insert_var", ERR_MALLOC);
	ft_strlcpy(new_str, *str, pos - *str + 1);
	ft_strlcpy(&(new_str[ft_strlen(new_str)]), var_value,
		ft_strlen(var_value) + 1);
	index_var_end = ft_strlen(new_str);
	ft_strlcpy(&(new_str[ft_strlen(new_str)]), var_end, ft_strlen(var_end) + 1);
	free(*str);
	free(var_name);
	*str = new_str;
	return (index_var_end);
}

void	handle_var(int i, char **pos, int *tmp, t_exp *utils)
{
	char	*var_name;
	char	*var_value;
	int		var_len;
	
	var_value = NULL;
	var_name = NULL;
	t_avars *lol = &(utils->arg_vars[i]);
	if (utils->arg_vars[i].type[utils->v_count] == '0')
	{
		*tmp += 1;
		utils->arg_vars[i].e_index[utils->v_count] = *tmp - 1;
	}
	else if (utils->arg_vars[i].type[utils->v_count] == '1'
			|| utils->arg_vars[i].type[utils->v_count] == '2')
	{
		var_len = utils->arg_vars[i].s_index[utils->v_count];
		utils->arg_vars[i].s_index[utils->v_count] = *tmp;
		if (var_len)
		{
			var_value = get_var(*pos, &var_name, var_len, utils);
			if (!var_value)
				ft_memmove(*pos, *pos + var_len + 1, ft_strlen(*pos + var_len + 1) + 1);
			else
				*tmp = insert_var(utils->str, *pos, var_value, var_name);
		}
		// else if (!((*(*pos + 1) == '\0') || (*(*pos + 1) == '$')))
		// 	ft_memmove(*pos, *pos + 1, ft_strlen(*pos + 1) + 1);
		else
			*tmp += 1;
		utils->arg_vars[i].e_index[utils->v_count] = *tmp - 1;
	}	
	else if (utils->arg_vars[i].type[utils->v_count] == '3')
	{
		ft_memmove(*pos, *pos + 1, ft_strlen(*pos + 1) + 1);
		*tmp = *pos - *(utils->str);
	}
}

void	expand_string(char **str, int type, t_exp *utils, int i)
{
	int		tmp;
	char	*pos;
	char frt;
	tmp = 0;
	utils->v_count = 0;
	utils->str = str;
	if (type != IN_HEREDOC)
	{
		while (str[0][tmp])
		{
			frt = str[0][tmp];
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
	f_name = ft_strdup(tmp->filename);
	error_check(f_name, "strdup in expand_redirect", ERR_MALLOC);
	while (tmp)
	{
		if (tmp->char_vars)
		{
			utils->arg_vars->type = tmp->char_vars;
			error_check(utils->arg_vars->type, "strdup in expand_cmd", ERR_MALLOC);
			utils->arg_vars->s_index = tmp->int_vars;
			utils->arg_vars->e_index = tmp->int_vars;
				expand_string(&tmp->filename, tmp->type, utils, 0);
			if (ft_strchr(tmp->filename, ' ') && tmp->type != IN_HEREDOC)
				return(ft_error(f_name, "ambiguous redirect", 0),
					free(utils->arg_vars), free(f_name), 2);
		}
		tmp = tmp->next;
	}
	return (free(utils->arg_vars), free(f_name), 0);
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
		setup_exp_help_struct(cmd, &utils, arg_len, 0);
	while (cmd->char_vars && cmd->args[++i] && ++a >= 0)
	{
		expand_string(&cmd->args[i], 0, &utils, a);
		if (strchr(utils.arg_vars[a].type, '1'))
			cmd->args = split_arg(cmd->args, utils.arg_vars, &i, a);
	}
	// free_arg_vars(&utils, arg_len);
	if (cmd->reds)
		return (expand_redirects(cmd->reds, &utils));
	return (0);
}
