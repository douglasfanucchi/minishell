/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:42:28 by coder             #+#    #+#             */
/*   Updated: 2023/02/03 16:42:29 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	ft_is_valid_variable_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

char	ft_is_variable(char *str)
{
	return ((*str == '$' && str[1] && !ft_isspace(str[1])
			&& !ft_isdigit(str[1])) && str[1] != '\"' && str[1] != '"');
}
