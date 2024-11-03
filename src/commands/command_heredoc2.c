/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_heredoc2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyarsla <beyarsla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 23:59:49 by beyza             #+#    #+#             */
/*   Updated: 2024/11/03 18:23:08 by beyarsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*replace_str_heredoc(char *str, char *var_value, int index)
{
	char	*tmp;

	tmp = NULL;
	if (var_value == NULL)
		*str = '\0';
	else
	{
		tmp = str;
		str = erase_and_replace(NULL, str, var_value, index);
		free_pointr(tmp);
	}
	free_pointr(var_value);
	return (str);
}

char	*recover_val(t_token *token, char *str, t_data *data)
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
	else if (var && var[0] == '?' && var[1] == '=')
		value = ft_itoa(g_last_exit_code);
	else
		value = NULL;
	free_pointr(var);
	return (value);
}

char	*handle_dollar_in_heredoc(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$'
			&& is_next_char_a_sep(str[i + 1]) == FAILURE
			&& var_between_quotes(str, i) == FAILURE)
				str = replace_str_heredoc(str, recover_val(NULL, str + i, data), i);
		else
			i++;
	}
	return (str);
}

static char	*dollar_in_heredoc(t_data *data, char *line)
{
	char	**words;
	int		i;

	words = ft_split(line, ' ');
	if (!words)
		return (NULL);
	i = 0;
	while (words[i])
	{
		if (ft_strchr(words[i], '$'))
		{
			words[i] = handle_dollar_in_heredoc(data, words[i]);
			if (!words[i])
				return (NULL);
		}
		i++;
	}
	return (make_str_from_tab(words));
}

int	evaluate_heredoc_line(t_data *data, char **line, t_io_fds *io, bool *return_status)
{
	if (*line == NULL)
	{
		errmsg_cmd("warning", "here-document delimited by end-of-file: wanted",
			io->heredoc_delimiter, true);
		*return_status = true;
		return (FAILURE);
	}
	if (ft_strncmp(*line, io->heredoc_delimiter, ft_strlen(*line)) == 0)
	{
		*return_status = true;
		return (FAILURE);
	}
	if (io->heredoc_quotes == false && ft_strchr(*line, '$'))
	{
		*line = dollar_in_heredoc(data, *line);
		if (!(*line))
		{
			free_pointr(*line);
			*return_status = false;
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
