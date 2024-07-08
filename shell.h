/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:17:50 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/08 15:36:07 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

#include "include/libft/libft.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>

extern char **environ;

char *read_input(void);
char **parse_input(char *str);
void execute_commands(char **arg);
void signal_handle(int signum);
void go_home(void);
void change_directory(char *move_to);
void display_pwd(void);
void exit_shell(void);
void clean_shell(char **str);
void print_env(void);

#endif