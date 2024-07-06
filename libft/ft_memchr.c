/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:26:16 by timschmi          #+#    #+#             */
/*   Updated: 2024/03/15 12:53:52 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *buf, int c, size_t count)
{
	unsigned char		*buffer;
	unsigned char		ch;
	unsigned long int	i;

	i = 0;
	buffer = (unsigned char *)buf;
	ch = (unsigned char)c;
	while (count > i)
	{
		if (buffer[i] == ch)
			return (buffer + i);
		i++;
	}
	return (0);
}

// int main() {
//     const char *str = "Hello, world!";
//     char ch = 'o';
//     size_t len = strlen(str);

//     // Search for the character 'o' in the string
//     void *result = ft_memchr(str, ch, len);

//     if (result != NULL) {
//         printf("Found '%c' at position: %ld\n", ch, (char *)result - str);
//     } else {
//         printf("'%c' not found in the string.\n", ch);
//     }

//     return (0);
// }