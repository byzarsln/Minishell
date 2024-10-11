/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyarsla <beyarsla@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 20:04:54 by beyarsla          #+#    #+#             */
/*   Updated: 2023/12/21 18:21:32 by beyarsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	int		i;
	int		j;
	char	*str2;

	i = ft_strlen(str);
	j = 0;
	str2 = malloc((i + 1) * sizeof(char));
	if (!str2)
		return (NULL);
	while (str[j] != '\0')
	{
		str2[j] = str[j];
		j++;
	}
	str2[j] = '\0';
	return (str2);
}
