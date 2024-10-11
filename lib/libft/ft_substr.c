/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyarsla <beyarsla@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 17:28:30 by beyarsla          #+#    #+#             */
/*   Updated: 2023/12/21 18:30:08 by beyarsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	c;

	c = ft_strlen(s);
	if (!s)
		return (NULL);
	if ((unsigned int)ft_strlen(s) < start)
		return (ft_strdup(""));
	if (len > c)
		len = c;
	str = ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (s[start] && len > i)
		str[i++] = s[start++];
	return (str);
}
