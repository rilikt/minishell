/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:54:15 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/08 14:35:02 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void execute_commands(char **arg)
{
	// printf("%s, %s\n", arg[0], arg[1]); // shows arguments

	if (!ft_strncmp(arg[0], "cd", 2)) // takes only one argument
		change_directory(arg[1]);
	
	else if (!ft_strncmp(arg[0], "pwd", 3)) // takes no additional arguments and displays error if it does
		display_pwd();

	// else if (!ft_strncmp(arg[0], "exit", 4)) // closes the program right away and doesn't care if it get additional arguments
	// 	exit_shell();

	// else if (!ft_strncmp(arg[0], "env", 3)) // takes no argument and throws error if it does
	// 	print_env();
	

	
	


}