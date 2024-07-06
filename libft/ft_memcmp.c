/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:45:32 by timschmi          #+#    #+#             */
/*   Updated: 2024/03/15 12:55:26 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *buffer, const void *buffer2, size_t count)
{
	unsigned long int	i;
	unsigned char		*buf;
	unsigned char		*buf2;

	buf = (unsigned char *)buffer;
	buf2 = (unsigned char *)buffer2;
	i = 0;
	while (count > i)
	{
		if (buf[i] != buf2[i])
			return (buf[i] - buf2[i]);
		i++;
	}
	return (0);
}

// int main() {
//     const char *str1 = "abcd";
//     const char *str2 = "abcf";
//     size_t len = strlen(str1);

//     // Compare the first 'len' bytes of str1 and str2
//     int result = ft_memcmp(str1, str2, len);

// 	printf("%d\n", result);
//     if (result < 0) {
//         printf("str1 is less than str2.\n");
//     } else if (result > 0) {
//         printf("str1 is greater than str2.\n");
//     } else {
//         printf("str1 is equal to str2.\n");
//     }

//     return (0);
// }