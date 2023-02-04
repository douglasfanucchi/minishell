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

static char	*get_var_value(char *var, char **envp)
{
	char	*value;
	char	*var_equals;
	size_t	var_len;

	if (ft_strncmp(var, "$?", 3) == 0)
		return (ft_itoa(g_bash_status));
	var = ft_substr(var, 1, ft_strlen(var) - 1);
	var_equals = ft_strjoin(var, "=");
	var_len = ft_strlen(var_equals);
	while (*envp)
	{
		if (ft_strncmp(*envp, var_equals, var_len) == 0)
		{
			free(var_equals);
			free(var);
			return (ft_substr(*envp, var_len, ft_strlen(*envp) - var_len + 1));
		}
		envp++;
	}
	free(var);
	free(var_equals);
	return (NULL);
}

static void	replace_var_for_value(char **argv, char *var, char *value)
{
	char	*before_var;
	char	*var_end;
	char	*var_start;
	char	*result;

	var_start = ft_strnstr(*argv, var, ft_strlen(*argv));
	var_end = var_start + ft_strlen(var);
	free(var);
	if (!value)
	{
		ft_memmove(var_start, var_end, ft_strlen(var_end) + 1);
		free(value);
		return ;
	}
	before_var = ft_substr(*argv, 0, var_start - *argv);
	result = ft_strjoin((const char *)before_var, (const char *)value);
	free(before_var);
	before_var = *argv;
	*argv = ft_strjoin((const char *)result, (const char *)var_end);
	free(before_var);
	free(result);
	free(value);
}

static char	should_skip(char *str, char *quoted)
{
	if (!*quoted && (*str == '\'' || *str == '"'))
	{
		*quoted = *str;
		return (1);
	}
	if (ft_is_variable(str) && (!*quoted || *quoted == '"'))
		return (0);
	if (*quoted == *str)
		*quoted = 0;
	return (1);
}

static void	expand_token(char **argv, char **envp)
{
	char	*str;
	char	*var_end;
	char	*var;
	char	quoted;

	str = *argv;
	quoted = 0;
	while (*str)
	{
		if (should_skip(str, &quoted))
		{
			str++;
			continue ;
		}
		var_end = str + 1;
		if (*var_end == '?')
			var_end++;
		else
			while (*var_end && ft_is_valid_variable_char(*var_end))
				var_end++;
		var = ft_substr(str, 0, var_end - str);
		replace_var_for_value(argv, var, get_var_value(var, envp));
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
