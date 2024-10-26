/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyza <beyza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 21:14:04 by ayirmili          #+#    #+#             */
/*   Updated: 2024/10/26 18:03:39 by beyza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parse_cmd_trunc(t_command **last_cmd, t_token **token_lst)
{
	t_token		*temp;
	t_command	*cmd;

	temp = *token_lst;
	cmd = lst_last_cmd(*last_cmd);
	init_io(cmd);
	open_outfile_trunc(cmd->io_fds, temp->next->value,
		temp->next->value_backup);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}

void	parse_cmd_input(t_command **last_cmd, t_token **token_lst)
{
	t_token		*temp;
	t_command	*cmd;

	temp = *token_lst;
	cmd = lst_last_cmd(*last_cmd);
	init_io(cmd);
	open_infile(cmd->io_fds, temp->next->value, temp->next->value_backup);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}

void	lst_add_back_cmd(t_command **alst, t_command *new_node)
{
	t_command	*start;

	start = *alst;
	if (start == NULL)
	{
		*alst = new_node;
		return ;
	}
	if (alst && *alst && new_node)
	{
		while (start->next != NULL)
			start = start->next;
		start->next = new_node;
		new_node->prev = start;
	}
}
