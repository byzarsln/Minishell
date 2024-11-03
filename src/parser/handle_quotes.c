/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyarsla <beyarsla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:18:14 by ayirmili          #+#    #+#             */
/*   Updated: 2024/11/03 16:38:43 by beyarsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_any_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			return (SUCCESS);
		i++;
	}
	return (FAILURE);
}

static int	count_len(char *str, int count, int i)
{
	int	status;

	status = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && status == DEFAULT)
		{
			if (str[i] == '\'')
				status = SQUOTE;
			if (str[i] == '\"')
				status = DQUOTE;
			i++;
			continue ;
		}
		else if ((str[i] == '\'' && status == SQUOTE) || (str[i] == '\"'
				&& status == DQUOTE))
		{
			status = DEFAULT;
			i++;
			continue ;
		}
		count++;
		i++;
	}
	return (count + 1);
}

int	remove_quotes(t_token **token_node)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_line = malloc(sizeof(char) * count_len((*token_node)->value, i, i));
	if (!new_line)
		return (1);
	while ((*token_node)->value[i])
	{
		printf("toke->value: %c, ", (*token_node)->value[i]);
		printf("toke->status: %d\n", (*token_node)->status);
		if (if_quotes_and_default(token_node, i) == SUCCESS)
		{
			change_status_to_quote(token_node, &i);
			continue ;
		}
		else if (change_back_to_default(token_node, &i) == SUCCESS)
			continue ;
		new_line[j++] = (*token_node)->value[i++];
	}
	new_line[j] = '\0';
	free_pointr((*token_node)->value);
	(*token_node)->value = new_line;
	(*token_node)->join = true;
	return (0);
}

int	dollar_check_quote(char *str, t_data *data)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = 0;
	if (str[0] == '\"' && str[len -1] == '\"')
		return (DLLR_IN_DQUOTE);
	while (str[i])
	{
		if (str[i] == '$')
			handle_dollar(data, &data->token);
		i++;
	}
	return(SUCCESS);
}

int	handle_quotes(t_data *data)
{
	t_token	*temp;

	temp = data->token;
	while (temp)
	{
		if (is_any_quotes(temp->value) == SUCCESS && (!temp->prev || (temp->prev
					&& temp->prev->type != HEREDOC) && temp->type != VAR))
				remove_quotes(&temp);
		else if (temp->type == VAR)
		{
			if (dollar_check_quote(temp->value, data) == DLLR_IN_DQUOTE)
				remove_quotes(&temp);
		}
		temp = temp->next;
	}
	return (0);
}
