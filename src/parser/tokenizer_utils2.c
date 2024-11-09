/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayirmili <ayirmili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 13:26:10 by beyarsla          #+#    #+#             */
/*   Updated: 2024/11/07 22:31:16 by ayirmili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	handle_heredoc_append(t_token **token_lst, char *user_input, int index,
		int type)
{
	int		i;
	char	*seperator;

	i = 0;
	seperator = malloc(sizeof(char) * 3);
	if (!seperator)
		return (FAILURE);
	while (i < 2)
		seperator[i++] = user_input[index++];
	seperator[i] = '\0';
	lst_add_back_token(token_lst, lst_new_token(seperator, NULL, type,
			DEFAULT));
	return (SUCCESS);
}

int	consec_define(t_token *temp_token)
{
	if (temp_token->prev)
	{
		if (temp_token->type == PIPE && temp_token->prev->type == PIPE)
			return (FAILURE);
		if (temp_token->type > PIPE && temp_token->prev->type > PIPE)
			return (FAILURE);
		if (temp_token->type == END && temp_token->prev->type >= PIPE)
			return (FAILURE);
	}
	return (SUCCESS);
}

int	consecutive_check(t_token **temp_lst)
{
	t_token	*tmp;

	tmp = *temp_lst;
	while (tmp)
	{
		if (consec_define(tmp) == FAILURE)
		{
			if (tmp->type == END && tmp->prev && tmp->prev->type > PIPE)
				printf("syntax error near unexpected token `newline'\n");
			else if (tmp->type == END && tmp->prev)
				printf("syntax error near unexpected token %s\n",
					tmp->prev->value);
			else
				printf("syntax error near unexpected token %s\n", tmp->value);
			return (FAILURE);
		}
		tmp = tmp->next;
	}
	return (SUCCESS);
}

static void	variable_cont(t_token **temp_lst)
{
	int	i;

	i = 0;
	while ((*temp_lst)->value[i])
	{
		if ((*temp_lst)->value[i] == '$')
		{
			if ((*temp_lst)->prev && (*temp_lst)->prev->type == HEREDOC)
				break ;
			(*temp_lst)->type = VAR;
			return ;
		}
		i++;
	}
}

int	check_var(t_token **token_lst)
{
	t_token	*temp_list;

	temp_list = *token_lst;
	if (temp_list->type == PIPE)
	{
		printf("syntax error near unexpected token %s\n", temp_list->value);
		return (FAILURE);
	}
	while (temp_list)
	{
		variable_cont(&temp_list);
		if (consecutive_check(&temp_list) == FAILURE)
			return (FAILURE);
		temp_list = temp_list->next;
	}
	return (SUCCESS);
}
