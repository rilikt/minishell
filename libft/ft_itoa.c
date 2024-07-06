/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:15:08 by timschmi          #+#    #+#             */
/*   Updated: 2024/03/14 15:12:06 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	int_len(long int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int			len;
	char		*num;
	long int	nbr;

	nbr = n;
	len = int_len(nbr);
	num = (char *)malloc((len + 1) * sizeof(char));
	if (num == NULL)
		return (NULL);
	num[len] = '\0';
	if (nbr < 0)
	{
		num[0] = '-';
		nbr *= -1;
	}
	if (nbr == 0)
		num[len -1] = '0';
	while (nbr > 0)
	{
		num[len - 1] = nbr % 10 + '0';
		nbr /= 10;
		len--;
	}
	return (num);
}

// int	main(void)
// {
// 	int	i;

// 	i = 0;
// 	printf("Itoa:%s\n", ft_itoa(i));
// }
