/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 14:18:11 by dfanucch          #+#    #+#             */
/*   Updated: 2022/12/27 14:18:12 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_pathname(char *bin, char **paths)
{
	char	*pathname;
	char	*slashed_bin;

	if (access(bin, F_OK))
		return (ft_strdup(bin));
	slashed_bin = ft_strjoin("/", bin);
	while (*paths)
	{
		pathname = ft_strjoin(*paths, slashed_bin);
		if (access(pathname, F_OK) == 0)
		{
			free(slashed_bin);
			return (pathname);
		}
		free(pathname);
		paths++;
	}
	free(slashed_bin);
	return (ft_strdup(""));
}

static char	*get_filename(t_list **tokens)
{
	t_list	*node;
	t_token	*token;
	t_token	*prev_token;

	node = *tokens;
	prev_token = NULL;
	while (node->next)
	{
		token = node->content;
		if (!ft_is_redirection_token(token->original)
			&& (!node->prev || !ft_is_redirection_token(prev_token->original)))
			break ;
		prev_token = token;
		node = node->next;
	}
	token = node->content;
	if (token->original[0] == '\n')
		return (ft_strdup(""));
	return (ft_strdup(token->original));
}

static char	**get_command_args(t_list **tokens)
{
	t_list	*node;
	t_token	*token;
	char	**args;
	size_t	list_size;
	size_t	i;

	list_size = 0;
	node = *tokens;
	while (node->next)
	{
		node = node->next;
		list_size++;
	}
	args = ft_calloc(list_size + 1, sizeof(char *));
	i = 0;
	node = *tokens;
	while (node->next)
	{
		token = node->content;
		args[i] = ft_strdup(token->original);
		i++;
		node = node->next;
	}
	return (args);
}

void	ft_del_command(void *cmd)
{
	char		**argv;
	t_command	*command;

	command = cmd;
	argv = command->argv;
	free(command->filename);
	free(command->pathname);
	while (*argv)
		free(*(argv++));
	free(command->argv);
	ft_lstclear(command->redirects, free);
	free(command->redirects);
	free(command);
}

t_command	*ft_new_command(t_list **tokens, char **envp, char **paths)
{
	t_command	*command;

	command = malloc(sizeof(t_command));
	command->filename = get_filename(tokens);
	command->is_builtin = 0;
	command->pathname = NULL;
	if (!command->is_builtin)
		command->pathname = get_pathname(command->filename, paths);
	command->argv = get_command_args(tokens);
	command->envp = envp;
	command->bash_status = 1;
	command->pid = 0;
	command->pipe[0] = -1;
	command->pipe[1] = -1;
	command->redirects = ft_newlist();
	return (command);
}
