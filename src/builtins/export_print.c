/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 18:29:24 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/14 18:30:25 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	add_qoutes(char **envp)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (envp[i])
	{
		j = 0;
		len = var_len(envp[i], NULL);
		printf("declare -x ");
		if (len == 0)
			printf("%s\n", envp[i]);
		else
		{
			while (j <= len)
			{
				printf("%c", envp[i][j]);
				j++;
			}
			printf("\"%s\"\n", envp[i] + len + 1);
		}
		i++;
	}
}

int	copy_envp(char ***local_envp, char **envp)
{
	int	len;

	len = 0;
	while (envp[len])
		len++;
	(*local_envp) = (char **)malloc((len + 1) * sizeof(char *));
	error_check((*local_envp), "copy_envp", ERR_MALLOC);
	len = 0;
	while (envp[len])
	{
		(*local_envp)[len] = ms_strdup(envp[len]);
		len++;
	}
	(*local_envp)[len] = NULL;
	return (len);
}

void	export_print(char **envp)
{
	char	*temp;
	int		j;
	int		len;
	char	**local_envp;
	int		len_var;

	len = copy_envp(&local_envp, envp);
	while (len - 1)
	{
		j = 0;
		while (j < len - 1)
		{
			len_var = var_len(local_envp[j], local_envp[j + 1]);
			if (ft_strncmp(local_envp[j], local_envp[j + 1], len_var + 1) > 0)
			{
				temp = local_envp[j];
				local_envp[j] = local_envp[j + 1];
				local_envp[j + 1] = temp;
			}
			j++;
		}
		len--;
	}
	add_qoutes(local_envp);
	free_string_array(local_envp);
}

int	check_and_print(char **args, char ***envp)
{
	int	j;

	j = 1;
	if (!(*envp))
		return (0);
	while (args[j])
	{
		if (ft_isdigit(args[j][0]) || args[j][0] == '?' || args[j][0] == '$'
			|| args[j][0] == '=')
		{
			write(2, "minishell: export: `", 20);
			write(2, args[j], ft_strlen(args[j]));
			write(2, "': not a valid identifier\n", 27);
			return (0);
		}
		j++;
	}
	return (1);
}
