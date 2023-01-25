/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 19:31:55 by coder             #+#    #+#             */
/*   Updated: 2023/01/24 19:31:56 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_analyser	*get_analyser(t_token *token)
{
	if (token->original[0] == '|')
		return (get_pipe_analyser());
	if (token->original[0] == '\'' || token->original[0] == '"')
		return (get_quoted_analyser());
	if (ft_is_redirection_token(token->original))
		return (get_redirection_analyser());
	return (NULL);
}

char	*ft_analyse_token(t_list *node)
{
	char		*result;
	t_token		*token;
	t_analyser	*analyser;

	token = node->content;
	analyser = get_analyser(token);
	if (!analyser)
		return (NULL);
	result = analyser->analyse(node);
	free(analyser);
	return (result);
}
