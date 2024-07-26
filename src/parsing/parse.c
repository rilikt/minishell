/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:48:13 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/26 16:27:34 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"

void while_not_op(t_token **temp, int *is_var, t_token *start)
{
	while((*temp) && ((*temp)->type != PIPE && !is_redir((*temp))))
	{
		if ((*temp)->type == VARIABLE)
			(*is_var)++;
		(*temp) = (*temp)->next;
	}
	if ((*temp) && (*temp)->type == PIPE)
	{
		if (!(*temp)->next)
			ft_error("pipe syntax error", ERR_SYNTAX);
		else if((*temp)->next->type == PIPE)
			ft_error("pipe syntax error", ERR_SYNTAX);
		else if ((*temp) == start)
			ft_error("pipe syntax error", ERR_SYNTAX);
	}
}


void create_var_list(t_shell *shell)
{
	char *vars = NULL;
	int i = 0;
	char *flag;
	int start;
	while (shell->input[i])
	{
		flag = "1";
		if (shell->input[i] == 34 || shell->input[i] == 39)
		{
			start = i;
			if (shell->input[i] == 39)
				flag = "0";
			while(shell->input[i] != shell->input[start])
			{
				if (shell->input[i] == '$')
					vars = ft_strjoin(vars, flag);
				i++;
			}
		}
		else if (shell->input[i] == '$')
			vars = ft_strjoin(vars, flag);
		i++;
	}
	// printf("%s\n", vars);
}


void parse_tokens(t_shell *shell)
{
	t_token *temp = shell->tokens;
	t_token *start;
	t_cmd *command = NULL;
	shell->cmd_nb = 0;
	int is_var;
	char **arr;

	create_var_list(shell);
	while(temp)
	{
		is_var = 0;
		start = temp;
		append_cmd_node(&command);
		while_not_op(&temp, &is_var, shell->tokens);
		arr = create_array(start, temp);
		if (is_redir(temp))
		{
			temp = check_redir(&command, temp);
			start = temp;
			while_not_op(&temp, &is_var, shell->tokens);
			arr = append_array(arr, start, temp);
		}
		store_in_cmd(&command, arr, is_var);
		if (temp)
			temp = temp->next;
		shell->cmd_nb += 1;
	}
	shell->commands = command;
}
