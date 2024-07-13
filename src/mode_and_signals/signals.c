/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 15:56:00 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/13 16:00:06 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void signal_handle(int signum)
{
	// printf("received ctrl + c (SIGINT)\n");
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
	return;
}