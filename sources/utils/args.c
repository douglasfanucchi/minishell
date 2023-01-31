/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 18:35:55 by coder             #+#    #+#             */
/*   Updated: 2023/01/30 18:35:56 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**ft_find_arg(char **argv, char *arg)
{
	while (*argv)
	{
		if (ft_strncmp(*argv, arg, ft_strlen(*argv) + 1) == 0)
			return (argv);
		argv++;
	}
	return (NULL);
}

void	ft_remove_arg(char **argv, char *arg)
{
	int		i;
	char	**found;

	found = ft_find_arg(argv, arg);
	if (!found)
		return ;
	i = 0;
	while (found[i])
		i++;
	free(*found);
	ft_memmove(found, found + 1, i * sizeof(char *));
}
