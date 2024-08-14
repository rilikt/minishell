/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:42:47 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/14 12:44:48 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

char	**append_env(char *var, char **envp)
{
	int		len;
	char	**re;

	len = 0;
	while (envp[len])
	{
		if (!ft_strncmp(envp[len], var, var_len(envp[len], var) + 1))
			return (envp);
		len++;
	}
	re = (char **)malloc((len + 2) * sizeof(char *));
	error_check(re, "append_env", ERR_MALLOC);
	len = 0;
	while (envp[len])
	{
		re[len] = ms_strdup(envp[len]);
		len++;
	}
	re[len] = ms_strdup(var);
	re[len + 1] = NULL;
	free_string_array(envp);
	return (re);
}

int	var_len(char *str, char *str2)
{
	char	*var_name_end;
	int		len1;
	int		len2;

	if (!str2)
	{
		var_name_end = ft_strchr(str, '=');
		if (!var_name_end)
			return (0);
		return (var_name_end - str);
	}
	else
	{
		if (!(len1 = var_len(str, NULL)))
			len1 = ft_strlen(str);
		if (!(len2 = var_len(str2, NULL)))
			len2 = ft_strlen(str2);
		if (len1 < len2)
			len1 = len2;
		return (len1);
	}
}

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

char	*rm_plus(char *str)
{
	int		i;
	int		j;
	char	*re;
	int		flag;

	i = 0;
	j = 0;
	flag = 1;
	re = (char *)malloc(ft_strlen(str));
	while (str[i])
	{
		if (flag && str[i] == '+')
		{
			i++;
			flag = 0;
		}
		re[j] = str[i];
		i++;
		j++;
	}
	re[j] = '\0';
	return (re);
}

int	ex_append_loop(char ***envp, char *arg, int len)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	if (len == 0)
		return (0);
	while ((*envp)[i] && len != 0)
	{
		len = var_len(arg, (*envp)[i]);
		if (!ft_strncmp((*envp)[i], arg, len))
		{
			tmp = ms_strjoin((*envp)[i], ft_strchr(arg, '=') + 1);
			free((*envp)[i]);
			(*envp)[i] = tmp;
			return (1);
		}
		i++;
	}
	return (0);
}


int check_plus(char *arg)
{
	int i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (arg[i] == '+')
			return (1);
		i++;
	}
	return (0);
}

int	export_append(char **args, char ***envp, int *j)
{
	char	*str;
	int		i;
	int		len;
	int		set;

	i = 0;
	set = 0;
	if (!check_plus(args[*j]))
		return (0);
	str = rm_plus(args[*j]);
	len = var_len(str, NULL);
	set = ex_append_loop(envp, str, len);
	if (set != 1)
		(*envp) = append_env(str, *envp);
	*j += 1;
	if (!args[*j])
		return (1);
	return (0);
}

int	export_loop(char ***envp, char *arg, int len)
{
	int	i;

	i = 0;
	if (len == 0)
		return (0);
	while ((*envp)[i] && len != 0)
	{
		len = var_len(arg, (*envp)[i]);
		if (!ft_strncmp((*envp)[i], arg, len))
		{
			free((*envp)[i]);
			(*envp)[i] = ms_strdup(arg);
			return (1);
		}
		i++;
	}
	return (0);
}

int	export(char **args, char ***envp)
{
	int	j;
	int	set;
	int	len;

	j = 1;
	if (!args[1])
		return (export_print(*envp), 0);
	if (check_input(args, envp, 1) == -1)
		return (1);
	while (args[j])
	{
		if (export_append(args, envp, &j))
			break ;
		len = var_len(args[j], NULL);
		set = export_loop(envp, args[j], len);
		if (set != 1)
			(*envp) = append_env(args[j], *envp);
		j++;
	}
	return (0);
}
