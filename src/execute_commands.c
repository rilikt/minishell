/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:54:15 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/09 17:05:42 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void execute_commands(char **arg)
{
	// printf("%s, %s\n", arg[0], arg[1]); // shows arguments



	if (!ft_strncmp(arg[0], "cd", 3)) // takes only one argument
		change_directory(arg);
	
	else if (!ft_strncmp(arg[0], "pwd", 4)) // takes no additional arguments and displays error if it does
		display_pwd(arg);

	else if (!ft_strncmp(arg[0], "env", 4)) // takes no argument and throws error if it does
		print_env(arg);
	
}