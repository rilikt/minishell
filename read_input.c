/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:39:58 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/06 17:29:20 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

char *read_input(void)
{
	char *input = NULL;
	char path[1024];

	getcwd(path, sizeof(path)); // maybe move to home dir first
	printf("%s", path);
	input = readline(" > "); // readline returns 0 on EOF
	if (!input)
	{
		free(input);
		exit(EXIT_FAILURE);
	}
	// printf("%s", getenv("PWD")); // shows PWD
	
	add_history(input);
	
	return (input);
}
