/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayirmili <ayirmili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:18:14 by ayirmili          #+#    #+#             */
/*   Updated: 2024/11/07 22:25:45 by ayirmili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

int	remove_quotes_for_squote(t_token **input)
{
	int		len;
	int		i;
	int		j;
	char	*new_line;

	i = 1;
	j = 0;
	len = ft_strlen((*input)->value);
	new_line = malloc(sizeof(char) * len - 1);
	if (!new_line)
		return (1);
	while ((*input)->value[i] && i != (len - 1))
		new_line[j++] = (*input)->value[i++];
	new_line[j] = '\0';
	free_pointr((*input)->value);
	(*input)->value = new_line;
	(*input)->join = true;
	return (0);
}

static int	dollar_check_quote(char *str, t_data *data, int exit_code)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = 0;
	if (str[0] == '\"' && str[len - 1] == '\"')
		return (DLLR_IN_DQUOTE);
	else if (str[0] == '\'' && str[len - 1] == '\'')
		return (DLLR_IN_SQUOTE);
	while (str[i])
	{
		if (str[i] == '$')
			handle_dollar(data, &data->token, exit_code);
		i++;
	}
	return (SUCCESS);
}

int	handle_quotes(t_data *data, int exit_code)
{
	t_token	*temp;

	temp = data->token;
	while (temp)
	{
		if ((is_any_quotes(temp->value) == SUCCESS) && ((!temp->prev
					|| (temp->prev && temp->prev->type != HEREDOC))
				&& (temp->type != VAR)))
			remove_quotes(&temp);
		else if (temp->type == VAR)
		{
			if (dollar_check_quote(temp->value_backup, data,
					exit_code) == DLLR_IN_DQUOTE)
				remove_quotes(&temp);
			else if (dollar_check_quote(temp->value_backup, data,
					exit_code) == DLLR_IN_SQUOTE)
				remove_quotes_for_squote(&temp);
		}
		temp = temp->next;
	}
	return (0);
}
