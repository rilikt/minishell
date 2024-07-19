/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 09:50:22 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/19 11:42:49 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

t_token	*check_redir(t_cmd **command, t_token *tkn_temp)
{
	t_cmd	*cmd_temp;
	char	*filename;
	int		type;
	int		is_var;

	cmd_temp = *command;
	filename = NULL;
	is_var = 0;
	if (!is_redir(tkn_temp))
		return (tkn_temp);
	while (cmd_temp->next)
		cmd_temp = cmd_temp->next;
	type = tkn_temp->type;
	tkn_temp = tkn_temp->next;
	if (tkn_temp->type == PIPE)
		ft_error("redir syntax error", ERR_SYNTAX);
	if (tkn_temp)
	{
		filename = tkn_temp->str;
		if (tkn_temp->type == VARIABLE)
			is_var = 1;
		tkn_temp = tkn_temp->next;
	}
	append_rdct_node(&cmd_temp, type, filename, is_var);
	tkn_temp = check_redir(command, tkn_temp);
	return (tkn_temp);
}

void	append_rdct_node(t_cmd **command, int type, char *filename, int is_var)
{
	t_rdct	*new_node;
	t_rdct	*temp;

	new_node = (t_rdct *)malloc(sizeof(t_rdct));
	if (!new_node)
		ft_error("malloc error", ERR_MALLOC);
	new_node->next = NULL;
	new_node->type = type;
	new_node->filename = filename;
	if (is_var)
		(*command)->var_in_redir++;
	if ((*command)->reds == NULL)
	{
		(*command)->reds = new_node;
		return ;
	}
	temp = (*command)->reds;
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
