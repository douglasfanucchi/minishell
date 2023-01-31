/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 14:56:14 by dfanucch          #+#    #+#             */
/*   Updated: 2023/01/18 14:56:16 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_del_token(void *param)
{
	t_token	*token;

	token = param;
	free(token->original);
	free(token->expanded);
	free(token);
}

static char	should_expand(char *token)
{
	if (*token == '\'')
		return (0);
	if (ft_strchr(token, '$'))
		return (1);
	return (0);
}

t_token	*ft_new_token(char *str)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->should_expand = should_expand(str);
	token->original = ft_strdup(str);
	token->expanded = ft_strdup(token->original);
	return (token);
}
