/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:21:27 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/14 12:41:46 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s$\n", arr[i]);
		i++;
	}
}

void	print_commands(t_shell *shell)
{
	t_cmd	*temp;
	t_rdct	*temp_redir;
	int		cmd_i;
	int		redir_i;
	int		i;
	int j;

	// t_shell *temp = shell;
	temp = shell->commands;
	cmd_i = 1;
	redir_i = 0;
	i = 0;
	printf("Commands: %d\n", shell->cmd_nb);
	while (temp)
	{
		redir_i = 1;
		i = 0;
		printf("-command%d- :", cmd_i);
		while (temp->args && temp->args[i])
		{
			printf("%s ", temp->args[i]);
			i++;
		}
		printf("vars %s ", temp->char_vars);
		if (temp->char_vars)
		{
			j = 0;
			printf("int_vars:");
			while (j < ft_strlen(temp->char_vars))
			{
				printf("%d ", temp->int_vars[j]);
				j++;
			}
		}
		if (temp->reds)
		{
			printf("redirections: ");
			temp_redir = temp->reds;
			while (temp_redir)
			{
				printf("nr:%d type: %d filename: %s vars %s", redir_i,
					temp->reds->type, temp->reds->filename, temp->reds->char_vars);
				if (temp->reds->char_vars)
				{
					j = 0;
					printf("int_vars:");
					while (j < ft_strlen(temp->reds->char_vars))
					{
						printf("%d ", temp->reds->int_vars[j]);
						j++;
					}
				}
				temp_redir = temp_redir->next;
				redir_i++;
			}
		}
		printf("\n");
		temp = temp->next;
		cmd_i++;
	}
}
