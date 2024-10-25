/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyarsla <beyarsla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:10:24 by beyarsla          #+#    #+#             */
/*   Updated: 2024/10/25 19:22:10 by beyarsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fill_args(t_token **token_node, t_command *last_cmd)
{
	if (!ft_strncmp(last_cmd->command, "echo", ft_strlen(last_cmd->command)))
	{
		if (!(last_cmd->args))
			return (create_args_echo_mode(token_node, last_cmd));
		else
			printf("YETER\n");
			// return (add_args_echo_mode(token_node, last_cmd));
	}
	else
	{
		if (last_cmd && !(last_cmd->args))
			return (create_args_default_mode(token_node, last_cmd));
		else
			return (add_args_default_mode(token_node, last_cmd));
	}
	return (SUCCESS);
}

t_command	*lst_last_cmd(t_command *cmd)
{
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}

bool	contains_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (true);
		i++;
	}
	return (false);
}

void	split_var_cmd_token(t_command *last_cmd, char *cmd_str)
{
	t_token		*new_tokens;
	t_token		*tmp;
	char		**strs;
	int			i;

	new_tokens = NULL;
	strs = ft_split(cmd_str, ' ');
	if (!strs)
		return ;
	last_cmd->command = ft_strdup(strs[0]);
	if (strs[1])
		new_tokens = lst_new_token(ft_strdup(strs[1]), NULL, WORD, DEFAULT);
	tmp = new_tokens;
	i = 1;
	while (strs[++i])
		lst_add_back_token(&new_tokens ,
			lst_new_token(ft_strdup(strs[i]), NULL, WORD, DEFAULT));
	lst_add_back_token(&new_tokens,
		lst_new_token(NULL, NULL, END, DEFAULT));
	fill_args(&new_tokens, last_cmd);
	lst_clear_token(&tmp, &free_pointr);
	free_str_tab(strs);
}
