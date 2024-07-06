/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 18:51:50 by timschmi          #+#    #+#             */
/*   Updated: 2024/03/16 12:55:27 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = (unsigned char *)s;
	while (n > 0)
	{
		*p = 0;
		p++;
		n--;
	}
}

// int	main(void)
// {
// 	char str[] = "This is an example string";

// 	printf("%s\n", str);
// 	ft_bzero(str, sizeof(str[0]));
// 	printf("%s\n", str);
// 	return (0);
// }