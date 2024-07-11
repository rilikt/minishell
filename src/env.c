/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:31:40 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/11 12:28:56 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void print_env(void) // prints out env from extern char **environ we might have to create our own env don't know
{
	

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
	return ;
}