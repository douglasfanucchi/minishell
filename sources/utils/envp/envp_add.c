/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 22:50:29 by dfanucch          #+#    #+#             */
/*   Updated: 2023/02/11 22:50:29 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_var(char *str)
{
	size_t	size;

	size = 0;
	while (str[size] && ft_is_valid_variable_char(str[size]))
		size++;
	return (ft_substr(str, 0, size));
}

static char	*get_value(char *str)
{
	char	*end_var;

	end_var = ft_strchr(str, '=');
	if (!end_var || !end_var[1])
		return (ft_strdup(""));
	end_var++;
	return (ft_substr(end_var, 0, ft_strlen(end_var)));
}

static size_t	get_envp_size(char **envp)
{
	size_t	size;

	size = 0;
	while (envp[size])
		size++;
	return (size);
}

void	ft_envp_add(char ***envp, char *str)
{
	char	*existing;
	char	*var;
	char	*value;
	char	**new_envp;

	var = get_var(str);
	value = get_value(str);
	existing = ft_envp_value(*envp, var);
	if (existing)
	{
		ft_envp_update_var(*envp, var, value);
		free(var);
		free(value);
		free(existing);
		return ;
	}
	new_envp = malloc(sizeof(char **) * (get_envp_size(*envp) + 2));
	ft_memmove(new_envp, *envp, get_envp_size(*envp) * sizeof(char **));
	new_envp[get_envp_size(*envp)] = ft_strdup(str);
	new_envp[get_envp_size(*envp) + 1] = NULL;
	free(*envp);
	free(var);
	free(value);
	*envp = new_envp;
}
