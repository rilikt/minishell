/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:56:00 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/07 13:24:56 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void signal_handle(int signum)
{
	// printf("received ctrl + c (SIGINT)\n");
	
	printf("\n");
	// rl_replace_line("\n", 1);
	rl_redisplay();
	// rl_on_new_line();
	// rl_redisplay();
	return;
}