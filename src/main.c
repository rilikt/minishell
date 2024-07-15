/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:17:27 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/15 12:16:19 by timschmi         ###   ########.fr       */
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

		parse_tokens(&shell);

		print_commands(&shell);

		// expand_and_execute(&shell);
	}

	// clean_shell(&shell);

	return (0);
}
