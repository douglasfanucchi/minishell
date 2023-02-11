/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/10 12:15:33 by dfanucch          #+#    #+#             */
/*   Updated: 2023/02/11 16:10:44 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	is_valid(char **args)
{
	size_t	size;

	size = 0;
	while (args[size])
		size++;
	return (size < 2);
}

static char	*get_dir(t_command *command)
{
	char	**splitted;
	t_list	**dirs;
	char	*cwd;
	int		i;

	if (!command->argv[1])
		return (ft_envp_value(g_minishell.envp, "HOME"));
	cwd = getcwd(NULL, 0);
	splitted = ft_split(cwd, '/');
	i = 0;
	dirs = ft_newlist();
	while (splitted[i])
		ft_lstadd_back(dirs, ft_lstnew(splitted[i++]));
	free(cwd);
	free(splitted);
	return (ft_path_after_navigate(dirs, command->argv[1]));
}

static int	exec(t_command *command)
{
	char	*old_dir;
	char	*dir;

	if (!is_valid(command->argv + 1))
	{
		command->bash_status = 1;
		ft_lstadd_back(command->errors,
			ft_lstnew(ft_strdup("cd: too many arguments\n")));
		return (-1);
	}
	dir = get_dir(command);
	old_dir = getcwd(NULL, 0);
	if (chdir(dir) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		perror(dir);
		free(old_dir);
		free(dir);
		return (-1);
	}
	ft_envp_update_var(g_minishell.envp, "OLDPWD", old_dir);
	ft_envp_update_var(g_minishell.envp, "PWD", dir);
	free(old_dir);
	free(dir);
	return (0);
}

t_builtin	*ft_new_change_directory(void)
{
	t_builtin	*builtin;

	builtin = malloc(sizeof(t_builtin));
	builtin->id = ft_strdup("cd");
	builtin->exec = exec;
	return (builtin);
}
