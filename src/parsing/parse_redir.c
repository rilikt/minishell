/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 09:50:22 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/04 15:12:52 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int check_redir(t_cmd **command, t_token **tkn_temp, int *err)
{
	char	*filename;
	int		type;
	int		*int_vars;
	char	*vars;

	filename = NULL;
	int_vars = NULL;
	vars = NULL;
	if (!is_redir(*tkn_temp))
		return (0);
	type = (*tkn_temp)->type;
	*tkn_temp = (*tkn_temp)->next;
	if (!(*tkn_temp) || ((*tkn_temp)->type == PIPE) || is_redir((*tkn_temp)))
		return(ft_sytax_error(err, *tkn_temp), ERR_SYNTAX);
	if (*tkn_temp)
	{
		filename = (*tkn_temp)->str;
		if ((*tkn_temp)->type == VARIABLE)
		{
			vars = ft_strjoin(vars, (*tkn_temp)->char_vars);
			int_vars = add_to_arr(vars, (*tkn_temp)->int_vars, (*tkn_temp)->char_vars, int_vars);
		}
		*tkn_temp = (*tkn_temp)->next;
	}
	append_rdct_node(command, type, filename, vars, int_vars);
	check_redir(command, tkn_temp, err);
	return (0);
}

void	append_rdct_node(t_cmd **head, int type, char *filename, char *vars, int *int_vars)
{
	t_rdct	*new_node;
	t_rdct	*temp;
	t_cmd	*command;

	command = *head;
	while (command->next)
		command = command->next;
	new_node = (t_rdct *)malloc(sizeof(t_rdct));
	error_check(new_node, "append_rdct_node", ERR_MALLOC);
	new_node->next = NULL;
	new_node->type = type;
	new_node->filename = filename;
	new_node->char_vars = vars;
	new_node->int_vars = int_vars;
	if (command->reds == NULL)
	{
		command->reds = new_node;
		return ;
	}
	temp = command->reds;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

int	is_redir(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == IN_REDIRECT)
		return (1);
	else if (token->type == IN_HEREDOC)
		return (1);
	else if (token->type == OUT_REDIRECT)
		return (1);
	else if (token->type == OUT_RED_APPEND)
		return (1);
	return (0);
}
