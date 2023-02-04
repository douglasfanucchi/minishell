/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 06:40:57 by dfanucch          #+#    #+#             */
/*   Updated: 2023/02/04 06:40:57 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_del_variable(void *content)
{
	t_variable	*var;

	var = content;
	free(var->value);
	free(var);
}

t_variable	*ft_new_variable(size_t position, char *value)
{
	t_variable	*var;

	var = malloc(sizeof(t_variable));
	var->position = position;
	var->len = ft_strlen(value);
	var->value = ft_strdup(value);
	return (var);
}
