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

static void	del_redirection_nodes(t_list *node, char **argv)
{
	ft_lstdel(node, ft_del_token);
	ft_lstdel(node, ft_del_token);
	ft_remove_arg(argv, *argv);
	ft_remove_arg(argv, *argv);
}

static char	validate_redirect(t_command *command, t_redirect *redirect,
		t_list *node)
{
	char	*error_msg;
	t_token	*token;

	if (redirect->old_fd != -1)
		return (1);
	token = node->next->content;
	if (access(token->original, F_OK) != 0)
		error_msg = ": No such file or directory\n";
	else if (access(token->original, X_OK) != 0)
		error_msg = ": Permission denied\n";
	ft_lstadd_back(command->errors, ft_lstnew(
			ft_strjoin(token->original, error_msg)));
	command->bash_status = 1;
	ft_del_redirect((void *)redirect);
	return (0);
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
		if (!validate_redirect(command, redirect, node))
			break ;
		ft_lstadd_back(command->redirects, ft_lstnew(redirect));
		del_redirection_nodes(node, argv);
	}
}
