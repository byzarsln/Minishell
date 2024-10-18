/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: beyarsla <beyarsla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:52:56 by ayirmili          #+#    #+#             */
/*   Updated: 2024/10/18 18:42:07 by beyarsla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int parse_input(t_data *data)
{
    // parser_error_control(data);
    if (tokenizer(data, data->user_input) == FAILURE)
        return (FAILURE);
    if (data->token->type == END)
        return (FAILURE);
    // if (check_if_var(&data->token) == FAILURE) // TODO buradan itibaren yapılacak
	// 	return (false);
    return(1);
}