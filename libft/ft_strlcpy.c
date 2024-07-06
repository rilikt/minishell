/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 20:46:25 by timschmi          #+#    #+#             */
/*   Updated: 2024/03/14 15:39:40 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	unsigned long int	i;
	int					len;

	len = ft_strlen(src);
	if (size == 0)
		return (len);
	i = 0;
	while (src[i] && i < size -1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (len);
}

// int main(void)
// {
// 	char	str1[] = "Copy only n -1 chrarcters of this string.";
// 	char dest [15];

// 	printf("%s\n", str1);
// 	int i = ft_strlcpy(dest, str1, sizeof(dest));
// 	printf("%s\n", dest);
// 	printf("%d\n", i);
// }
