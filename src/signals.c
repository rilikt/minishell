/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:56:00 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/08 12:09:29 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

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