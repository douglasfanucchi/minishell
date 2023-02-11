/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   navigate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 09:59:17 by dfanucch          #+#    #+#             */
/*   Updated: 2023/02/11 17:06:17 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	is_go_back(char *str)
{
	return (ft_strncmp("..", str, 3) == 0 || ft_strncmp("../", str, 4) == 0);
}

static char	*join_list(t_list **dirs)
{
	t_list	*node;
	char	*aux;
	char	*path;

	path = ft_strdup("/");
	node = *dirs;
	while (node)
	{
		aux = path;
		path = ft_strjoin(path, (char *)node->content);
		free(aux);
		aux = path;
		path = ft_strjoin(path, "/");
		free(aux);
		node = node->next;
	}
	if (ft_strncmp(path, "/", 2) != 0)
		path[ft_strlen(path) - 1] = 0;
	return (path);
}

void	del_dirs(t_list **dirs)
{
	ft_lstclear(dirs, free);
	free(dirs);
}

void	go_back(t_list **dirs)
{
	t_list	*last_node;

	last_node = ft_lstlast(*dirs);
	if (*dirs == last_node)
		*dirs = NULL;
	ft_lstdel(last_node, free);
}

char	*ft_path_after_navigate(t_list **dirs, char *cmd_navigation)
{
	char	**splitted;
	char	*path;
	int		i;

	splitted = ft_split(cmd_navigation, '/');
	if (*cmd_navigation == '/')
	{
		del_dirs(dirs);
		dirs = ft_newlist();
	}
	i = 0;
	while (splitted[i])
	{
		if (!is_go_back(splitted[i]))
			ft_lstadd_back(dirs, ft_lstnew(ft_strdup(splitted[i])));
		else
			go_back(dirs);
		free(splitted[i++]);
	}
	free(splitted);
	path = join_list(dirs);
	del_dirs(dirs);
	return (path);
}
