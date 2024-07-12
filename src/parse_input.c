/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:48:13 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/12 12:04:01 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"



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
