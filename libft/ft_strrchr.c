/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:13:06 by timschmi          #+#    #+#             */
/*   Updated: 2024/03/16 12:59:44 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	ch;
	char	*st;
	int		len;

	st = (char *)str;
	ch = (char)c;
	len = ft_strlen(str);
	while (len >= 0)
	{
		if (ch == st[len])
			return (st + len);
		len--;
	}
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