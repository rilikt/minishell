/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:17:27 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/09 16:02:32 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int main(void)
{
	char *input;
	char **arg;

	signal(SIGINT, signal_handle);
	go_home(); //moves to "root" dir of the user
	while(1)
	{
		input = read_input();
	
		arg = tokenize(input);

		parse_input(arg);

		if (!ft_strncmp(arg[0], "exit", 4))
			break;

		execute_commands(arg);
	}

	clean_shell(arg);

	return (0);
}
