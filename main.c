/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:17:27 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/07 12:38:44 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

int main(void)
{
	char *input;
	char **arg;

	signal(SIGINT, signal_handle);
	go_home();
	while(1)
	{
		input = read_input();
	
		arg = parse_input(input);

		execute_commands(arg);
	}

	
	return (0);
}