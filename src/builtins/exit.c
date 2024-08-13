/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 17:08:42 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/13 15:57:21 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	exit_msg(char *str)
{
	// write(1, "exit\n", 6);
	write(2, "minishell: exit: ", 18);
	write(2, str, ft_strlen(str));
	write(2, ": numeric argument required\n", 28);
}

int	num_check(char *str)
{
	int	i;

	i = 1;
	if (ft_isalpha(str[0]))
		return (1);
	if (str[0] == '-' && !ft_isdigit(str[1]))
		return (1);
	else if (str[0] == '+' && !ft_isdigit(str[1]))
		return (1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

long long int	ft_longtoi(const char *str)
{
	int				i;
	int				sign;
	long long int	num;

	num = 0;
	i = 0;
	sign = 1;
	while (str[i] && (str[i] == ' ' || str[i] == '\f' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == '\t' || str[i] == '\v'))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - '0');
		i++;
	}
	return (sign * num);
}

int	ft_intlen(long long int n)
{
	int	len;

	len = 0;
	if (n == LLONG_MIN)
		n += 1;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	ft_exit(char **args, int *err, int exitstatus)
{
	long long int	re;
	int				i;
	int				clen;
	int				ilen;

	i = 0;
	if (!args[1])
		return (*err = 1, exitstatus);
	if (args[1][0] == '\0' || num_check(args[1]))
		return (*err = 1, exit_msg(args[1]), 255);
	if (args[2])
		return (write(2, "minishell: exit: too many arguments\n", 37), 1);
	clen = ft_strlen(args[1]);
	re = ft_longtoi(args[1]);
	if (re == LLONG_MAX || re == LLONG_MIN)
	{
		ilen = ft_intlen(re);
		if (clen != ilen)
			return (*err = 1, exit_msg(args[1]), 255);
	}
	if (re < 0)
		re = (re % 256 + 256) % 256;
	else if (re > 255)
		re %= 256;
	return (*err = 1, re);
}
