/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 09:38:55 by dfanucch          #+#    #+#             */
/*   Updated: 2023/01/23 09:38:55 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*analyse(t_list *node)
{
	t_token	*token;
	t_token	*next_token;

	token = node->content;
	next_token = node->next->content;
	if (next_token->original[0] == '\n')
		return (token->original);
	return (NULL);
}

t_analyser	*get_pipe_analyser(void)
{
	t_analyser	*analyser;

	analyser = malloc(sizeof(t_analyser));
	analyser->analyse = analyse;
	return (analyser);
}
