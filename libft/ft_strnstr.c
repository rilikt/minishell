/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:17:13 by timschmi          #+#    #+#             */
/*   Updated: 2024/03/15 17:23:03 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_seg(const char *str)
{
	char	*ok;

	ok = (char *)str;
	*ok = 's';
}

char	*ft_strnstr(const char *str, const char *find, size_t count)
{
	unsigned long int	len;
	unsigned long int	i;
	unsigned long int	j;

	i = 0;
	j = 0;
	len = ft_strlen(find);
	if (str == NULL)
		ft_seg(str);
	if (len == 0)
		return ((char *)str);
	if (count < len)
		return (NULL);
	while (str[i] && count > i)
	{
		j = 0;
		while (find[j] && str[i + j] == find[j] && count > i + j)
			j++;
		if (len == j)
		{
			return ((char *)str + i);
		}
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	// const char *largestring = "Foo Bar Baz";
// 	// const char *smallstring = "Bar";
// 	char *ptr;

// 	ptr = ft_strnstr("lorem ipsum dolor sit amet", "ipsum", 15);
// 	printf("%s\n", ptr);
// 	return (0);
// }