/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyarsla <beyarsla@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 18:47:08 by beyarsla          #+#    #+#             */
/*   Updated: 2023/12/21 18:49:36 by beyarsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] != '\0' && ft_strchr(set, *s1))
		s1++;
	len = ft_strlen(s1);
	j = len - 1;
	if (i == len)
		return (ft_strdup(""));
	while (j > i && ft_strchr(set, s1[j]))
		j--;
	str = ft_substr(s1, 0, j + 1);
	return (str);
}
