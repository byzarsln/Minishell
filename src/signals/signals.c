/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayirmili <ayirmili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:39:05 by ayirmili          #+#    #+#             */
/*   Updated: 2024/10/17 13:43:56 by ayirmili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sigint_reset(int signal_no)
{
	(void)signal_no;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	set_signals(void)
{
	struct sigaction	signl;

	ft_memset(&signl, 0, sizeof(signl));
	signl.sa_handler = &sigint_reset;
	sigaction(SIGINT, &signl, NULL);
}
