/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:50:21 by dfanucch          #+#    #+#             */
/*   Updated: 2023/02/06 11:50:22 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ft_new_envp(char **envp)
{
	size_t	size;
	size_t	i;
	char	**new_envp;

	size = 0;
	while (envp[size])
		size++;
	new_envp = malloc(sizeof(char **) * (size + 1));
	i = 0;
	while (i < size)
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

void	ft_del_envp(char **envp)
{
	char	**t_envp;

	t_envp = envp;
	while (*t_envp)
	{
		free(*t_envp);
		t_envp++;
	}
	free(envp);
}
