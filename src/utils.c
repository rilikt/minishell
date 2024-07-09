/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:19:54 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/09 16:59:52 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../shell.h"

void clean_shell(char **str)
{
	int i;

	i = 0;
	while(str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

t_cmd *create_node()
{
	t_cmd *new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	
	return (new_node);
}


void find_arg1(t_cmd *node, char **arg, int i)
{
	char *str = NULL;
	int j = i;

	i--;
	while (i > 0) // moves back to the start of the input or the next operator before
	{
		if (check_operators(arg[i]))
		{
			i++;
			break;
		}
		i--;
	}
	node->cmd1 = arg[i]; // stores the command
	i++;
	while(i < j) // joins arguments for commands into a single str
	{
		str = ft_strjoin(str, arg[i]);
		i++;
		if (i < j)
			str = ft_strjoin(str, " ");
	}
	node->arg1 = str;
	free (str);
	printf("command: %s, argument: %s\n", node->cmd1, node->arg1);
	return ;
}

void find_arg2(t_cmd *node, char **arg, int i)
{
	char *str2 = NULL;

	i++;
	int j = i;
	while (arg[i])
	{
		if (check_operators(arg[i]))
			break;
		i++;
	}
	node->cmd2 = arg[j];
	j++;
	while(j < i)
	{
		str2 = ft_strjoin(str2, arg[j]);
		j++;
		if (j < i)
			str2 = ft_strjoin(str2, " ");
	}
	node->arg2 = str2;
	free(str2);
	printf("command: %s, argument: %s\n", node->cmd2, node->arg2);
	return ;
}

void set_values(t_cmd *node, char **arg, int i)
{
	node->op = arg[i]; 

	find_arg1(node, arg, i);
	
	find_arg2(node, arg , i);
}

void append_node(t_cmd *head, char **arg, int i)
{
	t_cmd *new_node;

	new_node = create_node();
	set_values(new_node, arg, i);
	if (head == NULL)
	{
		head = new_node;
		head->next = NULL;
		return;
	}

	new_node->next = NULL;
	return ;
}
