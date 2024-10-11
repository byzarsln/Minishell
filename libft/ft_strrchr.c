/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyarsla <beyarsla@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 18:59:58 by beyarsla          #+#    #+#             */
/*   Updated: 2023/12/21 16:46:15 by beyarsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char const *str, int c)
{
	int	i;
	int	b;

	b = ft_strlen(str);
	i = 0;
	while (b >= i)
	{
		if (str[b] == (char)c)
		{
			return ((char *)str + b);
		}
		b--;
	}
	return (NULL);
}
