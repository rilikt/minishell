/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:16:56 by timschmi          #+#    #+#             */
/*   Updated: 2024/03/15 13:01:29 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		total_len;
	char	*str;

	total_len = ft_strlen(s1) + ft_strlen(s2) +1;
	str = (char *)ft_calloc(total_len, sizeof(char));
	if (str == NULL)
		return (NULL);
	ft_strlcat(str, s1, total_len);
	ft_strlcat(str, s2, total_len);
	return (str);
}

// int	main(void)
// {
// 	char s1[] = "Hello, ";
// 	char s2[] = "world!";
// 	char *join;
// 	join = ft_strjoin(s1, s2);

// 	printf("Concatenated string: %s\n", join);

// 	return (0);
// }