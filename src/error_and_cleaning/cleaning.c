/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:19:54 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/14 18:13:35 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void	free_tokens(t_shell *shell)
{
	t_token	*temp_tkn;
	t_shell	*temp;

	temp = shell;
	while (temp->tokens)
	{
		temp_tkn = temp->tokens;
		temp->tokens = temp->tokens->next;
		if (temp_tkn->str)
			free(temp_tkn->str);
		if (temp_tkn->char_vars)
		{
			free(temp_tkn->char_vars);
			free(temp_tkn->int_vars);
		}
		free(temp_tkn);
	}
}

void	free_struct(t_shell *shell)
{
	t_shell	*temp;
	t_cmd	*temp_cmd;
	t_rdct	*temp_redir;

	temp = shell;
	while (temp->commands)
	{
		temp_cmd = temp->commands;
		temp->commands = temp->commands->next;
		while (temp_cmd->reds)
		{
			temp_redir = temp_cmd->reds;
			temp_cmd->reds = temp_cmd->reds->next;
			if (temp_redir->filename)
				free(temp_redir->filename);
			if (temp_redir->char_vars)
			{
				free(temp_redir->char_vars);
				free(temp_redir->int_vars);
			}
			free(temp_redir);
		}
		if (temp_cmd->args)
			free_string_array(temp_cmd->args);
		if (temp_cmd->char_vars)
		{
			free(temp_cmd->char_vars);
			free(temp_cmd->int_vars);
		}
		free(temp_cmd);
	}
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	free(shell->char_vars);
	free(shell->int_vars);
}

void	free_string_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i])
			free(str[i]);
		i++;
	}
	free(str);
}
