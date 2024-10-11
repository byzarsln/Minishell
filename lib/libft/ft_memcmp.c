/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyarsla <beyarsla@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 17:10:02 by beyarsla          #+#    #+#             */
/*   Updated: 2023/12/21 17:28:10 by beyarsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str, const void *str1, size_t n)
{
	size_t	i;
	char	*str2;
	char	*str3;

	i = 0;
	str2 = (char *)str;
	str3 = (char *)str1;
	while (i < n)
	{
		if (str2[i] != str3[i])
		{
			return ((unsigned char)str2[i] - (unsigned char)str3[i]);
		}
		i++;
	}
	return (0);
}
