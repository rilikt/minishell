/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:22:38 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/04 17:11:24 by pstrohal         ###   ########.fr       */
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

void	expand_string(char **str, t_exp_help *utils)
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
	}
}

void	expand_cmd(t_cmd *cmd, int exitstatus, char **envp)
{
	int				i;
	t_rdct			*tmp;
	t_exp_help	utils;

	i = 0;
	utils.count = 0;
	utils.envp = envp;
	utils.vars.c_vars = cmd->char_vars;
	utils.vars.i_vars = cmd->int_vars;
	utils.exit = exitstatus;
	while (cmd->char_vars && cmd->args[i])
	{
		expand_string(&cmd->args[i], &utils);
		if (ft_strchr(cmd->args[i], ' ') && (i = 0 && !(cmd->char_vars[i] == '2')))
			cmd->args = split_and_arrange_cmd(cmd->args, i, ft_arr_len(cmd->args), NULL);
		i++;
	}
	tmp = cmd->reds;
	while (tmp && tmp->char_vars)
	{
		utils.vars.c_vars = tmp->char_vars;
		utils.vars.i_vars = tmp->int_vars;
		utils.count = 0;
		expand_string(&tmp->filename, &utils);
		tmp = tmp->next;
	}
	// print_arr(cmd->args);
	return ;
}
// int main(int argc, char **argv, char **envp)
// {
// 	t_cmd cmd;
// 	t_rdct	*tmp;
// 	char *f = "$SHLVL";
// 	char *s ="$LOGNAME";
// 	char *d = "ste$?hen$LS";
// 	char *f1 = "1";
// 	char *s1 = "1";
// 	char *d1 = "01";

// 	cmd.args = ft_split("echo $LS'$HOME'", ' ');
// 	cmd.is_var = 1;
// 	cmd.vars = "11";
// 	tmp = (t_rdct *)malloc(sizeof(t_rdct));
// 	cmd.reds = tmp;
// 	tmp->filename = (char *)malloc(sizeof(f));
// 	tmp-> vars = (char *)malloc(sizeof(f1));
// 	ft_memmove(tmp->vars, f1, ft_strlen(f));
// 	ft_memmove(tmp->filename, f, ft_strlen(f));
// 	tmp->next = (t_rdct *)malloc(sizeof(t_rdct));
// 	tmp = tmp->next;
	
// 	tmp->filename = (char *)malloc(sizeof(s));
// 	tmp-> vars = (char *)malloc(sizeof(s1));
// 	ft_memmove(tmp->vars, s1, ft_strlen(s1));
// 	ft_memmove(tmp->filename, s, ft_strlen(s));
// 	tmp->next = (t_rdct *)malloc(sizeof(t_rdct));
// 	tmp = tmp->next;
	
// 	tmp->filename = (char *)malloc(sizeof(d));
// 	tmp-> vars = (char *)malloc(sizeof(d1));
// 	ft_memmove(tmp->vars, d1, ft_strlen(d1));
// 	ft_memmove(tmp->filename, d, ft_strlen(d));
// 	tmp->next = NULL;
	
// 	cmd.var_in_redir = 1;
// 	expand_cmd(&cmd, 15, envp);
// 	int i = 0;
// 	printf("---final output---\n\n");
// 	while (cmd.args[i])
// 	{
// 		if (cmd.args[i + 1])
// 			printf("%s\n", cmd.args[i]);
// 		else
// 			printf("%s\n", cmd.args[i]);
// 		free(cmd.args[i]);
// 		i++;
// 	}
// 	free(cmd.args);
// 	printf("\n------reds---------\n\n");
// 	while (1)
// 	{
// 		tmp = cmd.reds;
// 		printf("%s\n", cmd.reds->filename);
// 		free(cmd.reds->filename);
// 		cmd.reds = cmd.reds->next;
// 		free(tmp);
// 		if(!cmd.reds)
// 			break ;
// 	}
// 	printf("\n");
	
// 	// system("leaks a.out");
// 	return 0;
// }
// cc -Wall -Wextra -Werror -lreadline ../../include/libft/libft.a 
// expanding.c ../error_and_utils/error.c -g