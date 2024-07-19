/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 17:22:38 by pstrohal          #+#    #+#             */
/*   Updated: 2024/07/19 11:27:40 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

char	*get_var(char *pos, char **var_name)
{
	char	*tmp;
	char	*var_value;

	tmp = pos + 1;
	while (*tmp && (*tmp != ' ') && (*tmp != '$'))
		tmp++;
	*var_name = (char *)malloc(sizeof(char) * (tmp - pos));
	error_check(*var_name, "malloc failed", ERR_MALLOC);
	ft_strlcpy(*var_name, pos + 1, tmp - pos);
	var_value = getenv(*var_name);
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
	ft_strlcpy(new_str, *str, pos + 1 - *str);
	ft_strlcpy(&(new_str[ft_strlen(new_str)]), var_value,
		ft_strlen(var_value) + 1);
	ft_strlcpy(&(new_str[ft_strlen(new_str)]), var_end, ft_strlen(var_end) + 1);
	free(var_name);
	free(*str);
	*str = new_str;
	return ;
}

void	expand_string(char **str, int exitstatus)
{
	char	*pos;
	char	*value;
	char	*name;
	char	*tmp;

	tmp = *str;
	pos = ft_strchr(tmp, '$');
	name = NULL;
	while (pos)
	{
		check_char_behind(&pos, &tmp);
		if (pos)
		{
			if (*(pos + 1) == '?')
				value = ft_itoa(exitstatus);
			else
				value = get_var(pos, &name);
			if (!value)
				ft_memmove(pos, pos + ft_strlen(name) + 1, ft_strlen(name) + 1);
			else
				insert_var(str, pos, value, name);
			tmp = *str;
			pos = ft_strchr(tmp, '$');
		}
	}
}

void	expand_cmd(t_cmd *cmd, int exitstatus)
{
	int		i;
	t_rdct	*tmp;

	i = 0;
	while (cmd->is_var > 0 && cmd->args[i])
	{
		expand_string(&cmd->args[i], exitstatus);
		if (i == 0 && ft_strchr(cmd->args[0], ' '))
			cmd->args = split_and_arrange_cmd(cmd->args);
		i++;
	}
	tmp = cmd->reds;
	while (cmd->var_in_redir > 0 && tmp)
	{
		expand_string(&tmp->filename, exitstatus);
		tmp = tmp->next;
	}
	return ;
}
// int main()
// {
// 	t_cmd cmd;
// 	t_rdct	*tmp;
// 	char *f = "Hier$SHLVL";
// 	char *s ="Muestte $LOGNAME";
// 	char *d = "stehen$LS";

// 	cmd.args = ft_split("Ha$LOGNAME$$$ l l o&hier&ist&philipp&aka$LS", '&');
// 	cmd.is_var = 1;
// 	tmp = (t_rdct *)malloc(sizeof(t_rdct));
// 	cmd.reds = tmp;
// 	tmp->filename = (char *)malloc(sizeof(f));
// 	ft_memmove(tmp->filename, f, ft_strlen(f));
// 	tmp->next = (t_rdct *)malloc(sizeof(t_rdct));
// 	tmp = tmp->next;
// 		tmp->filename = (char *)malloc(sizeof(s));
// 	ft_memmove(tmp->filename, s, ft_strlen(s));
// 	tmp->next = (t_rdct *)malloc(sizeof(t_rdct));
// 	tmp = tmp->next;
// 		tmp->filename = (char *)malloc(sizeof(d));
// 	ft_memmove(tmp->filename, d, ft_strlen(d));
// 	tmp->next = NULL;
// 	cmd.var_in_redir = 1;
// 	expand_cmd(&cmd, 0);
// 	int i = 0;
// 	printf("---final output---\n");
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
// 	printf("------reds---------\n");
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

// 	// system("leaks a.out");
// 	return 0;
// }
// cc -Wall -Wextra -Werror -lreadline ../../include/libft/libft.a 
// expanding.c ../error_and_utils/error.c -g