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
	ft_lstclear(token->variables, ft_del_variable);
	free(token->variables);
	free(token);
}

static char	should_expand(char *token)
{
	char	quoted;

	quoted = 0;
	while (*token)
	{
		if (!quoted && (*token == '\'' || *token == '"'))
		{
			quoted = *token;
			token++;
			continue ;
		}
		if (ft_is_variable(token) && (!quoted || quoted == '"'))
			return (1);
		if (quoted == *token)
			quoted = 0;
		token++;
	}
	return (0);
}

t_token	*ft_new_token(char *str)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->should_expand = should_expand(str);
	token->original = ft_strdup(str);
	token->expanded = ft_strdup(token->original);
	token->variables = ft_newlist();
	return (token);
}
