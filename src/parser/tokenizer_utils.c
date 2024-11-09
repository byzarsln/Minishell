/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayirmili <ayirmili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:55:27 by ayirmili          #+#    #+#             */
/*   Updated: 2024/11/07 22:31:08 by ayirmili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	lst_add_back_token(t_token **token_lst, t_token *created_token)
{
	t_token	*last_token;

	last_token = *token_lst;
	if (!*token_lst)
	{
		*token_lst = created_token;
		return ;
	}
	if (token_lst && *token_lst && created_token)
	{
		while (last_token->next != NULL)
			last_token = last_token->next;
		last_token->next = created_token;
		created_token->prev = last_token;
	}
}

t_token	*lst_new_token(char *value, char *value_backup, int type, int status)
{
	t_token	*created_token;

	created_token = malloc(sizeof(t_token));
	if (!created_token)
		return (NULL);
	created_token->value = value;
	created_token->value_backup = value_backup;
	created_token->type = type;
	created_token->status = status;
	created_token->next = NULL;
	created_token->prev = NULL;
	return (created_token);
}

int	save_separator(t_token **token_lst, char *user_input, int index, int type)
{
	int		i;
	char	*seperator;

	i = 0;
	if (type == HEREDOC || type == APPEND)
		return (handle_heredoc_append(token_lst, user_input, index, type));
	seperator = malloc(sizeof(char) * 2);
	if (!seperator)
		return (FAILURE);
	while (i < 1)
		seperator[i++] = user_input[index++];
	seperator[i] = '\0';
	lst_add_back_token(token_lst, lst_new_token(seperator, NULL, type,
			DEFAULT));
	return (FAILURE);
}

int	save_word(t_token **token_lst, char *user_input, int index, int start)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc(sizeof(char) * (index - start + 1));
	if (!word)
		return (1);
	while (start < index)
	{
		word[i] = user_input[start];
		start++;
		i++;
	}
	word[i] = '\0';
	lst_add_back_token(token_lst, lst_new_token(word, ft_strdup(word), WORD,
			DEFAULT));
	return (0);
}
