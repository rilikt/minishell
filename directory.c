/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   directory.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 16:32:16 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/06 17:43:30 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

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

void change_directory(char *move_to)
{
	char path[1024];
	char *new_path;

	getcwd(path, sizeof(path)); // get the current dir and append onto it
	
	if (!ft_strchr(move_to, '/'))
	{
		if (path[ft_strlen(path)-1] != '/')
		move_to = ft_strjoin("/", move_to);
		new_path = ft_strjoin(path, move_to);
	
		if (chdir(new_path) == -1)
		{
			perror("chdir in change_directory\n");
		}
	}
	else 
	{
		if (chdir(move_to) == -1)
		{
			perror("chdir in change_directory\n");
		}
	}
	return;
}