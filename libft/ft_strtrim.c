/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 13:25:56 by timschmi          #+#    #+#             */
/*   Updated: 2024/03/16 12:47:43 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	set_front(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (set[j])
	{
		if (s1[i] == set[j])
		{
			i++;
			j = 0;
		}
		else
			j++;
	}
	return (i);
}

static int	ft_trim_len(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	total;
	int	len;

	j = 0;
	total = set_front(s1, set);
	len = ft_strlen(s1);
	i = len - 1;
	while (i >= 0 && set[j])
	{
		if (s1[i] == set[j])
		{
			i--;
			j = 0;
			total++;
		}
		else
			j++;
	}
	len -= total;
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	int		front;
	int		trim_len;

	if (s1 == NULL || *s1 == '\0')
	{
		trim = (char *)malloc(1 * sizeof(char));
		if (trim == NULL)
			return (NULL);
		trim[0] = '\0';
		return (trim);
	}
	front = set_front(s1, set);
	trim_len = ft_trim_len(s1, set);
	trim = ft_substr(s1, front, trim_len);
	return (trim);
}

// int main(void)
// {
// 	// char s1[] = "obobTrim the o's from thisooob";
// 	// char set[]= "ob";

// 	char *trim = ft_strtrim("", "cdef");
// 	printf("%s\n", trim);
// }