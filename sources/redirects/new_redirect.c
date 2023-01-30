/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_redirect.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 22:59:43 by dfanucch          #+#    #+#             */
/*   Updated: 2023/01/29 22:59:44 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_redirect	*ft_new_redirect(t_list *node)
{
	t_redirect	*redirect;
	t_token		*token;
	char		*n_end;
	char		*str_number;
	int			fd;

	redirect = malloc(sizeof(t_redirect));
	token = node->content;
	n_end = token->original;
	if (*token->original == '>')
		fd = 1;
	else if (*token->original == '<')
		fd = 0;
	else
	{
		while (*n_end != '<' && *n_end != '>')
			n_end++;
		str_number = ft_substr(token->original, 0, n_end - token->original);
		fd = ft_atoi(str_number);
		free(str_number);
	}
	redirect->new_fd = fd;
	return (redirect);
}
