/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayirmili <ayirmili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 16:24:52 by beyarsla          #+#    #+#             */
/*   Updated: 2024/11/03 21:48:58 by ayirmili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	initialize_cmd(t_command **cmd)
{
	(*cmd)->command = NULL;
	(*cmd)->path = NULL;
	(*cmd)->args = NULL;
	(*cmd)->pipe_output = false;
	(*cmd)->pipe_fd = 0;
	(*cmd)->prev = NULL;
	(*cmd)->next = NULL;
}

t_command	*lst_new_cmd(bool value)
{
	t_command	*new_node;

	new_node = (t_command *)malloc(sizeof(t_command));
	if (!(new_node))
		return (NULL);
	ft_memset(new_node, 0, sizeof(t_command));
	new_node->pipe_output = value;
	initialize_cmd(&new_node);
	return (new_node);
}

void	parse_cmd_word(t_command **cmd, t_token **token_lst)
{
	t_token		*temp;
	t_command	*last_cmd;

	temp = *token_lst;
	while (temp->type == WORD || temp->type == VAR)
	{
		last_cmd = lst_last_cmd(*cmd);
		if (temp->prev == NULL || (temp->prev && temp->prev->type == PIPE)
			|| last_cmd->command == NULL)
		{
			if (temp->type == VAR && contains_space(temp->value))
				split_var_cmd_token(last_cmd, temp->value);
			else
				last_cmd->command = ft_strdup(temp->value);
			temp = temp->next;
		}
		else
			fill_args(&temp, last_cmd);
	}
	*token_lst = temp;
}

static void	prep_no_arg_commands(t_data *data)
{
	t_command	*cmd;

	if (!data || !data->cmd)
		return ;
	cmd = data->cmd;
	while (cmd && cmd->command)
	{
		if (!cmd->args)
		{
			cmd->args = malloc(sizeof * cmd->args * 2);
			cmd->args[0] = ft_strdup(cmd->command);
			cmd->args[1] = NULL;
		}
		cmd = cmd->next;
	}
	cmd = lst_last_cmd(data->cmd);
}

void	create_commands(t_data *data, t_token *token, int exit_code)
{
	t_token	*tmp;

	tmp = token;
	if (tmp->type == END)
		return ;
	while (tmp->next != NULL)
	{
		if (tmp == token)
			lst_add_back_cmd(&data->cmd, lst_new_cmd(false));
		if (tmp->type == WORD || tmp->type == VAR)
			parse_cmd_word(&data->cmd, &tmp);
		else if (tmp->type == INPUT)
			parse_cmd_input(&data->cmd, &tmp);
		else if (tmp->type == TRUNC)
			parse_cmd_trunc(&data->cmd, &tmp);
		else if (tmp->type == HEREDOC)
			parse_cmd_heredoc(data, &data->cmd, &tmp, exit_code);
		else if (tmp->type == APPEND)
			parse_cmd_append(&data->cmd, &tmp);
		else if (tmp->type == PIPE)
			parse_cmd_pipe(&data->cmd, &tmp);
		else if (tmp->type == END)
			break ;
	}
	prep_no_arg_commands(data);
}
