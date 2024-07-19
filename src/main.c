/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:17:27 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/19 11:52:23 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int main(int argc, char **argv, char **envp)
{
	t_shell	shell;

	// setup_shell(&shell);
	go_home(); //moves to "root" dir of the user
	while(1)
	{
		shell.input = read_input();
	
		tokenize(&shell);

		// print_tokens(&shell);

		parse_tokens(&shell);

		print_commands(&shell);
		
		// free_struct(&shell);

		// expand_and_execute(&shell);

	}

	// clean_shell(&shell);

	return (0);
}
