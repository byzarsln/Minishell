/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayirmili <ayirmili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 15:34:51 by beyarsla          #+#    #+#             */
/*   Updated: 2024/11/07 20:59:05 by ayirmili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	lst_delone_cmd(t_command *cmd, void (*del)(void *))
{
	if (del && cmd && cmd->command)
		(*del)(cmd->command);
	if (del && cmd && cmd->args)
		free_mult_str(cmd->args);
	if (del && cmd && cmd->pipe_fd)
		(*del)(cmd->pipe_fd);
	if (del && cmd && cmd->io_fds)
		free_io(cmd->io_fds);
	(*del)(cmd);
}

void	lst_delone_token(t_token *token_node, void (*del)(void *))
{
	if (token_node && token_node->value)
	{
		(*del)(token_node->value);
		token_node->value = NULL;
	}
	if (token_node && token_node->value_backup)
	{
		(*del)(token_node->value_backup);
		token_node->value_backup = NULL;
	}
	if (token_node->prev)
		token_node->prev->next = token_node->next;
	if (token_node->next)
		token_node->next->prev = token_node->prev;
	free(token_node);
}

void	lst_clear_token(t_token **token_lst, void (*del)(void *))
{
	t_token	*tmp;

	if (!token_lst)
		return ;
	while (*token_lst)
	{
		tmp = (*token_lst)->next;
		lst_delone_token(*token_lst, del);
		*token_lst = tmp;
	}
	*token_lst = NULL;
}

void	lst_clear_cmd(t_command **command, void (*del)(void *))
{
	t_command	*tmp;

	if (!command)
		return ;
	while (*command)
	{
		tmp = (*command)->next;
		lst_delone_cmd(*command, del);
		*command = tmp;
	}
	*command = NULL;
}

void	free_data(t_data *data, bool clear_history)
{
	if (data && data->token)
		lst_clear_token(&data->token, &free_pointr);
	if (data && data->cmd)
		lst_clear_cmd(&data->cmd, &free_pointr);
	if (data && data->user_input)
	{
		free_pointr(data->user_input);
		data->user_input = NULL;
	}
	if (clear_history == true)
	{
		if (data && data->env)
			free_mult_str(data->env);
		if (data && data->export_env)
			free_mult_str(data->export_env);
		if (data && data->work_direc)
			free_pointr(data->work_direc);
		if (data && data->old_work_direc)
			free_pointr(data->cmd);
		rl_clear_history();
	}
}
