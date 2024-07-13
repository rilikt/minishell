/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:17:27 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/13 16:06:48 by pstrohal         ###   ########.fr       */
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

		add_history(shell.input);

		print_tokens(&shell);

		// parse(&shell);

		// expand_and_execute(&shell);
	}

	// clean_shell(&shell);

	return (0);
}
