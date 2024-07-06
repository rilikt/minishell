/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:02:16 by timschmi          #+#    #+#             */
/*   Updated: 2024/03/16 13:03:32 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned long int	i;
	unsigned char		*str1;
	unsigned char		*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && str1[i] && str1[i] == str2[i])
	{
		i++;
	}
	if (str1[i] == str2[i])
		return (0);
	else
		return (str1[i] - str2[i]);
}

// #include <unistd.h>
// #include <stdio.h>

// int main(void)
// {
// 	char str1[] = "Hello";
// 	char str2[] = "Hallo";
// 	int n = 4;

// 	int	i = ft_strncmp(str1, str2, n);
// 	printf("%d\n", i);
// }
