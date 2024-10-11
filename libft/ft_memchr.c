/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyarsla <beyarsla@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 16:21:53 by beyarsla          #+#    #+#             */
/*   Updated: 2023/12/21 17:20:19 by beyarsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t	i;
	char	*str2;

	i = 0;
	str2 = (char *)str;
	if (!str && !n)
		return (NULL);
	while (i < n)
	{
		if (str2[i] == (char)c)
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}
