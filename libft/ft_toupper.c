/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyarsla <beyarsla@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 17:38:45 by beyarsla          #+#    #+#             */
/*   Updated: 2023/12/21 16:40:08 by beyarsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_toupper(int c)
{
	if ((char)c >= 'a' && (char)c <= 'z')
	{
		c -= 32;
	}
	return (c);
}
