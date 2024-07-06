/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:21:09 by timschmi          #+#    #+#             */
/*   Updated: 2024/03/14 12:37:20 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

// void print_index_and_char(unsigned int index, char *c) {
//     printf("Index: %u, Character: %c\n", index, *c);
// }

// int main(void)
// {
// 	char *str = "Apply x function to this string.";
// 	char *str2;

// 	ft_striteri(str, print_index_and_char);
// 	printf("%s\n", str2);

// }