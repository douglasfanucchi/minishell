/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_file_descriptor.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 19:11:44 by dfanucch          #+#    #+#             */
/*   Updated: 2023/02/14 00:49:16 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	sigint_exit_here_doc(int signal)
{
	if (signal != SIGINT)
		return ;
	close(g_minishell.here_doc[1]);
	ft_child_exit_shell(g_minishell.commands, (char) 130);
}

static void	create_here_doc(char *limiter)
{
	char	*next_line;

	close(g_minishell.here_doc[0]);
	signal(SIGINT, sigint_exit_here_doc);
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
		write(g_minishell.here_doc[1], next_line, ft_strlen(next_line));
		if (*next_line != '\n')
			write(g_minishell.here_doc[1], "\n", 1);
		free(next_line);
		write(1, "heredoc> ", 9);
		next_line = get_next_line(0);
	}
	close(g_minishell.here_doc[1]);
	ft_child_exit_shell(g_minishell.commands, 0);
}

static int	get_here_doc(char *limiter)
{
	if (g_minishell.cancel_cmd)
		return (-1);
	pipe(g_minishell.here_doc);
	g_minishell.waiting = 1;
	if (fork() == 0)
		create_here_doc(limiter);
	close(g_minishell.here_doc[1]);
	wait(NULL);
	return (g_minishell.here_doc[0]);
}

static void	remove_quotes(char *str)
{
	char	quoted;
	size_t	i;

	quoted = 0;
	i = 0;
	while (str[i])
	{
		if (!ft_is_quote(str[i]) || (quoted && quoted != str[i]))
		{
			i++;
			continue ;
		}
		if (!quoted || quoted == str[i])
		{
			if (!quoted)
				quoted = str[i];
			else
				quoted = 0;
			ft_memmove(str + i, str + i + 1, ft_strlen(str + i));
			continue ;
		}
		i++;
	}
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
	remove_quotes(filename);
	if (*filename == '\n')
		return (-1);
	if (ft_strncmp(redirect, ">", 2) == 0)
		return (open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644));
	if (ft_strncmp(redirect, ">>", 3) == 0)
		return (open(filename, O_CREAT | O_APPEND | O_WRONLY, 0644));
	if (ft_strncmp(redirect, "<", 2) == 0)
		return (open(filename, O_RDONLY));
	return (get_here_doc(token->original));
}
