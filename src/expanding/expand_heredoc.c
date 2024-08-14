/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 11:47:07 by pstrohal          #+#    #+#             */
/*   Updated: 2024/08/14 11:47:12 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	*check_char_behind(char **pos)
{
	char	c;
	int		*var_len;

	var_len = (int *)malloc(sizeof(int));
	*var_len = 0;
	if (*pos && *(*pos + 1))
		c = *(*pos + 1);
	else
		return (NULL);
	if (c == '\0')
		return (NULL);
	else if (!ft_isalpha((int)c) && c != '_')
		ft_memmove(*pos, *pos + 1, ft_strlen(*pos + 1) + 1);
	else if (ft_isalpha((int)c) || c == '_')
	{
		while (ft_isalpha((int)*(*pos + 1 + *var_len)) || ft_isdigit((int)*(*pos
					+ 1 + *var_len)) || *(*pos + 1 + *var_len) == '_')
			(*var_len)++;
	}
	return (var_len);
}

void	expand_heredoc(char **str, t_exp *utils)
{
	int		tmp;
	char	*pos;
	char	*var_value;
	char	*var_name;
	int		*var_len;

	tmp = 0;
	utils->str = str;
	var_value = NULL;
	pos = ft_strchr(*str + tmp, '$');
	while (pos)
	{
		var_len = check_char_behind(&pos);
		if (var_len)
			var_value = get_var(pos, &var_name, *var_len, utils);
		if (var_value)
			tmp = insert_var(str, pos, var_value, var_name);
		else
		{
			ft_memmove(pos, pos + 1 + *var_len, ft_strlen(pos));
			tmp++;
		}
		pos = ft_strchr(*str + tmp, '$');
	}
	return ;
}
