/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 11:21:27 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/31 14:29:37 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
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
		while (temp->args[i])
		{
			printf("%s ", temp->args[i]);
			i++;
		}
		printf("vars %s ", temp->vars);
		if (temp->reds)
		{
			printf("redirections: ");
			temp_redir = temp->reds;
			while (temp_redir)
			{
				printf("nr:%d type: %d filename: %s vars %s", redir_i,
					temp->reds->type, temp->reds->filename, temp->reds->vars);
				temp_redir = temp_redir->next;
				redir_i++;
			}
		}
		printf("\n");
		temp = temp->next;
		cmd_i++;
	}
}

// void copy_string(char **des, char *src)
// {
// 	int len = ft_strlen(src) +1;
// 	*des = (char *)malloc(len);
// 	int i = 0;
// 	while(src[i])
// 	{
// 		(*des)[i] = src[i];
// 		i++;
// 	}
// 	(*des)[i] = '\0';
// 	// printf("%s\n", *des);

// }