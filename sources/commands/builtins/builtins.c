/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 07:58:34 by dfanucch          #+#    #+#             */
/*   Updated: 2023/02/10 07:58:34 by dfanucch         ###   ########.fr       */
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
				ft_strlen(builtins_filenames[i])) == 0)
		{
			del_builtin_filenames(builtins_filenames);
			return (1);
		}
		i++;
	}
	del_builtin_filenames(builtins_filenames);
	return (0);
}
