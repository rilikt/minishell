/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:54:15 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/07 13:16:29 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void execute_commands(char **arg)
{
	// printf("%s, %s\n", arg[0], arg[1]); // shows arguments

	if (!ft_strncmp(arg[0], "cd", 2))
		change_directory(arg[1]);
	else if (!ft_strncmp(arg[0], "pwd", 3))
		display_pwd();

}