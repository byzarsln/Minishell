/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayirmili <ayirmili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:00:49 by ayirmili          #+#    #+#             */
/*   Updated: 2024/11/08 14:08:53 by ayirmili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	erase_var(t_token **token_list, char *str, int index)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	i = 0;
	j = 0;
	len = ft_strlen(str) - var_length(str + index);
	new_str = (char *)malloc(sizeof(char) * len + 1);
	if (!new_str)
		return (1);
	while (str[i])
	{
		if (str[i] == '$' && i == index)
		{
			i = i + var_length(str + index) + 1;
			if (str[i] == '\0')
				break ;
		}
		new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	free_pointr((*token_list)->value);
	(*token_list)->value = new_str;
	return (0);
}

static void	copy_var_string(char *new_str, char *var_value, int *j)
{
	int	k;

	k = 0;
	while (var_value[k])
	{
		new_str[*j] = var_value[k];
		k++;
		(*j)++;
	}
}

static char	*generate_token_string(char *oldstr, char *var_value,
		int newstr_size, int index)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * newstr_size);
	if (!new_str)
		return (NULL);
	while (oldstr[i])
	{
		if (oldstr[i] == '$' && i == index)
		{
			copy_var_string(new_str, var_value, &j);
			i = i + var_length(oldstr + index) + 1;
			if (oldstr[i] == '\0')
				break ;
		}
		new_str[j++] = oldstr[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*erase_and_replace(t_token **token_list, char *str, char *var_value,
		int index)
{
	char	*newstr;
	int		newstr_size;

	newstr_size = (ft_strlen(str) - var_length(str + index)
			+ ft_strlen(var_value));
	newstr = generate_token_string(str, var_value, newstr_size, index);
	if (token_list && *token_list)
	{
		free_pointr((*token_list)->value);
		(*token_list)->value = newstr;
	}
	return (newstr);
}

int	handle_replace_var(t_token **token_list, char *var_value, int index)
{
	if (var_value == NULL)
	{
		if (erase_var(token_list, (*token_list)->value, index) == 1)
		{
			free_pointr(var_value);
			return (1);
		}
	}
	else
	{
		if (erase_and_replace(token_list, (*token_list)->value, var_value,
				index) == NULL)
		{
			free_pointr(var_value);
			return (1);
		}
	}
	free_pointr(var_value);
	return (0);
}
