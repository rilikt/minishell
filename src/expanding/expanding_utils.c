/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:31:51 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/11 18:22:04 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	*check_char_behind(char **pos, char **str)
{
	char	c;
	int		*var_len;

	var_len = (int*)malloc(sizeof(int));
	*var_len = 0;
	if (*pos && *(*pos + 1))
		c = *(*pos + 1);
	else
		return (NULL);
	if (c == '\0')
		return (NULL);
	else if (!ft_isalpha((int)c) && c != '_')
		ft_memmove(*pos, *pos + 1, ft_strlen(*pos + 1) + 1);
	else if(ft_isalpha((int)c) || c == '_')
	{
		while(ft_isalpha((int)*(*pos + 1 + *var_len))
			|| ft_isdigit((int)*(*pos + 1 + *var_len)) || *(*pos + 1 + *var_len) == '_')
		(*var_len)++;
	}
	return (var_len);
}
int	ft_arr_len(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return (i);
	while  (arr[i])
		i++;
	return (i);
}

void	free_arg_vars(t_exp *utils, int arg_len)
{
	int	i;
	int	s_e_len;
	i = 0;
	while (i < arg_len)
	{
		if (ft_strlen(utils->arg_vars[i].type) > 0)
		{
			free(utils->arg_vars[i].s_index);
			free(utils->arg_vars[i].e_index);
		}
		free(utils->arg_vars[i].type);
		i++;
	}
	free(utils->arg_vars);
	
}

void	setup_exp_help_struct(t_cmd *cmd, t_exp *utils, int arg_len, int vars_used)
{
	int	i;
	int	j;
	int	var_count;
	
	i = -1;
	utils->arg_vars = (t_avars *)malloc(sizeof(t_avars) * arg_len);
	error_check(utils->arg_vars, "malloc arg_vars in setup_exp_help_struct", ERR_MALLOC);
	while (++i < arg_len)
	{
		var_count = count_vars_in_str(cmd->args[i]);
		utils->arg_vars[i].type = ft_substr(cmd->char_vars, vars_used, var_count);
		error_check(utils->arg_vars[i].type, "substr in setup_exp_help_struct", ERR_MALLOC);
		utils->arg_vars[i].s_index = (int *)malloc(sizeof(int) * ft_strlen(utils->arg_vars[i].type));
		error_check(utils->arg_vars[i].type, "malloc s_i in setup_exp_struct", ERR_MALLOC);
		utils->arg_vars[i].e_index = (int *)malloc(sizeof(int) * ft_strlen(utils->arg_vars[i].type));
		error_check(utils->arg_vars[i].type, "malloc e_i in setup_exp_struct", ERR_MALLOC);
		j = -1;
		while (++j < var_count)
		{
			utils->arg_vars[i].s_index[j] = cmd->int_vars[vars_used + j];
			utils->arg_vars[i].e_index[j] = 0;
		}
		vars_used += var_count;
	}
return ;
}
	// int k = 0;
	// int l = 0;

	// while (cmd->args[k])
	// {
	// 	l = 0;
	// 	while (l < ft_strlen(utils->arg_vars[k].type))
	// 		printf("%d,", utils->arg_vars[k].s_index[l++]);
	// 	printf("\n%s\n", utils->arg_vars[k].type);
	// 	k++;
	// }
int	count_vars_in_str(char *str)
{
	int	j;
	int	var_count;

	j = -1;
	var_count = 0;
	if (str)
	{
		while (str[++j])
		{
		if (str[j] == '$')
			var_count++;	
		}
	}
	return (var_count);
	
}

void	expand_heredoc(char **str, t_exp *utils)
{
	int		tmp;
	char	*pos;
	char	*var_value;
	char	*var_name;
	int		*var_len;

	tmp = 0;
	utils->str = str;
	var_value = NULL;
	pos = ft_strchr(*str + tmp, '$');
	while (pos)
	{
		var_len = check_char_behind(&pos, str);
		if (var_len)
			var_value = get_var(pos, &var_name, *var_len, utils);
		if (var_value)
			tmp = insert_var(str, pos, var_value, var_name);
		pos = ft_strchr(*str + tmp, '$');
	}
	return ;
}
/*
ec$USER "$HOME $?" $$USER"$SHLVL" $"$"$
export T="ho    world"

 minishell > ec$HOME >  $USER"LOL" <HALLO$HOME <<s
> lool
> $USER
> $SHLVL
> "HALLO $USER$$$"
> s

cat << s
egdfg
srg
$HOME.edwsgo
rghgsfadok$USER/fdf"PRP"
'hallo$HOME'
hah
s


*/