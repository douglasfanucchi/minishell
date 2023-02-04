/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 18:24:35 by dfanucch          #+#    #+#             */
/*   Updated: 2023/02/04 18:24:36 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*here_doc_filename(void)
{
	char	*tmp_filename;
	char	*str_n;
	int		i;

	i = 1;
	str_n = NULL;
	tmp_filename = ft_strdup(".tmp_here_doc");
	while (access(tmp_filename, F_OK) == 0)
	{
		free(tmp_filename);
		free(str_n);
		str_n = ft_itoa(i);
		tmp_filename = ft_strjoin(".tmp_here_doc_", str_n);
		i++;
	}
	free(str_n);
	return (tmp_filename);
}

static int	reopen_here_doc_readonly(int fd, char *here_doc_filename)
{
	int	new_fd;

	close(fd);
	new_fd = open(here_doc_filename, O_RDONLY);
	free(here_doc_filename);
	return (new_fd);
}

void	ft_delete_here_docs(void)
{
	char	*tmp_filename;
	char	*str_n;
	int		i;

	i = 1;
	str_n = NULL;
	tmp_filename = ft_strdup(".tmp_here_doc");
	while (access(tmp_filename, F_OK) == 0)
	{
		unlink(tmp_filename);
		free(tmp_filename);
		free(str_n);
		str_n = ft_itoa(i++);
		tmp_filename = ft_strjoin(".tmp_here_doc_", str_n);
	}
	free(str_n);
	free(tmp_filename);
}

int	create_here_doc(char *here_doc_filename, char *limiter)
{
	char	*next_line;
	int		fd;

	fd = open(here_doc_filename, O_RDWR | O_CREAT | O_APPEND, 0644);
	write(1, "heredoc> ", 9);
	next_line = get_next_line(0);
	while (next_line)
	{
		if (*next_line != '\n')
			next_line[ft_strlen(next_line) - 1] = 0;
		if (ft_strncmp(next_line, limiter, ft_strlen(next_line)) == 0)
		{
			free(next_line);
			break ;
		}
		write(fd, next_line, ft_strlen(next_line));
		if (*next_line != '\n')
			write(fd, "\n", 1);
		free(next_line);
		write(1, "heredoc> ", 9);
		next_line = get_next_line(0);
	}
	return (reopen_here_doc_readonly(fd, here_doc_filename));
}
