/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:54:58 by dfanucch          #+#    #+#             */
/*   Updated: 2023/01/31 17:54:58 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	ft_is_variable(char *str)
{
	return (*str == '$' && str[1] && !ft_isspace(str[1])
		&& !ft_isdigit(str[1]));
}