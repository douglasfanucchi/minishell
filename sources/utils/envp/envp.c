/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 11:50:21 by dfanucch          #+#    #+#             */
/*   Updated: 2023/02/11 18:51:58 by dfanucch         ###   ########.fr       */
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

char	*ft_envp_value(char **envp, char *var)
{
	int	diff;

	while (*envp)
	{
		diff = ft_strncmp(*envp, var, ft_strlen(var) + 1);
		if (diff == 0 || diff - '=' == 0)
			return (ft_strdup(*envp + ft_strlen(var) + 1));
		envp++;
	}
	return (NULL);
}

int	ft_envp_update_var(char **envp, char *var, char *value)
{
	char	*str;
	int		diff;

	while (*envp)
	{
		diff = ft_strncmp(*envp, var, ft_strlen(var) + 1);
		if (diff != 0 && diff - '=' != 0)
		{
			envp++;
			continue ;
		}
		free(*envp);
		*envp = malloc(sizeof(char) * (ft_strlen(value) + ft_strlen(var) + 2));
		str = *envp;
		ft_memmove(str, var, ft_strlen(var));
		str += ft_strlen(var);
		str[0] = '=';
		str++;
		ft_memmove(str, value, ft_strlen(value) + 1);
		return (0);
	}
	return (1);
}

int	ft_envp_remove(char **envp, char *var)
{
	size_t	len;
	int		diff;

	while (*envp)
	{
		diff = ft_strncmp(*envp, var, ft_strlen(var) + 1);
		if (diff != 0 && diff - '=' != 0)
		{
			envp++;
			continue ;
		}
		len = 0;
		while (envp[len])
			len++;
		free(*envp);
		ft_memmove(envp, envp + 1, len * sizeof(char *));
		return (0);
	}
	return (1);
}
