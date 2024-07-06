/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 19:17:03 by timschmi          #+#    #+#             */
/*   Updated: 2024/05/11 16:53:36 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// The memmove() function copies count bytes of src to dest.
// This function allows copying between objects that might overlap as
// if src is first copied into a temporary array.

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	unsigned char		*d;
	unsigned char		*s;

	if (dest == NULL && src == NULL)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (d > s && d < s + count)
	{
		while (count > 0)
		{
			d[count -1] = s[count -1];
			count--;
		}
	}
	else
		ft_memcpy(dest, src, count);
	return (dest);
}

// int	main(void)
// {
// 	char	x[] = "abcdefghi";
// 	char	y[] = "abcdefghi";

// 	memmove(&x[3], &x[0], 4);
// 	printf("after memmove: %s\n", x);
// 	ft_memmove(&y[3], &y[0], 4);
// 	printf("after memcpy:  %s\n", y);
// }
