/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 16:42:28 by coder             #+#    #+#             */
/*   Updated: 2023/02/13 19:22:36 by dfanucch         ###   ########.fr       */
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

char	ft_is_valid_variable(char *var)
{
	if (!ft_is_variable(var))
		return (0);
	var++;
	while (*var)
	{
		if (!ft_is_valid_variable_char(*var))
			return (0);
		var++;
	}
	return (1);
}

void	ft_print_envp_var(char *envp_str)
{
	char	*var;

	var = ft_get_var_from_envp_str(envp_str);
	ft_putstr(var);
	free(var);
}

void	ft_print_envp_var_value(char *envp_str)
{
	char	*value;

	value = ft_get_value_from_envp_str(envp_str);
	if (value && *value)
	{
		ft_putstr("=");
		ft_putstr("\"");
	}
	ft_putstr(value);
	if (value && *value)
		ft_putstr("\"");
	free(value);
}
