/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:32:16 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/21 17:16:32 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void go_home(void) //moves the current working dir to root
{
	char *user;
	char *path;

	user = getenv("LOGNAME");
	path = ft_strjoin("/Users/", user);

	if (chdir(path) == -1)
	{
		perror("chdir in go_home\n");
	}
	return;
}

void cd(char **arg)
{
	char path[1024];
	char *new_path;
	char *input = arg[1];
	char *move_to = arg[1];

	if (arg[2])
	{
		write(2, "cd : too many arguments\n", 25);
		return;
	}

	getcwd(path, sizeof(path)); // get the current dir and append onto it
	
	if (!ft_strchr(move_to, '/')) // for relative path containing 
	{
		if (path[ft_strlen(path)-1] != '/')
		move_to = ft_strjoin("/", move_to);
		move_to = ft_strjoin(path, move_to);
	}
	if (chdir(move_to) == -1)
	{
		fprintf(stderr, "cd : %s %s\n", strerror(errno), input);
	}

	return;
}

void pwd(char **arg)
{
	char path[1024];
	
	if (arg[1])
	{
		write(2, "pwd : too many arguments\n", 25);
		return;
	}
	printf("%s\n", getcwd(path, sizeof(path)));
	return;
}