/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 09:50:22 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/02 16:33:21 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

t_token	*check_redir(t_cmd **command, t_token *tkn_temp)
{
	char	*filename;
	int		type;
	int		is_var;
	char	*vars;

	filename = NULL;
	is_var = 0;
	vars = NULL;
	if (!is_redir(tkn_temp))
		return (tkn_temp);
	type = tkn_temp->type;
	tkn_temp = tkn_temp->next;
	if (tkn_temp->type == PIPE)
		ft_error("redir syntax error", ERR_SYNTAX);
	if (tkn_temp)
	{
		filename = tkn_temp->str;
		if (tkn_temp->type == VARIABLE)
		{
			is_var = 1;
			vars = ft_strjoin(vars, tkn_temp->vars);
		}
		tkn_temp = tkn_temp->next;
	}
	append_rdct_node(command, type, filename, is_var, vars);
	tkn_temp = check_redir(command, tkn_temp);
	return (tkn_temp);
}

void	append_rdct_node(t_cmd **head, int type, char *filename, int is_var, char *vars)
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
	new_node->vars = vars;
	if (is_var)
		command->var_in_redir++;
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
