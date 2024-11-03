/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyarsla <beyarsla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:37:51 by ayirmili          #+#    #+#             */
/*   Updated: 2024/11/03 18:25:49 by beyarsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	set_status(int status, char c)
{
	if (c == '\'' && status == DEFAULT)
		status = SQUOTE;
	else if (c == '\'' && status == SQUOTE)
		status = DEFAULT;
	else if (c == '\"' && status == DEFAULT)
		status = DQUOTE;
	else if (c == '\"' && status == DQUOTE)
		status = DEFAULT;
	return (status);
}

int	seperator_type(char *user_input, int i)
{
	if (((user_input[i] > 8 && user_input[i] < 14) || user_input[i] == 32))
		return (SPACES);
	else if (user_input[i] == '|')
		return (PIPE);
	else if (user_input[i] == '<' && user_input[i + 1] == '<')
		return (HEREDOC);
	else if (user_input[i] == '>' && user_input[i + 1] == '>')
		return (APPEND);
	else if (user_input[i] == '<')
		return (INPUT);
	else if (user_input[i] == '>')
		return (TRUNC);
	else if (user_input[i] == '\0')
		return (END);
	else
		return (0);
}

int	save_word_or_sep(int *i, char *user_input, int start, t_data *data)
{
	int	type;

	(void)data;
	(void)start;
	type = seperator_type(user_input, *i);
	if (type)
	{
		if ((*i) != 0 && seperator_type(user_input, (*i) - 1) == 0)
			save_word(&data->token, user_input, (*i), start);
		if (type == APPEND || type == HEREDOC || type == PIPE || type == INPUT
			|| type == TRUNC || type == END)
		{
			save_separator(&data->token, user_input, (*i), type);
			if (type == APPEND || type == HEREDOC)
				(*i)++;
		}
		start = (*i) + 1;
	}
	return (start);
}

int	tokenizer(t_data *data, char *user_input)
{
	int	i;
	int	start;
	int	end;
	int	status;

	i = -1;
	start = 0;
	end = ft_strlen(user_input);
	status = DEFAULT;
	while (++i <= end)
	{
		status = set_status(status, user_input[i]);
		if (status == DEFAULT)
			start = save_word_or_sep(&i, user_input, start, data);
	}
	if (status != DEFAULT)
	{
		status_error(status);
		return (FAILURE);
	}
	else
		remove_quotes(&data->token);
	return (SUCCESS);
}
