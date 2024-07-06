/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:50:46 by timschmi          #+#    #+#             */
/*   Updated: 2024/03/14 14:03:46 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long int	i;

	i = n;
	if (i < 0)
	{
		ft_putchar_fd('-', fd);
		i = i * (-1);
	}
	if (i < 10)
	{
		ft_putchar_fd((i + '0'), fd);
	}
	else
	{
		ft_putnbr_fd((i / 10), fd);
		ft_putchar_fd((i % 10 + '0'), fd);
	}
}
