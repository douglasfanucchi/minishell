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

static int	create_here_doc(char *limiter)
{
	char	*next_line;
	int		fd[2];

	pipe(fd);
	write(1, "heredoc> ", 9);
	next_line = get_next_line(0);
	while (next_line)
	{
		if (*next_line != '\n')
			next_line[ft_strlen(next_line) - 1] = 0;
		if (ft_strncmp(next_line, limiter, ft_strlen(limiter) + 1) == 0)
		{
			free(next_line);
			break ;
		}
		write(fd[1], next_line, ft_strlen(next_line));
		if (*next_line != '\n')
			write(fd[1], "\n", 1);
		free(next_line);
		write(1, "heredoc> ", 9);
		next_line = get_next_line(0);
	}
	close(fd[1]);
	return (fd[0]);
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
		return (open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644));
	if (ft_strncmp(redirect, ">>", 3) == 0)
		return (open(filename, O_CREAT | O_APPEND | O_WRONLY, 0644));
	if (ft_strncmp(redirect, "<", 2) == 0)
		return (open(filename, O_RDONLY));
	return (create_here_doc(token->original));
}
