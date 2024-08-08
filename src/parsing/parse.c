/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:48:13 by timschmi          #+#    #+#             */
/*   Updated: 2024/08/07 18:49:44 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"


int *add_to_arr(char *vars, int *arr, char *added, int *int_vars)
{
	int *re;
	int len;
	int i;
	int j;

	i = 0;
	j = 0;
	len = ft_strlen(vars) - ft_strlen(added);
	re = (int*)malloc(ft_strlen(vars) * sizeof(int));
	error_check(re, "add_to_arr", ERR_MALLOC);
	while(i < len)
	{
		re[i] = int_vars[i];
		i++;
	}
	len = ft_strlen(vars);
	while (i < len)
	{
		re[i] = arr[j];
		i++;
		j++;
	}
	//free(int_vars);
	return(re);
}


void	while_not_op(t_token **temp, t_shell *shell, char **vars, int **int_vars)
{
	while ((*temp) && ((*temp)->type != PIPE && !is_redir((*temp))))
	{
		if ((*temp)->type == VARIABLE)
		{
			*vars = ft_strjoin(*vars, (*temp)->char_vars);
			*int_vars = add_to_arr(*vars, (*temp)->int_vars, (*temp)->char_vars, *int_vars);
		}
		(*temp) = (*temp)->next;
	}
	if ((*temp) && (*temp)->type == PIPE)
	{
		if (!(*temp)->next)
			ft_sytax_error(&shell->err, *temp);
		else if ((*temp)->next->type == PIPE)
			ft_sytax_error(&shell->err, *temp);
		else if ((*temp) == shell->tokens)
			ft_sytax_error(&shell->err, *temp);
		else if (is_redir((*temp)->prev))
			ft_sytax_error(&shell->err, *temp);
	}
}

t_cmd	*parse_loop(t_token *temp, t_cmd *command, t_shell *shell, char **arr)
{
	t_token	*start;
	char	*vars;
	int		*int_vars;

	while (temp && !shell->err)
	{
		vars = NULL;
		int_vars = NULL;
		start = temp;
		append_cmd_node(&command);
		while_not_op(&temp, shell, &vars, &int_vars);
		arr = create_array(start, temp);
		if (is_redir(temp))
		{
			if(check_redir(&command, &temp, &shell->err))
				return(shell->exitstatus = 2, command);
			start = temp;
			while_not_op(&temp, shell, &vars, &int_vars);
			arr = append_array(arr, start, temp);
		}
		store_in_cmd(&command, arr, vars, int_vars);
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
