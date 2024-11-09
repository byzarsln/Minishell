/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_heredoc2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayirmili <ayirmili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:05:29 by beyarsla          #+#    #+#             */
/*   Updated: 2024/11/08 13:51:01 by ayirmili         ###   ########.fr       */
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

char	*recover_val(t_token *token, char *str, t_data *data, int exit_code)
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
		value = ft_itoa(exit_code);
	else
		value = NULL;
	free_pointr(var);
	return (value);
}

char	*handle_dollar_in_heredoc(t_data *data, char *str, int exit_code)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && is_next_char_a_sep(str[i + 1]) == FAILURE
			&& var_between_quotes(str, i) == FAILURE)
			str = replace_str_heredoc(str, recover_val(NULL, str + i, data,
						exit_code), i);
		else
			i++;
	}
	return (str);
}

static char	*dollar_in_heredoc(t_data *data, char *line, int exit_code)
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
			words[i] = handle_dollar_in_heredoc(data, words[i], exit_code);
			if (!words[i])
				return (NULL);
		}
		i++;
	}
	return (make_str_from_tab(words));
}

int	evaluate_heredoc_line(t_data *data, char **line, bool *return_status,
		int exit_code)
{
	if (*line == NULL)
	{
		errmsg_cmd("warning", "here-document delimited by end-of-file: wanted",
			data->cmd->io_fds->heredoc_delimiter, true);
		*return_status = true;
		return (FAILURE);
	}
	if (ft_strncmp(*line, data->cmd->io_fds->heredoc_delimiter,
			ft_strlen(*line)) == 0 && *line[0] != '\0')
	{
		*return_status = true;
		return (FAILURE);
	}
	if (data->cmd->io_fds->heredoc_quotes == false && ft_strchr(*line, '$'))
	{
		*line = dollar_in_heredoc(data, *line, exit_code);
		if (!(*line))
		{
			free_pointr(*line);
			*return_status = false;
			return (FAILURE);
		}
	}
	return (SUCCESS);
}
