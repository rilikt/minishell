/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:06:06 by timschmi          #+#    #+#             */
/*   Updated: 2024/03/15 17:47:48 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char				*sub;
	unsigned long int	i;
	unsigned int		size;
	unsigned int		str_len;

	i = 0;
	size = len;
	str_len = ft_strlen(s);
	if (start + len > str_len)
		size = str_len - start;
	if (start >= str_len)
		size = 0;
	sub = (char *)malloc((size + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	sub[size] = '\0';
	if (size == 0)
		return (sub);
	while (s[start] && len > i && size != 0)
	{
		sub[i] = s[start];
		start++;
		i++;
	}
	return (sub);
}

// int	main(void)
// {
// 	char str[] = "";
// 	char *sub;

// 	sub = ft_substr(str, 1, 1);
// 	printf("%s\n", sub);
// 	printf("%zu\n", ft_strlen(sub));
// }