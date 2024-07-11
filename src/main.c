/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:17:27 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/11 12:27:00 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	signal(SIGINT, signal_handle);
	go_home();
	while(1)
	{
		shell.input = read_input();
	
		tokenize(&shell);

		parse(&shell);

		expand_and_execute(&shell);
	}

	clean_shell(&shell);
	
	return (0);
}