/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:48:13 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/03 15:08:58 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"


void	create_var_list(t_shell *shell)
{
	char	*vars;
	int		i;

	vars = NULL;
	i = 0;
	while (shell->input[i])
	{
		if (shell->input[i] == 39)
		{
			i++;
			while (shell->input[i] && (shell->input[i] != 39))
			{
				if (shell->input[i] == '$') // myb check for whitespace after and set flag accordingly
					vars = ft_strjoin(vars, "0");
				i++;
			}
		}
		if (shell->input[i] == '$')
		{
			if ((shell->input[i+1] == 39 || shell->input[i+1] == 34))
				vars = ft_strjoin(vars, "2");
			else
				vars = ft_strjoin(vars, "1");
		}
		
		i++;
	}
	shell->vars = vars;
}

void	while_not_op(t_token **temp, int *is_var, t_shell *shell, char **vars)
{
	while ((*temp) && ((*temp)->type != PIPE && !is_redir((*temp))))
	{
		if ((*temp)->type == VARIABLE)
		{
			(*is_var)++;
			*vars = ft_strjoin(*vars, (*temp)->vars);
		}
		(*temp) = (*temp)->next;
	}
	if ((*temp) && (*temp)->type == PIPE)
	{
		if (!(*temp)->next)
			shell->err = ERR_SYNTAX;
		else if ((*temp)->next->type == PIPE)
			shell->err = ERR_SYNTAX;
		else if ((*temp) == shell->tokens)
			shell->err = ERR_SYNTAX;
		else if (is_redir((*temp)->prev))
			shell->err = ERR_SYNTAX;
	}
}

t_cmd	*parse_loop(t_token *temp, t_cmd *command, t_shell *shell, char **arr)
{
	int		is_var;
	t_token	*start;
	char	*vars;

	while (temp)
	{
		vars = NULL;
		is_var = 0;
		start = temp;
		append_cmd_node(&command);
		while_not_op(&temp, &is_var, shell, &vars);
		arr = create_array(start, temp);
		if (is_redir(temp))
		{
			if(check_redir(&command, &temp, &shell->err))
				return(command);
			start = temp;
			while_not_op(&temp, &is_var, shell, NULL);
			arr = append_array(arr, start, temp);
		}
		store_in_cmd(&command, arr, is_var, vars);
		if (temp)
			temp = temp->next;
	}
	return (command);
}

void	parse_tokens(t_shell *shell)
{
	t_token	*temp;
	t_token	*start;
	t_cmd	*command;
	int		is_var;
	char	**arr;

	shell->cmd_nb = 0;
	temp = shell->tokens;
	command = NULL;
	arr = NULL;
	shell->commands = parse_loop(temp, command, shell, arr);
	command = shell->commands;
	while (command)
	{
		shell->cmd_nb += 1;
		command = command->next;
	}
}
