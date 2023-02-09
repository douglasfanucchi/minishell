#include <minunit.h>
#include <minishell.h>

MU_TEST(test_token_should_not_expands) {
	char		*input = "cat Makefile | grep '$name'";
	char		**not_expanded = ft_split(input, ' ');
	t_command	*command = ft_new_command(ft_tokenizer(input), g_minishell.envp, ft_get_paths(g_minishell.envp));

	ft_expand_args(command);

	int i = -1;
	while (command->argv[++i])
		mu_check(ft_strncmp(not_expanded[i], command->argv[i], ft_strlen(not_expanded[i]) + 1) == 0);
	ft_del_command(command);
	i = 0;
	while (not_expanded[i])
		free(not_expanded[i++]);
	free(not_expanded);
}

MU_TEST(test_token_should_expand_to_empty_value) {
	t_list	**tokens = ft_tokenizer("cat $filename");
	t_command	*command = ft_new_command(tokens, g_minishell.envp, ft_get_paths(g_minishell.envp));
	char	*assert_str;

	ft_expand_args(command);
	mu_check(ft_strncmp(command->argv[1], "", 1) == 0);
	ft_del_command(command);

	tokens = ft_tokenizer("cat \"$filename\"");
	command = ft_new_command(tokens, g_minishell.envp, ft_get_paths(g_minishell.envp));

	ft_expand_args(command);
	mu_check(ft_strncmp(command->argv[1], "\"\"", 3) == 0);
	ft_del_command(command);

	tokens = ft_tokenizer("echo \"filename $fillename is being used\"");
	command = ft_new_command(tokens, g_minishell.envp, ft_get_paths(g_minishell.envp));
	assert_str = "\"filename  is being used\"";
	
	ft_expand_args(command);
	mu_check(ft_strncmp(command->argv[1], assert_str, ft_strlen(assert_str) + 1) == 0);
	ft_del_command(command);
}

MU_TEST(test_token_should_expand_to_path_value) {
	t_list	**tokens = ft_tokenizer("echo \"$PATH\"");
	t_command	*command = ft_new_command(tokens, g_minishell.envp, ft_get_paths(g_minishell.envp));
	char *assert_str;

	ft_expand_args(command);
	mu_check(ft_strncmp(command->argv[1], "\"/usr/bin:/usr/sbin\"", ft_strlen("\"/usr/bin:/usr/sbin\"") + 1) == 0);
	ft_del_command(command);

	tokens = ft_tokenizer("echo $PATH");
	command = ft_new_command(tokens, g_minishell.envp, ft_get_paths(g_minishell.envp));

	ft_expand_args(command);
	mu_check(ft_strncmp(command->argv[1], "/usr/bin:/usr/sbin", ft_strlen("/usr/bin:/usr/sbin") + 1) == 0);
	ft_del_command(command);

	tokens = ft_tokenizer("echo \"the shell $SHELL is what im using\"");
	assert_str = "\"the shell minishell is what im using\"";
	command = ft_new_command(tokens, g_minishell.envp, ft_get_paths(g_minishell.envp));

	ft_expand_args(command);
	mu_check(ft_strncmp(command->argv[1], assert_str, ft_strlen(assert_str) + 1) == 0);
	ft_del_command(command);
}

MU_TEST(test_token_should_expand_to_bash_status_code) {
	t_list	**tokens = ft_tokenizer("echo $?");
	t_command	*command = ft_new_command(tokens, g_minishell.envp, ft_get_paths(g_minishell.envp));

	ft_expand_args(command);
	mu_check(ft_strncmp(command->argv[1], "127", 4) == 0);
	ft_del_command(command);

	tokens = ft_tokenizer("echo \"$?\"");
	command = ft_new_command(tokens, g_minishell.envp, ft_get_paths(g_minishell.envp));

	ft_expand_args(command);
	mu_check(ft_strncmp(command->argv[1], "\"127\"", 6) == 0);
	ft_del_command(command);
}

MU_TEST(test_token_should_to_expand_even_with_single_quotes) {
	t_command	*command = ft_new_command(ft_tokenizer("\"'$?'\""), g_minishell.envp, ft_get_paths(g_minishell.envp));

	ft_expand_args(command);
	mu_check(ft_strncmp(command->argv[0], "\"'127'\"", 6) == 0);
	ft_del_command(command);
}

MU_TEST(test_token_should_expand_two_straight_variables) {
	t_command	*command = ft_new_command(ft_tokenizer("$SHELL$PATH"), g_minishell.envp, ft_get_paths(g_minishell.envp));
	char		*assert_str = "minishell/usr/bin:/usr/sbin";

	ft_expand_args(command);
	mu_check(ft_strncmp(command->argv[0], assert_str, ft_strlen(assert_str) + 1) == 0);
	ft_del_command(command);
}

MU_TEST(test_should_expand_variable_after_quoted_variable) {
	t_command	*command = ft_new_command(ft_tokenizer("'$not'$SHELL"), g_minishell.envp, ft_get_paths(g_minishell.envp));
	char		*assert_str = "'$not'minishell";

	ft_expand_args(command);
	mu_check(ft_strncmp(command->argv[0], assert_str, ft_strlen(assert_str) + 1) == 0);
	ft_del_command(command);
}

MU_TEST(test_should_expand_quoted_straight_tokens) {
	t_command	*command = ft_new_command(ft_tokenizer("\"$SHELL$PATH\""), g_minishell.envp, ft_get_paths(g_minishell.envp));
	char		*assert_str = "\"minishell/usr/bin:/usr/sbin\"";

	ft_expand_args(command);
	mu_check(ft_strncmp(command->argv[0], assert_str, ft_strlen(assert_str) + 1) == 0);
	ft_del_command(command);
}

MU_TEST(test_should_not_consider_invalid_char_at_var_name) {
	t_command	*command = ft_new_command(ft_tokenizer("$SHELL^"), g_minishell.envp, ft_get_paths(g_minishell.envp));
	char		*assert_str = "minishell^";

	ft_expand_args(command);
	mu_check(ft_strncmp(command->argv[0], assert_str, ft_strlen(assert_str) + 1) == 0);
	ft_del_command(command);

	command = ft_new_command(ft_tokenizer("$SHELL-"), g_minishell.envp, ft_get_paths(g_minishell.envp));
	assert_str = "minishell-";

	ft_expand_args(command);
	mu_check(ft_strncmp(command->argv[0], assert_str, ft_strlen(assert_str) + 1) == 0);
	ft_del_command(command);

	command = ft_new_command(ft_tokenizer("$SHELL;"), g_minishell.envp, ft_get_paths(g_minishell.envp));
	assert_str = "minishell;";

	ft_expand_args(command);
	mu_check(ft_strncmp(command->argv[0], assert_str, ft_strlen(assert_str) + 1) == 0);
	ft_del_command(command);

	command = ft_new_command(ft_tokenizer("hello$?world"), g_minishell.envp, ft_get_paths(g_minishell.envp));
	assert_str = "hello127world";

	ft_expand_args(command);
	mu_check(ft_strncmp(command->argv[0], assert_str, ft_strlen(assert_str) + 1) == 0);
	ft_del_command(command);
}

MU_TEST(test_variable_positions) {
	t_command	*command = ft_new_command(ft_tokenizer("$SHELL"), g_minishell.envp, ft_get_paths(g_minishell.envp));
	ft_expand_args(command);
	t_list	*token_node = *command->tokens;
	t_token	*token = token_node->content;
	t_list	*var_node = *token->variables;
	t_variable	*var = var_node->content;

	mu_check(var->position == 0);
	ft_del_command(command);

	command = ft_new_command(ft_tokenizer("hello$SHELL"), g_minishell.envp, ft_get_paths(g_minishell.envp));
	ft_expand_args(command);
	token_node = *command->tokens;
	token = token_node->content;
	var_node = *token->variables;
	var = var_node->content;

	mu_check(var->position == 5);
	ft_del_command(command);
}

MU_TEST_SUITE(test_token_expansion) {
	MU_RUN_TEST(test_token_should_not_expands);
	MU_RUN_TEST(test_token_should_expand_to_empty_value);
	MU_RUN_TEST(test_token_should_expand_to_path_value);
	MU_RUN_TEST(test_token_should_expand_to_bash_status_code);
	MU_RUN_TEST(test_token_should_to_expand_even_with_single_quotes);
	MU_RUN_TEST(test_token_should_expand_two_straight_variables);
	MU_RUN_TEST(test_should_expand_variable_after_quoted_variable);
	MU_RUN_TEST(test_should_expand_quoted_straight_tokens);
	MU_RUN_TEST(test_should_not_consider_invalid_char_at_var_name);
	MU_RUN_TEST(test_variable_positions);
}
