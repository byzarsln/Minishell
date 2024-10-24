/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayirmili <ayirmili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 14:52:56 by ayirmili          #+#    #+#             */
/*   Updated: 2024/10/24 12:09:01 by ayirmili         ###   ########.fr       */
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
    if (check_var(&data->token) == FAILURE)
		return (FAILURE);
    handle_dollar(data, &data->token);
    return(1);
}
