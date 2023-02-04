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

static int	read_file(char *filename, int flags)
{
	if (access(filename, F_OK) != 0)
	{
		printf("%s: No such file or directory.\n", filename);
		return (-1);
	}
	if (access(filename, R_OK) != 0)
	{
		printf("%s: Permission denied.\n", filename);
		return (-1);
	}
	return (open(filename, flags));
}

static int	create_file(char *filename, int flags, mode_t mode)
{
	int	fd;

	fd = open(filename, flags, mode);
	if (fd == -1)
	{
		printf("Could not create %s: Permission denied.\n", filename);
		return (-1);
	}
	return (fd);
}

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
		return (create_file(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644));
	if (ft_strncmp(redirect, ">>", 3) == 0)
		return (create_file(filename, O_CREAT | O_APPEND | O_WRONLY, 0644));
	if (ft_strncmp(redirect, "<", 2) == 0)
		return (read_file(filename, O_RDONLY));
	return (create_here_doc(here_doc_filename(), token->original));
}
