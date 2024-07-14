/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:48:13 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/14 15:44:58 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"


void print_arr(char **arr)
{
	int i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

char **create_array(t_token *start, t_token *end)
{
	t_token *temp_start = start;
	int str_count = 0;
	int i = 0;
	char **arr;

	while (temp_start != end)
	{
		str_count++;
		temp_start = temp_start->next;
	}
	arr = (char **)malloc(str_count+1);
	if (!arr)
		ft_error("malloc error", ERR_MALLOC);
	arr[str_count] = NULL;
	while (i < str_count)
	{
		arr[i] = (char *)malloc(ft_strlen(start->str));
		if (!arr[i])
			ft_error("malloc error", ERR_MALLOC);
		arr[i] = start->str;
		start = start->next;
		i++;
	}
	return (arr);
}


void parse_tokens(t_shell *shell)
{
	// compose **args 
	// check for redirects
	// maybe save pointer to struct to know where to start forming the array
	t_token *temp = shell->tokens;
	t_token *start;
	t_cmd *command = NULL;
	char **arr;

	while(temp)
	{
		start = temp;
		while(temp && (temp->type != PIPE && temp->type != IN_REDIRECT)) // make it check for all redir
		{
			temp = temp->next;
		}
		arr = create_array(start, temp);
		print_arr(arr);
		// append_cmd_node(command, arr);
		// check_redir(temp); // move to current / latest command
		// temp = temp->next;
	}

}

// void parse_input(char **arg)
// {
// 	t_cmd *cmd = NULL;
// 	int i = 0;
// 	int j = 0;

// 	while(arg[i])
// 	{
// 		if (check_operators(arg[i]))	// if no operator found it has to be a single command 
// 			append_node(&cmd, arg, i);	// maybe iterate trough it muliple times changing operator based on priority
			
// 		i++;
// 	}
// 	print_list(cmd);
// }
