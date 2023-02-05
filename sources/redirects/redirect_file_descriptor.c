/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 19:11:44 by dfanucch          #+#    #+#             */
/*   Updated: 2023/01/28 19:11:44 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_get_redirect_file_descriptor(t_list *node)
{
	t_token	*token;
	char	*redirect;
	char	*filename;

	if (!node->next)
		return (-1);
	token = node->content;
	redirect = token->original;
	while (*redirect != '<' && *redirect != '>')
		redirect++;
	token = node->next->content;
	filename = token->original;
	if (*filename == '\n')
		return (-1);
	if (ft_strncmp(redirect, ">", 2) == 0)
		return (open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644));
	if (ft_strncmp(redirect, ">>", 3) == 0)
		return (open(filename, O_CREAT | O_APPEND | O_WRONLY, 0644));
	if (ft_strncmp(redirect, "<", 2) == 0)
		return (open(filename, O_RDONLY));
	return (create_here_doc(here_doc_filename(), token->original));
}
