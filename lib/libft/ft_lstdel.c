/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:38:28 by dfanucch          #+#    #+#             */
/*   Updated: 2023/02/11 14:39:20 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_recursive_del(t_list *node)
{
	void	*content;

	if (!node->next)
	{
		if (node->prev)
			node->prev->next = NULL;
		content = node->content;
		free(node);
		return (content);
	}
	content = node->content;
	node->content = ft_recursive_del(node->next);
	return (content);
}

void	ft_lstdel(t_list *node, void (*del)(void*))
{
	if (!node)
		return ;
	del(ft_recursive_del(node));
}
