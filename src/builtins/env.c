/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:31:40 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/17 12:47:56 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

// void print_env(char **arg, t_shell *shell) // prints out env from extern char **environ we might have to create our own env don't know
// {
	// char **env = shell->envp;

// 	if (arg[1])
// 	{
// 		write(2, "env : too many arguments\n", 25);
// 		return;
// 	}

// 	while (*env != NULL)
// 	{
// 		printf("%s\n", *env);
// 		env++;
// 	}
// 	return ;
// }