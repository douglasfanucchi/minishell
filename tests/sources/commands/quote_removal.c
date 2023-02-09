#include <minishell.h>
#include <minunit.h>

MU_TEST(test_should_remove_quotes_acting_as_quoting) {
	t_command	*command = ft_new_command(ft_tokenizer("'hello world'"), g_minishell.envp, ft_get_paths(g_minishell.envp));
	char		*assert_str = "hello world";
	ft_quote_removal(command);

	mu_check(ft_strncmp(command->argv[0], assert_str, ft_strlen(assert_str) + 1) == 0);
	mu_check(ft_strncmp(command->filename, assert_str, ft_strlen(assert_str) + 1) == 0);
	ft_del_command(command);

	command = ft_new_command(ft_tokenizer("only'$one'arg"), g_minishell.envp, ft_get_paths(g_minishell.envp));
	assert_str = "only$onearg";
	ft_quote_removal(command);

	mu_check(ft_strncmp(command->argv[0], assert_str, ft_strlen(assert_str) + 1) == 0);
	ft_del_command(command);

	command = ft_new_command(ft_tokenizer("my'arg'"), g_minishell.envp, ft_get_paths(g_minishell.envp));
	assert_str = "myarg";
	ft_quote_removal(command);

	mu_check(ft_strncmp(command->argv[0], assert_str, ft_strlen(assert_str) + 1) == 0);
	ft_del_command(command);

	command = ft_new_command(ft_tokenizer("only'$one''arg'"), g_minishell.envp, ft_get_paths(g_minishell.envp));
	assert_str = "only$onearg";
	ft_quote_removal(command);

	mu_check(ft_strncmp(command->argv[0], assert_str, ft_strlen(assert_str) + 1) == 0);
	ft_del_command(command);

	command = ft_new_command(ft_tokenizer("\"hello\"'world'"), g_minishell.envp, ft_get_paths(g_minishell.envp));
	assert_str = "helloworld";

	ft_quote_removal(command);
	mu_check(ft_strncmp(command->argv[0], assert_str, ft_strlen(assert_str) + 1) == 0);
	ft_del_command(command);
}

MU_TEST(test_shouldnot_remove_quotes_not_acting_as_quoting) {
	t_command	*command = ft_new_command(ft_tokenizer("'\"$?\"'"), g_minishell.envp, ft_get_paths(g_minishell.envp));
	char		*assert_str = "\"$?\"";

	ft_quote_removal(command);
	mu_check(ft_strncmp(command->argv[0], assert_str, ft_strlen(assert_str)) == 0);
	ft_del_command(command);

	command = ft_new_command(ft_tokenizer("\"'echo'\""), g_minishell.envp, ft_get_paths(g_minishell.envp));
	assert_str = "'echo'";

	ft_quote_removal(command);
	mu_assert_string_eq(assert_str, command->filename);
	ft_del_command(command);
}

MU_TEST(test_should_not_remove_quotes_that_was_expanded) {
	t_command	*command = ft_new_command(ft_tokenizer("$quoted_var"), g_minishell.envp, ft_get_paths(g_minishell.envp));
	char		*assert_str = "'hello'";
	ft_expand_args(command);

	ft_quote_removal(command);
	mu_check(ft_strncmp(command->argv[0], assert_str, ft_strlen(assert_str) + 1) == 0);
	ft_del_command(command);

	command = ft_new_command(ft_tokenizer("\"$quoted_var2\""), g_minishell.envp, ft_get_paths(g_minishell.envp));
	assert_str = "\"hello\"";
	ft_expand_args(command);

	ft_quote_removal(command);
	mu_assert_string_eq(assert_str, command->argv[0]);
	mu_assert_string_eq(assert_str, command->filename);
	ft_del_command(command);
}

MU_TEST_SUITE(test_quote_removal) {
	MU_RUN_TEST(test_should_remove_quotes_acting_as_quoting);
	MU_RUN_TEST(test_shouldnot_remove_quotes_not_acting_as_quoting);
	MU_RUN_TEST(test_should_not_remove_quotes_that_was_expanded);
}
