/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:05:24 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/13 16:36:27 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

char	*ms_strdup(const char *str)
{
	char	*s;

	s = ft_strdup(str);
	error_check(s, str, ERR_MALLOC);
	return (s);
}

char	*ms_substr(const char *str, unsigned int start, size_t len)
{
	char	*s;

	s = ft_substr(str, start, len);
	error_check(s, str, ERR_MALLOC);
	return (s);
}

char	**ms_split(char *str, char c)
{
	char	**arr;

	arr = ft_split(str, c);
	error_check(arr, str, ERR_MALLOC);
	return (arr);
}

char	*ms_strjoin(char const *s1, char const *s2)
{
	char	*s;

	s = ft_strjoin(s1, s2);
	error_check(s, s1, ERR_MALLOC);
	return (s);
}
