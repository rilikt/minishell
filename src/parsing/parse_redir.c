/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 09:50:22 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/12 17:57:17 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

int	check_redir(t_cmd **command, t_token **tkn_temp, int *err)
{
	t_redir_val	redir;

	redir.filename = NULL;
	redir.int_vars = NULL;
	redir.vars = NULL;
	if (!is_redir(*tkn_temp))
		return (0);
	redir.type = (*tkn_temp)->type;
	*tkn_temp = (*tkn_temp)->next;
	if (!(*tkn_temp) || ((*tkn_temp)->type == PIPE) || is_redir((*tkn_temp)))
		return (ft_sytax_error(err, *tkn_temp), ERR_SYNTAX);
	if (*tkn_temp)
	{
		redir.filename = (*tkn_temp)->str;
		if ((*tkn_temp)->type == VARIABLE)
		{
			redir.vars = ft_strjoin(redir.vars, (*tkn_temp)->char_vars);
			redir.int_vars = add_to_arr(redir.vars, (*tkn_temp)->int_vars,
					(*tkn_temp)->char_vars, redir.int_vars);
		}
		*tkn_temp = (*tkn_temp)->next;
	}
	append_rdct_node(command, &redir);
	return (check_redir(command, tkn_temp, err));
}

void	append_rdct_node(t_cmd **head, t_redir_val *redir)
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
	new_node->type = redir->type;
	new_node->filename = redir->filename;
	new_node->char_vars = redir->vars;
	new_node->int_vars = redir->int_vars;
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
