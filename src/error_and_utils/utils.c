/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:19:54 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/13 16:39:59 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"






// void clean_shell(char **str)
// {
// 	int i;

// 	i = 0;
// 	while(str[i])
// 	{
// 		free(str[i]);
// 		i++;
// 	}
// 	free(str);
// }

// void print_list(t_cmd *head)
// {
// 	t_cmd *temp = head;

// 	while (temp)
// 	{
// 		printf("operator: %s, command1: %s, argument1: %s, command2: %s, argument2: %s\n", temp->op, temp->cmd1, temp->arg1, temp->cmd2, temp->arg2);
// 		temp = temp->next;
// 	}
// }




// void find_arg1(t_cmd *node, char **arg, int i)
// {
// 	char *str = NULL;
// 	int j = i;

// 	i--;
// 	while (i > 0) // moves back to the start of the input or the next operator before
// 	{
// 		if (check_operators(arg[i]))
// 		{
// 			i++;
// 			break;
// 		}
// 		i--;
// 	}
// 	node->cmd1 = arg[i]; // stores the command 
// 	i++;
// 	while(i < j) // joins arguments for commands into a single str
// 	{
// 		str = ft_strjoin(str, arg[i]);
// 		i++;
// 		if (i < j)
// 			str = ft_strjoin(str, " ");
// 	}
// 	node->arg1 = str;
// 	return ;
// }

// void find_arg2(t_cmd *node, char **arg, int i)
// {
// 	char *str2 = NULL;

// 	i++;
// 	int j = i;
// 	while (arg[i])
// 	{
// 		if (check_operators(arg[i]))
// 			break;
// 		i++;
// 	}
// 	node->cmd2 = arg[j];
// 	j++;
// 	while(j < i)
// 	{
// 		str2 = ft_strjoin(str2, arg[j]);
// 		j++;
// 		if (j < i)
// 			str2 = ft_strjoin(str2, " ");
// 	}
// 	node->arg2 = str2;
// 	return ;
// }

// t_cmd *set_values(t_cmd **node, char **arg, int i)
// {
// 	t_cmd *temp = *node;
// 	temp->op = arg[i]; // check operator and proceed accordingly

// 	find_arg1(temp, arg, i); 
	
// 	find_arg2(temp, arg , i);

// 	return (temp);
// }

// int find_type(char *str)
// {
// 	char *operator = "|<>";

// 	int i = 0;
// 	int j = 0;
// 	int len = ft_strlen(str);

// 	while (operator[i])
// 	{
// 		if (str[j] == operator[i])
// 		{
// 			if (str[j] == '|')
// 				return (PIPE);
// 			else if (str[j] == '<' && len == 1)
// 				return (IN_REDIRECT);
// 			else if (str[j] == '>' && len == 1)
// 				return (OUT_REDIRECT);
// 			else if (str[j] == '<')
// 				return (IN_HEREDOC);
// 			else if (str[j] == '>')
// 				return (OUT_RED_APPEND);
// 		}
// 		i++;
// 	}
// 	return(WORD);
// }

// t_token *create_node(char *str)
// {
// 	t_token *new_node;

// 	new_node = (t_token *)malloc(sizeof(t_token));
// 	// if (!new_node)
// 	// 	exit_error();

// 	new_node->next = NULL;
// 	new_node->prev = NULL;
// 	new_node->str = str;
// 	new_node->type = find_type(str);

// 	return (new_node);
// }

// void append_node(t_token **head, char *str)
// {
// 	t_token *new_node;
// 	t_token *temp;

// 	new_node = create_node(str);
// 	if (*head == NULL)
// 	{
// 		*head = new_node;
// 		return;
// 	}
// 	temp = *head;
// 	while (temp->next)
// 		temp = temp->next;
// 	temp->next = new_node;
// 	new_node->prev = temp;
// 	return ;
// }
