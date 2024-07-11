/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:19:54 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/10 12:31:22 by timschmi         ###   ########.fr       */
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

void print_list(t_cmd *head)
{
	t_cmd *temp = head;

	while (temp)
	{
		printf("operator: %s, command1: %s, argument1: %s, command2: %s, argument2: %s\n", temp->op, temp->cmd1, temp->arg1, temp->cmd2, temp->arg2);
		temp = temp->next;
	}
}


t_cmd *create_node()
{
	t_cmd *new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));

	new_node->next = NULL;
	new_node->arg1 = NULL;
	new_node->arg2 = NULL;
	new_node->cmd1 = NULL;
	new_node->cmd2 = NULL;
	new_node->op = NULL;

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
	return ;
}

t_cmd *set_values(t_cmd **node, char **arg, int i)
{
	t_cmd *temp = *node;
	temp->op = arg[i]; // check operator and proceed accordingly

	find_arg1(temp, arg, i); 
	
	find_arg2(temp, arg , i);

	return (temp);
}

void append_node(t_cmd **head, char **arg, int i)
{
	t_cmd *new_node;

	new_node = create_node();
	new_node = set_values(&new_node, arg, i);
	if (*head == NULL)
	{
		*head = new_node;
		return;
	}
	return ;
}
