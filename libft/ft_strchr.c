/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:53:06 by timschmi          #+#    #+#             */
/*   Updated: 2024/03/14 13:57:15 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	char	ch;
	char	*st;
	int		i;

	i = 0;
	st = (char *)str;
	ch = (char)c;
	while (str[i])
	{
		if (ch == st[i])
			break ;
		i++;
	}
	if (ch == st[i])
		return (st + i);
	else
		return (0);
}

// int main(void)
// {
//   char buffer1[40] = "computer program";
//   char * ptr;
//   int    ch = 'p';

//   ptr = ft_strchr( buffer1, ch );
//   printf( "The first occurrence of %c in '%s' is '%s'\n",
//             ch, buffer1, ptr );

// }