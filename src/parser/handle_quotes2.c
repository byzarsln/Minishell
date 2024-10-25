/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayirmili <ayirmili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:49:05 by ayirmili          #+#    #+#             */
/*   Updated: 2024/10/25 14:58:09 by ayirmili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	if_quotes_and_default(t_token **token_node, int i)
{
	if (((*token_node)->value[i] == '\'' || (*token_node)->value[i] == '\"')
		&& (*token_node)->status == DEFAULT)
		return (SUCCESS);
	else
		return (FAILURE);
}

void	change_status_to_quote(t_token **token_node, int *i)
{
	if ((*token_node)->value[*i] == '\'')
		(*token_node)->status = SQUOTE;
	if ((*token_node)->value[*i] == '\"')
		(*token_node)->status = DQUOTE;
	(*i)++;
}

int	change_back_to_default(t_token **token_node, int *i)
{
	if (((*token_node)->value[*i] == '\'' && (*token_node)->status == SQUOTE)
		|| ((*token_node)->value[*i] == '\"' && (*token_node)->status == DQUOTE))
	{
		(*token_node)->status = DEFAULT;
		(*i)++;
		return (SUCCESS);
	}
	else
		return (FAILURE);
}
