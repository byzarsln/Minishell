/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyarsla <beyarsla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:06:41 by ayirmili          #+#    #+#             */
/*   Updated: 2024/11/03 16:23:26 by beyarsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	control_dlr_quote(t_token **token_node, char c)
{
	if (c == '\'' && (*token_node)->status == DEFAULT)
		(*token_node)->status = SQUOTE;
	else if (c == '\"' && (*token_node)->status == DEFAULT)
		(*token_node)->status = DQUOTE;
	else if (c == '\'' && (*token_node)->status == SQUOTE)
		(*token_node)->status = DEFAULT;
	else if (c == '\"' && (*token_node)->status == DQUOTE)
		(*token_node)->status = DEFAULT;
}

int	is_next_char_a_sep(char c)
{
	if (c == '$' || c == ' ' || c == '=' || c == '\0')
		return (SUCCESS);
	else
		return (FAILURE);
}

int	var_between_quotes(char *str, int i)
{
	if (i > 0)
	{
		if (str[i - 1] == '\"' && str[i + 1] == '\"')
			return (SUCCESS);
		else
			return (FAILURE);
	}
	return (FAILURE);
}

static char	*find_var(t_token *token, char *str, t_data *data)
{
	char	*value;
	char	*var;

	var = identify_var(str);
	if (var && var_exists(data, var) == 0)
	{
		if (token != NULL)
			token->var_exists = true;
		value = search_env_var(data, var);
	}
	else
		value = NULL;
	free_pointr(var);
	return (value);
}

void	handle_dollar(t_data *data, t_token **token_lst)
{
	t_token	*tmp;
	int		i;

	tmp = *token_lst;
	while (tmp)
	{
		if (tmp->type == VAR)
		{
			i = 0;
			while (tmp->value[i])
			{
				control_dlr_quote(&tmp, tmp->value[i]);
				if (tmp->value[i] == '$' && is_next_char_a_sep(tmp->value[i \
						+ 1]) == FAILURE && var_between_quotes(tmp->value,
						i) == FAILURE && (tmp->status == DEFAULT
						|| tmp->status == DQUOTE))
					handle_replace_var(&tmp, find_var(tmp, tmp->value + i,
							data), i);
				else
					i++;
			}
		}
		tmp = tmp->next;
	}
}
