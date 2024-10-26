/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_heredoc3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyza <beyza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 00:46:38 by beyza             #+#    #+#             */
/*   Updated: 2024/10/27 00:55:47 by beyza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*make_str_from_tab(char **tab)
{
	char	*str;
	char	*tmp;
	int		i;

	i = -1;
	while (tab[++i])
	{
		tmp = str;
		if (i == 0)
			str = ft_strdup(tab[0]);
		else
		{
			str = ft_strjoin(tmp, tab[i]);
			free_pointr(tmp);
		}
		if (tab[i + 1])
		{
			tmp = str;
			str = ft_strjoin(tmp, " ");
			free_pointr(tmp);
		}
	}
	free_str_tab(tab);
	return (str);
}
