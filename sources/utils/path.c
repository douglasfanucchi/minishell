/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 18:08:40 by dfanucch          #+#    #+#             */
/*   Updated: 2023/02/11 17:41:02 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*find_path_row(char **envp)
{
	while (*envp && !ft_strnstr(*envp, "PATH", 4))
		envp++;
	if (!*envp)
		return (NULL);
	return (ft_strdup(*envp));
}

char	**ft_get_paths(char **envp)
{
	char	*path;
	char	**paths;

	path = find_path_row(envp);
	if (!path)
		return (NULL);
	paths = ft_split(path + 5, ':');
	free(path);
	return (paths);
}

void	ft_del_paths(char **paths)
{
	char	**t_paths;

	if (!paths)
		return ;
	t_paths = paths;
	while (*t_paths)
	{
		free(*t_paths);
		t_paths++;
	}
	free(paths);
}
