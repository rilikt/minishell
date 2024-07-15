/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timschmi <timschmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/06 12:48:13 by timschmi          #+#    #+#             */
/*   Updated: 2024/07/15 14:27:03 by timschmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../shell.h"


void print_commands(t_shell *shell)
{
	t_shell *temp = shell;

	int cmd_i = 1;
	int redir_i = 0;
	int i = 0;

	while(temp->commands)
	{
		redir_i = 1;
		i = 0;
		printf("-command%d- :", cmd_i);
		while (temp->commands->args[i])
		{
			printf("%s ", temp->commands->args[i]);
			i++;
		}
		printf("is var: %d var in redir %d ", temp->commands->is_var, temp->commands->var_in_redir);
		if (temp->commands->reds)
		{
			printf("redirections: ");
			while(temp->commands->reds)
			{
				printf("nr:%d type: %d filename: %s ", redir_i, temp->commands->reds->type, temp->commands->reds->filename);
				temp->commands->reds = temp->commands->reds->next;
				redir_i++;
			}
		}
		printf("\n");
		temp->commands = temp->commands->next;
		cmd_i++;
	}
}

int is_redir(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == IN_REDIRECT)
		return(1);
	else if (token->type == IN_HEREDOC)
		return(1);
	else if (token->type == OUT_REDIRECT)
		return(1);
	else if (token->type == OUT_RED_APPEND)
		return(1);
	return (0);
}

void print_arr(char **arr)
{
	int i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

char **create_array(t_token *start, t_token *end)
{
	t_token *temp_start = start;
	int str_count = 0;
	int i = 0;
	char **arr;

	while (temp_start != end)
	{
		str_count++;
		temp_start = temp_start->next;
	}
	arr = (char **)malloc(str_count+1);
	if (!arr)
		ft_error("malloc error", ERR_MALLOC);
	arr[str_count] = NULL;
	while (i < str_count)
	{
		arr[i] = (char *)malloc(ft_strlen(start->str));
		if (!arr[i])
			ft_error("malloc error", ERR_MALLOC);
		arr[i] = start->str;
		start = start->next;
		i++;
	}
	return (arr);
}

void append_cmd_node(t_cmd **head, char **arr, int is_var)
{
	t_cmd *new_node;
	t_cmd *temp;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
			ft_error("malloc error", ERR_MALLOC);
	new_node->next = NULL;
	new_node->reds = NULL;
	new_node->args = arr;
	new_node->var_in_redir = 0;
	new_node->is_var = is_var;
	if (*head == NULL)
	{
		*head = new_node;
		return;
	}
	temp = *head;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}

void append_rdct_node(t_cmd **command, int type, char *filename, int is_var)
{
	t_rdct *new_node;
	t_rdct *temp;

	new_node = (t_rdct *)malloc(sizeof(t_rdct));
	if (!new_node)
			ft_error("malloc error", ERR_MALLOC);
	new_node->next = NULL;
	new_node->type = type;
	new_node->filename = filename;
	if (is_var)
		(*command)->var_in_redir = 1;
	if ((*command)->reds == NULL)
	{
		(*command)->reds = new_node;
		return;
	}
	temp = (*command)->reds;
	while (temp->next)
		temp = temp->next;
	temp->next = new_node;
}


t_token *check_redir(t_cmd **command, t_token *tkn_temp)
{
	t_cmd *cmd_temp = *command;
	char *filename = NULL;
	int type;
	int is_var = 0;
	
	if (!is_redir(tkn_temp))
		return (tkn_temp);
	printf("entered redir \n");
	while (cmd_temp->next)
		cmd_temp = cmd_temp->next;

	type = tkn_temp->type;
	tkn_temp = tkn_temp->next;

	while(tkn_temp && (tkn_temp->type != PIPE && !is_redir(tkn_temp)))
	{
		if (tkn_temp->str[0] == '$')
			is_var = 1;
		filename = ft_strjoin(filename, tkn_temp->str); // what can be the valid input for a filename more than 1? sperated by space?
		tkn_temp = tkn_temp->next;
	}

	append_rdct_node(&cmd_temp, type, filename, is_var);
	tkn_temp = check_redir(command, tkn_temp);
	return(tkn_temp);
}

void parse_tokens(t_shell *shell) // how to index env variables $$ ? no type in struct
{
	t_token *temp = shell->tokens;
	t_token *start;
	t_cmd *command = NULL;
	char **arr;
	int is_var;

	while(temp)
	{
		is_var = 0;
		start = temp;
		while(temp && (temp->type != PIPE && !is_redir(temp))) // make it check for all redir
		{
			if (temp->type == VARIABLE)
				is_var = 1;
			temp = temp->next;
		}
		arr = create_array(start, temp);
		// print_arr(arr);
		append_cmd_node(&command, arr, is_var);
		temp = check_redir(&command, temp); // move to current / latest command / look for redir and append node if needed
		if (temp)
		{
			// printf("%s\n", temp->str);
			temp = temp->next;
		}
	}
	shell->commands = command;
}

// void parse_input(char **arg)
// {
// 	t_cmd *cmd = NULL;
// 	int i = 0;
// 	int j = 0;

// 	while(arg[i])
// 	{
// 		if (check_operators(arg[i]))	// if no operator found it has to be a single command 
// 			append_node(&cmd, arg, i);	// maybe iterate trough it muliple times changing operator based on priority
			
// 		i++;
// 	}
// 	print_list(cmd);
// }
