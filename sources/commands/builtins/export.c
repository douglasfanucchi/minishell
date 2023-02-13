/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 22:19:22 by dfanucch          #+#    #+#             */
/*   Updated: 2023/02/13 19:21:51 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_var_end(char *str)
{
	while (*str && ft_is_valid_variable_char(*str))
		str++;
	return (str);
}

static void	print_invalid_identifier(char *identifier)
{
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd("`: not a valid identifier\n", 2);
}

static int	add_variable(char *str)
{
	char	*var;
	char	*var_end;

	var = ft_strjoin("$", str);
	if (ft_strncmp(var, "$=", 3) == 0 || !ft_is_variable(var))
	{
		print_invalid_identifier(str);
		free(var);
		return (-1);
	}
	var_end = get_var_end(str);
	if (*var_end && *var_end != '=')
	{
		print_invalid_identifier(str);
		free(var);
		return (-1);
	}
	ft_envp_add(&g_minishell.envp, str);
	free(var);
	return (0);
}

static int	exec(t_command *command)
{
	char	**envp;
	char	**args;

	envp = g_minishell.envp;
	args = command->argv + 1;
	if (!args[0])
	{
		while (*envp)
		{
			ft_putstr("declare -x ");
			ft_print_envp_var(*envp);
			ft_print_envp_var_value(*envp);
			ft_putstr("\n");
			envp++;
		}
		return (0);
	}
	while (*args)
	{
		if (add_variable(*args) == -1)
			command->bash_status = 1;
		args++;
	}
	return (0);
}

t_builtin	*ft_new_export(void)
{
	t_builtin	*builtin;

	builtin = malloc(sizeof(t_builtin));
	builtin->id = ft_strdup("export");
	builtin->exec = exec;
	return (builtin);
}
