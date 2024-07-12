/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:17:27 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/12 16:25:00 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

int main(int argc, char **argv, char **envp)
{
	t_shell	*shell = (t_shell *)malloc(sizeof(t_shell));

	signal(SIGINT, signal_handle);
	go_home(); //moves to "root" dir of the user
	while(1)
	{
		shell->input = read_input();
	
		tokenize(&shell);

		print_tokens(shell);

		// parse(&shell);

		// expand_and_execute(&shell);
	}

	// clean_shell(&shell);

	return (0);
}
