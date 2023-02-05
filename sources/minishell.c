/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 20:03:00 by dfanucch          #+#    #+#             */
/*   Updated: 2023/01/17 20:03:00 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	g_bash_status;

static char	*find_path_row(char **envp)
{
	while (!ft_strnstr(*envp, "PATH", 4))
		envp++;
	return (ft_strdup(*envp));
}

char	**get_paths(char **envp)
{
	char	*path;
	char	**paths;

	path = find_path_row(envp);
	paths = ft_split(path + 5, ':');
	free(path);
	return (paths);
}

void	del_paths(char **paths)
{
	char	**t_paths;

	t_paths = paths;
	while (*t_paths)
	{
		free(*t_paths);
		t_paths++;
	}
	free(paths);
}

int	main(int argc, char **argv, char **envp)
{
	g_bash_status = 0;
	char	**path = get_paths(envp);
	t_list	**list = ft_newlist();
	t_command *command = ft_new_command(ft_tokenizer("<"), envp, path);
	ft_lstadd_back(list, ft_lstnew(command));

	ft_executor(list);
	del_paths(path);
	return (g_bash_status);
}
