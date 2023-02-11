/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 07:58:34 by dfanucch          #+#    #+#             */
/*   Updated: 2023/02/10 12:24:21 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	del_builtin_filenames(char **filenames)
{
	size_t	i;

	i = 0;
	while (filenames[i])
		free(filenames[i++]);
	free(filenames);
}

char	ft_is_builtin(t_command *command)
{
	char	**builtins_filenames;
	size_t	i;

	builtins_filenames = ft_split("echo:cd:pwd:export:unset:env:exit", ':');
	i = 0;
	while (builtins_filenames[i])
	{
		if (ft_strncmp(builtins_filenames[i],
				command->filename,
				ft_strlen(builtins_filenames[i]) + 1) == 0)
		{
			del_builtin_filenames(builtins_filenames);
			return (1);
		}
		i++;
	}
	del_builtin_filenames(builtins_filenames);
	return (0);
}

void	ft_del_builtin(void *content)
{
	t_builtin	*builtin;

	builtin = content;
	free(builtin->id);
	free(builtin);
}

t_builtin	*ft_new_builtin(char *id)
{
	if (ft_strncmp(id, "echo", ft_strlen("echo") + 1) == 0)
		return (ft_new_echo());
	if (ft_strncmp(id, "cd", ft_strlen("cd") + 1) == 0)
		return (ft_new_change_directory());
	return (NULL);
}
