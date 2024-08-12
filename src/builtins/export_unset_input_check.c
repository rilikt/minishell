/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset_input_check.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 14:57:15 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/11 16:23:39 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int invalid_char(char *c, int mode)
{
	char *set;
	int i;

	i = 0;
	set = "-+.}{}*@!?#^\\~$;/";
	while (set[i])
	{
		if (mode == 2 && *c == '=')
			return (-1);
		if (set[i] == *c)
		{
			if (mode == 1 && set[i] == '+' &&  c[1] == '=')
				return(0);
			return (-1);
		}
		i++;
	}
	return (0);
}

void not_valid(char *str)
{
	write(2, "minishell: export: `", 20);
	write(2, str, ft_strlen(str));
	write(2, "': not a valid identifier\n", 27);
}
int		check_input(char **args, char ***envp, int mode)
{
	int	i;
	int j;

	i = 1;
	j = 0;
	if (!envp || !(*envp))
		return (-1);
	while (args[i])
	{
		j = 0;
		if (ft_isdigit(args[i][j]) || args[i][j] == '=' || args[i][j] == '\0')
			return (not_valid(args[i]), -1);
		while (args[i][j])
		{
			if (invalid_char(&args[i][j], mode))
				return (not_valid(args[i]), -1);
			if (args[i][j] == '=')
				break;
			j++;
		}
		i++;
	}
	return (i);
}
