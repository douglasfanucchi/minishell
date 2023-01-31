/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 09:50:04 by dfanucch          #+#    #+#             */
/*   Updated: 2023/01/31 09:50:04 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	del_redirection_nodes(t_list *node)
{
	ft_lstdel(node, ft_del_token);
	ft_lstdel(node, ft_del_token);
}

void	ft_set_command_redirects(t_command *command)
{
	t_list		**tokens;
	t_list		*node;
	t_token		*token;
	char		**argv;
	t_redirect	*redirect;

	argv = command->argv;
	tokens = command->tokens;
	node = *tokens;
	while (node)
	{
		token = node->content;
		if (!ft_is_redirection_token(token->original))
		{
			argv++;
			node = node->next;
			continue ;
		}
		redirect = ft_new_redirect(node);
		redirect->old_fd = ft_get_redirect_file_descriptor(node);
		ft_lstadd_back(command->redirects, ft_lstnew(redirect));
		ft_remove_arg(argv, *argv);
		ft_remove_arg(argv, *argv);
		del_redirection_nodes(node);
	}
}
