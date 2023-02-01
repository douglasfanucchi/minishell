/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dfanucch <dfanucch@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 17:54:58 by dfanucch          #+#    #+#             */
/*   Updated: 2023/01/31 17:54:58 by dfanucch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	is_variable(char *str)
{
	return (*str == '$' && str[1] && !ft_isspace(str[1])
		&& !ft_isdigit(str[1]));
}

static char	*get_var_value(char *var, char **envp)
{
	char	*value;
	char	*var_equals;
	size_t	var_len;

	var_equals = ft_strjoin(var, "=");
	var_len = ft_strlen(var_equals);
	if (ft_strncmp(var, "?", 2) == 0)
		return (ft_itoa(g_bash_status));
	while (*envp)
	{
		if (ft_strncmp(*envp, var_equals, var_len) == 0)
		{
			free(var_equals);
			return (ft_substr(*envp, var_len, ft_strlen(*envp) - var_len + 1));
		}
		envp++;
	}
	free(var_equals);
	return (NULL);
}

static void	replace_var_for_value(char **argv, char *var, char *value)
{
	char	*before_var;
	char	*var_end;
	char	*result;

	var_end = var;
	result = NULL;
	while (*var_end && !ft_isspace(*var_end) && *var_end != '\''
		&& *var_end != '"')
		var_end++;
	if (!value)
	{
		ft_memmove(var, var_end, ft_strlen(var_end) + 1);
		return ;
	}
	if (*var_end == '\'' || *var == '"')
		var_end++;
	before_var = ft_substr(*argv, 0, var - *argv);
	result = ft_strjoin((const char *)before_var, (const char *)value);
	free(before_var);
	before_var = *argv;
	*argv = ft_strjoin((const char *)result, (const char *)var_end);
	free(before_var);
	free(result);
}

static void	expand_token(char **argv, char **envp)
{
	char	*str;
	char	*var_end;
	char	*var;
	char	*value;

	str = *argv;
	while (*str)
	{
		if (!is_variable(str))
		{
			str++;
			continue ;
		}
		var_end = str;
		while (*var_end && !ft_isspace(*var_end) && *var_end != '\''
			&& *var_end != '"')
			var_end++;
		var = ft_substr(str, 1, var_end - (str + 1));
		value = get_var_value(var, envp);
		replace_var_for_value(argv, str, value);
		free(var);
		free(value);
		str = *argv;
	}
}

void	ft_expand_args(t_command *command)
{
	t_list	**tokens;
	char	**argv;
	t_list	*node;
	t_token	*token;

	tokens = command->tokens;
	argv = command->argv;
	node = *tokens;
	while (node->next)
	{
		token = node->content;
		if (token->should_expand)
			expand_token(argv, command->envp);
		argv++;
		node = node->next;
	}
}
